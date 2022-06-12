/**
 * Find and fix the type logic error.
 * @file ex19.c
 */

#include <stdio.h>

int main(int argc, char **argv) {
    char *printMessage = "Hello world!";
    
    // Does this work?
    float checkValue = 10.5;

    // Try to get the correct result without changing any code below
    // this point.
    if(checkValue == 10.5){
        printf("Results: %s\n", printMessage);
    } else {
        printf("Results: No dice!\n");
    }
    return 0;
}
