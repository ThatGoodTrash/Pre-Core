/**
 * Find and fix the logic error without dramatically changing the program.
 * @file ex68.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

union _uMessage{
    char cBuffer[80];
    struct {
        char targetA[20];
        char targetB[20];
        char targetC[20];
        char targetD[20];
    } parts;
};

void prep_message(union _uMessage *pMsg){
    memset(pMsg->cBuffer, '-', 80);
    printf("Writing to offset [targetA] %p\n", &pMsg->parts.targetA);
    strncpy(pMsg->parts.targetA, "Hel", 3);

    printf("Writing to offset [targetB] %p\n", &pMsg->parts.targetB);
    strncpy(pMsg->parts.targetB, "lo ", 3);

    printf("Writing to offset [targetC] %p\n", &pMsg->parts.targetC);
    strncpy(pMsg->parts.targetC, "Wor", 3);
    
    printf("Writing to offset [targetD] %p\n", &pMsg->parts.targetD);
    strncpy(pMsg->parts.targetD, "ld!", 3);
}

int main(int argc, char **argv) {
    union _uMessage printBuffers;
    prep_message(&printBuffers);
    printf("Prepped Message: \n[");
    for(int i=0; i<80; i++){
        printf("%c", printBuffers.cBuffer[i]);
    }
    printf("]\n");


    // Your goal is to parse together the parts of the union (or skip certain characters)
    // into the 'printMessage' buffer.
    // You shouldn't have to modify any code above this point. Everything
    // you need is inside the printBuffers variable.
    char printMessage[80] = {'\0'};
    strncat(printMessage, printBuffers.parts.targetA, 3);
    strncat(printMessage, printBuffers.parts.targetB, 3);
    strncat(printMessage, printBuffers.parts.targetC, 3);
    strncat(printMessage, printBuffers.parts.targetD, 3);
    printf("Results: %s\n", printMessage);
    
    return 0;
}
