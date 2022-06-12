/**
 * Find and fix the logic error without dramatically changing the program.
 * @file ex70.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADD 0
#define SUB 1
#define MUL 2
#define DIV 3

float math_add(float a, float b){
    return a + b;
}

float math_sub(float a, float b){
    return a - b;
}

float math_mul(float a, float b){
    return a * b;
}

float math_div(float a, float b){
    return a / b;
}

int main(int argc, char **argv) {
    char printMessage[100] = "Hello World!";
    
    // Create and assign the functions needed to fullfill the
    // conditions below and print the proper values.
    float (*mathFuncs[4])(float, float) = {math_add, math_sub, math_mul, math_div};

    if( mathFuncs[ADD](1,2) == 3 &&
        mathFuncs[SUB](3,1) == 2 &&
        mathFuncs[MUL](4,2) == 8 &&
        mathFuncs[DIV](4,2) == 2){
        printf("Results: %s\n", printMessage);
    } else {
        printf("Results: No dice!\n");
    }
    
    return 0;
}
