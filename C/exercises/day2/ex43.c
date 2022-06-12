/**
 * Find and fix the logic error without dramatically changing the program.
 * @file ex43.c
 */

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    char printMessage[100] = "Hello World!";

    printf("Result: ");
    for(int i =0; i < strnlen(printMessage, 100); i++){
        printf("%c", printMessage[i]);
    }
    printf("\n");
    return 0;
}
