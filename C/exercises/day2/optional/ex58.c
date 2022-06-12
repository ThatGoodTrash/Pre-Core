/**
 * Find and fix the logic error without dramatically changing the program.
 * @file ex58.c
 */

#include <stdio.h>
#include <string.h>

char printBuffer[100] = "buffalobuffalobuffaloHello World!buffaloBuffalobuffalo";

char *read_character_from_buffer(int *pIter){
    pIter++;
    return &printBuffer[(*pIter)-1];
}

int main(int argc, char **argv) {
    int iter = 0;
    printf("Result: ");
    for(int i=0; i<strlen("Hello World!"); i++){
        printf("%c", *read_character_from_buffer(&iter));
    }
    printf("\n");
    return 0;
}
