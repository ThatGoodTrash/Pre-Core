/**
 * Find and fix the logic error without dramatically changing the program.
 * @file ex67.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _sPartial{
    char part;
    struct _sPartial *pNext;
    struct _sPartial *pPrev;
} sPartial;

char printBuffer[100] = "Hello World!";

// Helper function to create new nodes
sPartial *create_node(sPartial *in, char value){
    sPartial* pNewNode = calloc(1, sizeof(sPartial));
    pNewNode->part = value;
    pNewNode->pPrev = in;
    in->pNext = pNewNode;
    printf("[%c] Prev-> %p, Next-> %p, In-> %p, sizeof-> %ld\n",
            value,
            pNewNode->pPrev,
            pNewNode->pNext,
            in, sizeof(sPartial));
    return pNewNode;
}

int main(int argc, char **argv) {
    // Create the header.
    sPartial *printMessage = NULL;
    printMessage = calloc(1, sizeof(sPartial));
    printMessage->part = printBuffer[0];

    // Create the iter
    sPartial *pIter = printMessage;
    int iCounter = 0;

    // Create the chain
    do{
        sPartial *pNext = NULL;
        create_node(pIter, printBuffer[iCounter]);
        if(pNext->part == '!'){
            break;
        }
        pIter = pNext;
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
