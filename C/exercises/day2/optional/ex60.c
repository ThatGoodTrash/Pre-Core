/**
 * Find and fix the logic error without dramatically changing the program.
 * @file ex60.c
 */

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    // Try not to reassign or modify password in this
    // exercise.
    float password = 3.14597;

    // Focus on modifying 'password' inside the condition instead.
    if(password == 3){
        printf("Result: Hello World!\n");
    } else {
        printf("Result: No dice!\n");
    }
    return 0;
}
