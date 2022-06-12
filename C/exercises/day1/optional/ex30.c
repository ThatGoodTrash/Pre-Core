/**
 * Find and fix the logic error.
 * @file ex30.c
 */

#include <stdio.h>

int main(int argc, char **argv) {
    int a = 1;
    int b = 2; 
    int c = 3;
    int d = 4;
    int e = 5;
    if( a > b && b < c &&
        d <= 0 && e != 5)
	    printf("Hello World!\n");
    else 
    printf("Buuuuurt! Incorrect!\n");
    return 0;
}
