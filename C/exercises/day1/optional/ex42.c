/**
 * Find and fix the logic error without dramatically changing the program.
 * @file ex42.c
 */

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    char printMessage[100] = {'#'};
    strncpy(printMessage, "Hello World!", 13);

    strnset(printMessage, '#', strnlen(printMessage, 100));
    
    if(strncmp(printMessage, "Hello World!", 13) == 0){
        printf("Result: %s.\n", printMessage);
    } else{
        printf("No dice!\n%s.\n", printMessage);
    }
    return 0;
}
