/**
 * Find and fix the type logic error.
 * @file ex24.c
 */

#include <stdio.h>

int main(int argc, char **argv) {
    char *printMessage = "Hello world!";
    
    // Does this work?
    unsigned int checkValue = 65593;

    // Try to get the correct result without changing any code below
    // this point.
    if(checkValue == 65593){
        printf("Results: %s\n", printMessage);
    } else {
        printf("Results: No dice!\n");
    }
    return 0;
}
