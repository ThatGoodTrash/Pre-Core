/**
 * Find and fix the logic error.
 * @file ex25.c
 */

#include <stdio.h>

int main(int argc, char **argv) {
    int a = 1;
    int b = 2;
    int c = 3;
    if(a < b && b < c)
	    printf("Hello World!\n");
    else 
    printf("Buuuuurt! Incorrect!\n");
    return 0;
}
