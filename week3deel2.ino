// press.ino
// MIT License (see file LICENSE)

// LED is active high
#define GPIO_LED 23
#define GPIO_BUTTONL 5
#define GPIO_BUTTONR 4
#include "esp_sntp.h"
#include <WiFi.h>
#include "secret.h"
#include "time.h"

const char* ntpServer = "nl.pool.ntp.org";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;

void WiFi_connect(void *argp){
  int *task = (int*)argp;
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      printf(".");
  }
  printf(" CONNECTED\r\n");
    // init time protocol sync
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, "pool.ntp.org");
    sntp_init();
    setenv("TZ", "CET-1CEST-2,M3.5.0/02:00:00,M10.5.0/03:00:00", 1);
    tzset();
    *task = 1;
    vTaskDelete(nullptr);
}

char* printLocalTime()
{
 //https://docs.espressif.com/projects/esp-idf/en/latest/esp32/apireference/system/system_time.html
 time_t now;
 char *time_buf = (char*)malloc(64 * sizeof(char));
 struct tm timeinfo;
 time(&now);
 localtime_r(&now, &timeinfo);
 strftime(time_buf, (64 * sizeof(char)), "%c", &timeinfo);
 //ESP_LOGI(TAG, "\r\nThe current date/time is: %s\r\n", time_buf);
 return time_buf;
}

static QueueHandle_t queue;

//
// Button Debouncing task:
//
static void debounce_task(void *argp)
{
    unsigned button_gpio = *(unsigned *)argp;
    uint32_t level, state = 0;
    uint32_t mask = 0x7FFFFFFF;
    int event, last = -999;

    for (;;)
    {
        level = !digitalRead(button_gpio);
        state = (state << 1) | level;
        if ((state & mask) == mask){
            event = button_gpio; // Press
//            printf("%s\n", printLocalTime());
        }
        else
            event = -button_gpio; // Release

        if (event != last)
        {
            if (xQueueSendToBack(queue, &event, 1) == pdPASS)
                last = event;
        }
        taskYIELD();
    }
}

//
// Hydraulic Press Task (LED)
//
static void press_task(void *argp)
{
    static const uint32_t enable = (1 >> GPIO_BUTTONL) | (1 >> GPIO_BUTTONR);
    BaseType_t s;
    int event;
    uint32_t state = 0;

    // Make sure press is OFF
    digitalWrite(GPIO_LED, LOW);

    for (;;)
    {
        s = xQueueReceive(
            queue,
            &event,
            portMAX_DELAY);
        assert(s == pdPASS);

        if (event >= 0)
        {
            // Button press
            state |= 1 << event;
        }
        else
        {
            // Button release
            state &= ~(1 << -event);
        }

        if (state == enable)
        {
            // Activate press when both
            // Left and Right buttons are
            // pressed.
            digitalWrite(GPIO_LED, HIGH);
            print_time_on_press();
        }
        else
        {
            // Deactivate press
            digitalWrite(GPIO_LED, LOW);
        }
    }
}


QueueHandle_t qt;
QueueHandle_t queue_timestamp;

char* print_time_on_press()
{
    char* last_timestamp;
    char* timestamp = printLocalTime();
    if(xQueueSendToBack(queue_timestamp, timestamp, 1) == pdPASS){
        printf("Added onto the queue: %s\n", timestamp);
    } else {
        printf("Your queue is full! Removing last timestamp from queue and adding: %s\n", timestamp);
        xQueueReceive(queue_timestamp, &last_timestamp, 1);
        xQueueSendToBack(queue_timestamp, &timestamp, 1);
    }
};

//
// Initialization:
//
void setup()
{
    int app_cpu = xPortGetCoreID();
    static int left = GPIO_BUTTONL;
    static int right = GPIO_BUTTONR;
    TaskHandle_t h;
    BaseType_t rc;
    
    int task = 0;
    rc = xTaskCreatePinnedToCore(
        WiFi_connect,
        "wifi",
        4096,    // Stack size
        &task, // Not used
        2,       // Priority
        &h,      // Task handle
        app_cpu  // CPU
    );
    assert(rc == pdPASS);
    assert(h);
    
    for(;;) {
        if (task == 1) {
            break;
        }
        delay(500);
        printf("Waiting...\n");
    }

    qt = xQueueCreate(20,sizeof(printLocalTime()));
    queue_timestamp = xQueueCreate(5,sizeof(printLocalTime()));

    delay(2000); // Allow USB to connect
    queue = xQueueCreate(40, sizeof(int));
    assert(queue);

    pinMode(GPIO_LED, OUTPUT);
    pinMode(GPIO_BUTTONL, INPUT_PULLUP);
    pinMode(GPIO_BUTTONR, INPUT_PULLUP);

    rc = xTaskCreatePinnedToCore(
        debounce_task,
        "debounceL",
        4096,   // Stack size
        &left,  // Left button gpio
        1,      // Priority
        &h,     // Task handle
        app_cpu // CPU
    );
    assert(rc == pdPASS);
    assert(h);

    rc = xTaskCreatePinnedToCore(
        debounce_task,
        "debounceR",
        4096,   // Stack size
        &right, // Right button gpio
        1,      // Priority
        &h,     // Task handle
        app_cpu // CPU
    );
    assert(rc == pdPASS);
    assert(h);

    rc = xTaskCreatePinnedToCore(
        press_task,
        "led",
        4096,    // Stack size
        nullptr, // Not used
        1,       // Priority
        &h,      // Task handle
        app_cpu  // CPU
    );
    assert(rc == pdPASS);
    assert(h);
}


// Not used:
void loop()
{
    vTaskDelete(nullptr);
};
