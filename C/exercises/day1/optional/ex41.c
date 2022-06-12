/**
 * Find and fix the logic error without dramatically changing the program.
 * @file ex41.c
 */

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    char gibberish[100] = "BuffalobuffaloBuffalobuffaloHello World!buffalobuffaloBuffalobuffalo";
    char *searchForHello = strchr(gibberish, 'W');

    char printMessage[100] = {'\0'};
    strncpy(printMessage, searchForHello, 13);
    
    if(strncmp(printMessage, "Hello World!", 13) == 0){
        printf("Result: %s.\n", printMessage);
    } else{
        printf("No dice!\n%s.\n", printMessage);
    }
    return 0;
}
