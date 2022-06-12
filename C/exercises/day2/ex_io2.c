/**
 *  1. Write a program in C to create and store information in a text file. Go to the editor
 * Test Data :
 * Input a sentence for the file : This is the content of the file test.txt.
 * Expected Output :
 * The file test.txt created successfully...!!
 * 
 * @file ex_io2.c
 **/

#include <stdio.h>

int main()
{
    FILE* fp;
    char* input[100];
    printf("Input a sentence for the file: ");
    char* user_input = fgets(input, 100, stdin);
    fp = fopen("/tmp/test.txt", "w");
    fputs(user_input, fp);
    fclose(fp);
    printf("The file test.txt created successfully");
}