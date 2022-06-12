/**
 * Find and fix the logic error without dramatically changing the program.
 * @file ex56.c
 */

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    char printBuffer[100] = "Hello World!";

    char *printMessage = NULL;

    printf("Result: %s.\n", printMessage);
    return 0;
}