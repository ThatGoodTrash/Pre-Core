/** 
 * Oh no! Something's wrong!
 * Your goal is to fix the program so that it prints "hello World" to the screen.
 * Try not to dramatically change the program, it should only require a few small edits to solve.
 * @file ex64.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _sPartial{
    char part;
} sPartial;

char printBuffer[100] = "Hello World!";

int main(int argc, char **argv) {
    struct _sPartial printMessage[100];

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
