/**
 * Without using a static array, allocate some memory and create a banner to print to the screen.
 * It's up to you on the size, however try to remain within the standard 80x20 console chracter dimensions.
 * The banner should be animated and the text should scroll across the screen similar to how marquee text does in HTML.
 * After creating the banner, dump it to the screen, clean up, then exit out with style.
 * Try to perform proper error and bounds checking to get us to a secure coding standard.
 * @file ex62.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    char *printMessage = NULL;

    // Allocate memory!
    printMessage = (char*)malloc(13);

    // Copy memory!
    strncpy(printMessage, "Hello World!", 13);

    // Print memory!
    printf("Result: %s\n", printMessage);

    // Free memory!
    free(printMessage);
    return 0;
}