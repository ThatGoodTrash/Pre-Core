/**
 * 2. Write a program in C to read an existing file. Go to the editor
 * Test Data :
 * Input the file name to be opened : file_test.txt
 * Expected Output :
 * The content of the file file_test.txt is  :                                                                       
 * This is the content of the file file_test.txt.
 * 
 * @file ex_io3.c
 */

#include <stdio.h>

int main()
{
    char file_name[100];
    FILE* fp = NULL;
    char buff[255];
    printf("Input the file name to be opened: ");
    fgets(file_name, sizeof(file_name), stdin);
    fp = fopen(file_name, "r");
    fgets(buff, 255, fp);
    printf("The content of the file %s is: %s\n", file_name, buff);
    fclose(fp);
    
}