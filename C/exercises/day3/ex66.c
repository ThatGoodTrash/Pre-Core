/**
 * Find and fix the logic error without dramatically changing the program.
 * @file ex66.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _sPartial{
    char part;
    struct _sPartial *pNext;
} sPartial;

char printBuffer[100] = "Hello World!";

int main(int argc, char **argv) {
    // Create the header.
    sPartial *printMessage = NULL;
    printMessage = calloc(1, sizeof(sPartial));

    // Create the iter
    sPartial *pIter = printMessage;
    int iCounter = 0;

    // Create the chain
    do{
        pIter->part = printBuffer[iCounter];
        if(pIter->part == '!'){
            break;
        }
        pIter = pIter->pNext;
        iCounter++;
    } while(1);

    // Print out the chain
    printf("Result: ");
    for(pIter=printMessage; pIter != NULL; pIter = pIter->pNext){
        printf("%c", pIter->part);
    }
    printf("\n");

    // Clean up the chain
    pIter = printMessage;
    sPartial *pNext = printMessage;
    while(pNext != NULL){
        pNext = pIter->pNext;
        free(pIter);
        pIter = pNext;
    }
    return 0;
}
