/**
 * Create a C program that accepts one integer and checks if the value is 
 * positive or negative.
 * The program output should print to console one of the two.
 * "The number # is positive."
 * "The number # is negative."
 * The user input is already done for you.
 * @file ex29.c
 */

#include <stdio.h>

int main(int argc, char **argv) {
    if(argc > 3){
        /*
        *   Usage: ./ex19-goal <#>
        *       ./ex19-goal 5
        */
        printf("Usage: %s <#>\n\t%s 5\n", argv[0], argv[0]);
        return -1;
    }
    // A new function from the standard library is used in this program.
    // atoi is a function used to convert a string number such as "52" into
    // its data type representative.
    //...                           // Argv[0] is the program name/path passed in
    int firstNumber = atoi(argv[1]);// Argv[1] is the first parameter passed in

    printf("Checking the value %d\n", firstNumber);
    if (firstNumber >= 0){
        printf("The number %d is positive.", firstNumber);
    }
    else{
        printf("The number %d is negative.", firstNumber);
    }

    return 0;
}
