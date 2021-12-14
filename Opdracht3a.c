#include <stdio.h>
#define MAX 3

float arraytotal(float a1[], float a2[], float a3[]);
float arrayshow(float a[]);

int main(){
    float a1[] = {0.7, 3.3, 0.5, 10.3};
    float *ptr1;
    ptr1 = a1;
    float a2[] = {4.1, 1.5, 0.5, 2.3};
    float *ptr2;
    ptr2 = a2;
    float a3[MAX];
    float *ptr3;
    ptr3 = a3;



    printf("First Array: \n");
    arrayshow(ptr1);
    printf("Second Array: \n");
    arrayshow(ptr2);
    printf("Third Array: \n");
    arraytotal(ptr1,ptr2,ptr3);
}


float arrayshow(float a[]){
    int i = 0;
    for(i=0; i<MAX; i++){
        printf("%f\n",a[i]);
    }
    printf("\n");
}
float arraytotal(float a1[], float a2[], float a3[]){
    int i = 0;
    for(i=0;i<MAX;i++){
        if(a1[i]>a2[i]){
            a3[i] = a1[i];
        } else{
            a3[i] = a2[i];
        }
    }
    arrayshow(a3);
}