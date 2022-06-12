/**
 * Find and fix the logic error without dramatically changing the program.
 * @file ex53.c
 */

#include <stdio.h>
#include <string.h>

char *find_hello_world(char *buffer){
    return strstr(buffer, "Hello World!");
}

void copy_results(char *outBuffer, char *inBuffer){
    strncpy(outBuffer, inBuffer, 12);
}

int main(int argc, char **argv) {
    char gibberish[100] = "BuffalobuffaloBuffalobuffaloHello World!buffalobuffaloBuffalobuffalo";
    char printMessage[100] = {'\0'};

    char *pHelloLocation = find_hello_world(gibberish);
    copy_results(printMessage, pHelloLocation);
    
    printf("Result: %s.\n", printMessage);

    return 0;
}
