/**
 * Find and fix the logic error without dramatically changing the program.
 * @file ex61.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    char *printMessage = NULL;

    printMessage = (char*)malloc(13);
    //printMessage = NULL;

    strncpy(printMessage, "Hello World!", 13);

    printf("Result: %s\n", printMessage);

    free(printMessage);
    return 0;
}
