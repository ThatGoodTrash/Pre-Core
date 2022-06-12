/**
 * Write a C program that prints out the value of'printMessage' as 
 * well as printing out it's address.
 * You might have to lookup the 'printf' function and how to format
 * strings properly in order to print out the address.
 * The example output is below.
 * """
 *      Value of printMessage:   Hello World!.
 *      Address of printMessage: 0x7ffc76d51a60.
 * """
 * @file ex55.c
*/

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    char printMessage[100] = "Hello World!";
    printf("Value of printMessage: %s\n", printMessage);
    printf("Address of printMessage: %p\n", &printMessage);
    return 0;
}
