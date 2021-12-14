#include <stdio.h>
int main() {
    char s[10000];
    gets(s);
    printf("Size = %d\n", strlen(s));
    
    return 0;
}