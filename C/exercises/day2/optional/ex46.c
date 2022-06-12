/**
 * Write a C program to tokenize the text inside 'cBuffer'. 
 * Tokens mean breaking the string apart into special 'words' based off a particular delimiter.
 * For this exercise, use ' ',(space), 0x20 as the delimiter and print out each word individually.
 * It should output something similar to below.
 * "tokenize this string with the power of string functions!"
 *      tokenize
 *      this
 *      string  
 *      with
 *      the
 *      power
 *      of
 *      string
 *      functions!
 * @file ex46.c
*/

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    char gibberish[] = "Betty Botter bought some butter;
But,\" said she, \"this butter's bitter!
If I put it in my batter
It will make my batter bitter.
But a bit o' better butter
Will but make my batter better.\"
Then she bought a bit o’ butter
Better than the bitter butter,
Made her bitter batter better.
So 'twas better Betty Botter
Bought a bit o’ better butter.";

    // Start tokenizing!

    return 0;
}
