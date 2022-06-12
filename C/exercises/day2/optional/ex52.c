/**
 * Find and fix the logic error without dramatically changing the program.
 * @file ex52.c
 */

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    const int iterations = 0x00010000;
    printf("Iteration number...");
    for(short i = 0; i < iterations; ++i ) {
        printf("\t%d\n", i);
    }
    printf("\nHello World!\n");

    return 0;
}
