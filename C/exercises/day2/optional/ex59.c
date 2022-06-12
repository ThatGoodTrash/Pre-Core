/**
 * Find and fix the logic error without dramatically changing the program.
 * @file ex59.c
 */

#include <stdio.h>
#include <string.h>

int div_magic(int firstNum, int secondNum){
    return firstNum / secondNum;
}

int main(int argc, char **argv) {

    if(divMagic(7,3) >= 2){
        printf("Result: Hello World! %f\n", div_magic(7,3));
    } else {
        printf("Result: No dice! %f\n", div_magic(7,3));
    }
    return 0;
}
