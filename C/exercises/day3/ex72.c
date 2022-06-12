/**
 * Find and fix the logic error without dramatically changing the program.
 * @file ex72.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Assign the correct value to Flags (programically or by hand) so that
// it is set to 0 after passing through the 'CheckFlags' function.
unsigned int Flags = 0;

unsigned int check_flags(unsigned int inFlags){
    inFlags ^= (1<<10);
    inFlags ^= (1<<1);
    inFlags ^= (1<<8);
    inFlags ^= (1<<30);
    inFlags ^= (1<<22);
    inFlags ^= (1<<16);
    // 00000000000000000000000000000000
    return inFlags;
}

int main(int argc, char** argv) {
    char printMessage[100] = "Hello World!";
    if(check_flags(Flags) == 1078002946){
        printf("Results: %s\n", printMessage);
    } else {
        printf("Results: No dice!\n");
    }
    
    return 0;
}
