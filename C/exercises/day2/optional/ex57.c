/**
 * Write a C program that adds the value of the two pointers pValueA and pValueB
 * together and then prints it out.
 * While you're at it, 
 *      - print the address of each pointer,
 *      - print the value of each pointer,
 *      - print the value pointer at by each pointer
 * The example output is below.
 *  """
 *      10 + 20 = 30
 *      pValueA Addr:   0x7fff9e5305a8
 *      pValueA Value:  0x7fff9e5305a0
 *      pValueA ValPtr: 10
 *      
 *      pValueB Addr:   0x7fff9e5305b0
 *      pValueB Value:  0x7fff9e5305a4 
 *      pValueB ValPtr: 20
 *  """
 * @file ex57.c
*/

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    // Ignore these two variables.
    int iA = 10;
    int iB = 20;

    // Add these two variables together
    int *pValueA = &iA;
    int *pValueB = &iB;

    // Start doing math and printing from here! Good luck!
    return 0;
}
