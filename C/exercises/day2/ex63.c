/** 
 * What went wrong?! There's a logical bug in this program that causes it to crash after a period of time.
 * Fix it!
 * ***** Note ***** Note ***** Note ***** Note ***** 
 * 
 * To exit the program, you'll need to Ctrl+C the application
 * 
 * *************************************************
 * Hint* Look at the memory usage
 * @file ex63.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _sData {
    char strName[20];
    int iAge;
};

int main(int argc, char **argv) {
    struct _sData *pDataArray = NULL;
    char strBuffer[100] = {0};
    int iAgeBuffer = 0;
    while(1){
        // Generate a random name and age
        sprintf(strBuffer, "UsernameTemplate_%d", rand());
        iAgeBuffer = rand();

        // Allocate the data
        pDataArray = calloc(1, sizeof(pDataArray));
        strncpy(pDataArray->strName, strBuffer, strnlen(strBuffer, 100));
        pDataArray->iAge = iAgeBuffer;

        printf("The name is %s and the age is %d.\n", pDataArray->strName, pDataArray->iAge);
    }

    // Free the data
    free(pDataArray);
    return 0;
}
