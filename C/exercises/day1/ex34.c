/**
 * Find and fix the logic error.
 * @file ex34.c
 */

#include <stdio.h>

int main(int argc, char **argv) {
    char *successMessage = "Hello world!";
    char *failureMessage = "Buuuuurt! Incorrect!";
    
    int a = 1;
    char *printMessage = (a)? successMessage : failureMessage;
    printf("%s\n", printMessage);
    return 0;
}
