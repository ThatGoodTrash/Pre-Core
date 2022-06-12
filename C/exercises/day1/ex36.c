/**
 * Find and fix the logic error.
 * @file ex36.c
 */

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    char printMessage[100] = {'\0'};

    strncpy(printMessage, "Hello world!", 12);

    printf("Result: %s.\n", printMessage);
    return 0;
}
