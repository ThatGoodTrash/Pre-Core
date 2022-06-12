/**
 * 1. Write a program that converts Centigrade to Fahrenheit. Go to the editor
 * Expected Output :
 * Input a temperature (in Centigrade): 45
 * 113.000000 degrees Fahrenheit.
 * 
 * @file ex_io1.c
 */

#include <stdio.h>

int main()
{
    char input[100];
    printf("Input a temperature (in Centigrade): ");
    char* received = fgets(input, 100, stdin);

    float converted = (float)atoi(received) * 1.8 + 32.0;


    printf("%f degrees Farenheit", converted); 

}