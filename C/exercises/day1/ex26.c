/**
 * Find and fix the type logic error.
 * @file ex26.c
 */

#include <stdio.h>

int main(int argc, char **argv) {
    char* printMessage = "Hello world!";
    
    // Does this work?
    unsigned int checkValue = 60000;
    unsigned short temp = 60000;

    checkValue += temp;

    // Try to get the correct result without changing any code below
    // this point.
    if(checkValue == 120000){
        printf("Results: %s\n", printMessage);
    } else {
        printf("Results: No dice!\n");
    }
    return 0;
}
