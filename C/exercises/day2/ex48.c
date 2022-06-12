/**
 * Compile and execute this file and observe the number errors. NO CODING REQUIRED.
 * @file ex48.c
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if( argc < 4 ) {
        fprintf(stderr, "Enter a positive or negative number, an operator, and another positive or negative number separated by a space\n");
        fprintf(stderr, "Example: +1 * -2.6\n");
        fprintf(stderr, "To use multiplication, escapt the asterisk (\\*)\n");
        exit(-1);
    }

    unsigned long a = strtod(argv[1], NULL);
    unsigned long b = strtod(argv[3], NULL);

    if( argv[2][0] == '+' ) {
        printf("%ld + %ld = %ld\n", a, b, a + b);
    } else if ( argv[2][0] == '-' ) {
        printf("%ld - %ld = %ld\n", a, b, a - b);
    } else if ( argv[2][0] == '*' ) {
        printf("%ld * %ld = %ld\n", a, b, a * b);
    } else if ( argv[2][0] == '/' ) {
        printf("%ld / %ld = %ld\n", a, b, a / b);
    } else {
        fprintf(stderr, "Unsupported operator (%c). Valid operators are +-*/\n", argv[2][0]);
    }

}