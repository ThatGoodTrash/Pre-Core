/**
 * Find and fix the logic error without dramatically changing the program.
 * @file ex54.c
 */

#include <stdio.h>
#include <string.h>


char gibberish[100] = "BuffalobuffaloBuffalobuffaloHello World!buffalobuffaloBuffalobuffalo";

void copy_results(char* outBuffer, char* inBuffer){
    strncpy(outBuffer, inBuffer, 13);
}

char *lottery_search(char searchChar){
    // Do not modify this function or its contents for this
    // exercrise.
    static int bufferOffset = 0;
    if(gibberish[bufferOffset] == searchChar){
        return &gibberish[bufferOffset];
    }
    bufferOffset++;
    return 0;
}

int main(int argc, char **argv) {
    char printMessage[100] = {'\0'};

    char *pHelloLocation = 0;
    
    pHelloLocation = lottery_search('W');
    if(pHelloLocation != 0){
        copy_results(printMessage, pHelloLocation);
        printf("Result: %s.\n", printMessage);
    }else{
        printf("No dice!\n");
    }
    
    return 0;
}
