/**
 * You're end goal is to have "Hello World" printed to screen.
 * @file ex51.c
 */

#include "../headers/money.h"
#include <stdio.h>


int main() {
    if(paycheck_please() > 100.0l){
        printf("Hello World!\n\n");
        printf("I make $%llu a pay period!\n", paycheck_please() );
    } else {
        printf("I make a depressing $%llu per pay period!\n", paycheck_please() );
    }

    return 0;
}
