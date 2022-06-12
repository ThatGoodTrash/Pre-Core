/**
 * Create a C program that accepts two integers and checks whether they are equal or not.
 * The program output should print to console one of the two.
 * "The numbers # and # are equal."
 * "The numbers # and # are not equal."
 * The user input is already done for you.
 * @file ex27.c
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if(argc < 3){
        /*
        *   Usage: ./ex27 <#> <#>
        *       ./ex27 5 5
        */
        printf("Usage: %s <#> <#>\n\t%s 5 5\n", argv[0], argv[0]);
        return -1;
    }
    // A new function from the standard library is used in this program.
    // atoi is a function used to convert a string number such as "52" into
    // its data type representative.
    //...                           // Argv[0] is the program name/path passed in
    int firstNumber = atoi(argv[1]);// Argv[1] is the first parameter passed in
    int secondNumber= atoi(argv[2]);// Argv[2] is the second parameter passed in
    printf("Comparing values %d and %d\n", firstNumber, secondNumber);

    return 0;
}
