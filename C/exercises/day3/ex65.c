/**
 * Find and fix the logic error without dramatically changing the program.
 * @file ex65.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _sPartial{
    char part;
}sPartial;


// No need to modify anything below this point to solve this exercise~!!
char printBuffer[100] = "Hello World!";

int main(int argc, char **argv) {
    sPartial printMessage[100];

    for(int i=0; i< strnlen(printBuffer, 100); i++){
        printMessage[i].part = printBuffer[i];
    }

    printf("Result: ");
    for(int i=0; i< strnlen(printBuffer, 100); i++){
        printf("%c", printMessage[i].part);
    }
    printf("\n");

    return 0;
}
