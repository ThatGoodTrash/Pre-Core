/**
 * Find and fix the logic error without dramatically changing the program.
 * @file ex71.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

short Flags = 0;
// 0000000000000000

int check_flags(){
    if(!(Flags & 0b0100000000000100)) return 1;
    if(!(Flags & 0b0001000000000001)) return 0;
    if(!(Flags & 0b0000000100001000)) return 0;
    if(!(Flags & 0b0000010001000000)) return 0;
    if(!(Flags & 0b1000000000100100)) return 0;
    if(!(Flags & 0b0000000000000000)) return 0;
    return 0;
}

int main(int argc, char **argv) {
    char printMessage[100] = "Hello World!";
    if(check_flags()){
        printf("Results: %s\n", printMessage);
    } else {
        printf("Results: No dice!\n");
    }
    
    return 0;
}
