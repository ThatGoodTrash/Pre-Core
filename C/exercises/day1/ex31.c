/**
 * 
 * Create a C program that only prints out the first X values
 * of an array..
 * The program output should print to console each value up
 * to the request number.
 * ./ex20-goal 5
 * "1 2 3 4 5" 
 * This time, user input is NOT done for you!
 * @file ex31.c
 */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if(argc > 3){
        /*
        *   Usage: ./ex31 <#>
        *       ./ex31 5
        */
        printf("Usage: %s <#>\n\t%s 5\n", argv[0], argv[0]);
        return -1;
    }
    int firstNumber = atoi(argv[1]);// Argv[1] is the first parameter passed in
    // 'numberArray' contains the values to print out.
    int numberArray[100] = {0};
    for(int i=1; i<101; i++){ numberArray[i-1] = i; }
    for(int i=1; i<=firstNumber; i++){
        printf("%d ", numberArray[i-1]);
    }
    // Add code to print out the numbers below this point!
    
    return 0;
}
