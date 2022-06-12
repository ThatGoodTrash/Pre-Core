/**
 * Find and fix the logic error.
 * @file ex23.c
 */

#include <stdio.h>


int main(int argc, char **argv) {
    int a = 1;
    int b = 2; 
    if(a < b)
	    printf("Hello World!\n");
    else 
    printf("Buuuuurt! Incorrect!\n");
    return 0;
}
