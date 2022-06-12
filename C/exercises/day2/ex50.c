/**
 * Find and fix the logic error without dramatically changing the program.
 * @file ex50.c
 */

#include <stdio.h>
#include <string.h>

char *find_hello_world(char* buffer){
    return strstr(buffer, "Hello World!");
}

int main(int argc, char **argv) {
    char gibberish[100] = "BuffalobuffaloBuffalobuffaloHello World!buffalobuffaloBuffalobuffalo";
    char printMessage[100] = {'\0'};

    char *pHelloLocation = find_hello_world(gibberish);

    strncpy(printMessage, pHelloLocation, 12);
    printf("Result: %s.\n", printMessage);

    return 0;
}
