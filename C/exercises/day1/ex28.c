/**
 * Find and fix the logic error.
 * @file ex28.c
 */

#include <stdio.h>

int main(int argc, char **argv) {
    int a = 1;
    int b = 2; 
    int c = 3;
    int d = 4;
    if(a > b || b < c || d <= 0)
	    printf("Hello World!\n");
    else 
    printf("Buuuuurt! Incorrect!\n");
    return 0;
}
