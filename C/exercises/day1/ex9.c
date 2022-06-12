/**
 * A macro is utilized in this program to grab the minimal value of two numbers. Does it behave as expected?
 * If not, try to fix it. The goal is to have 'Hello World' printed to the screen.
 * @file ex9.c
 */

#include <stdio.h>
#include "minmacro.h"
//#include "othermacro.h"

int main(int argc, char **argv) {
    if(min(1, 4)==1){
        printf("Hello World!\n");
    }else{
        printf("The min of 1 and 4 is %d\n", min(1, 4));
    }

    return 0;
}
