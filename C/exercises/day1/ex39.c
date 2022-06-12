/**
 * Find and fix the logic error without dramatically changing the program.
 * @file ex39.c
 */

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    char firstWord[100] = "Know";
    char secondWord[100] = "No";

    char printMessage[100] = "Hello world!";

    
    if(strncmp(firstWord, secondWord, 100)){
        printf("Result: %s.\n", printMessage);
    } else{
        printf("No dice!\n");
    }
    return 0;
}
