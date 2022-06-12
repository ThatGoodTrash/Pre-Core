/** 
 * There is nothing wrong with this program, modify the arguments for different results.
 * There are two "victories" you can get in this program and neither require code modification. 
 * Play around with the arguments passed into the program and try to win the end goal.
 * @file ex47.c
*/

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    int success = -1;
    if( argc != 3 ) {
        printf("Try somehing else to change the value of argc.\n");
    } else {
        printf("Hello World!\n");
        printf("SUCCESS! You figured out the secret!\n");
        printf("For an extra challenge, try changing argv[0]\n");
        success = 0;
    }

    if( argc == 3 ) {

        int i = 0;
        char *start = argv[0];
        char *ptr = strtok(start, "/");
        for(i = 0; (ptr = strtok(NULL, "/")); ++i ) {
            *(ptr - 1) = '/';
        }

        if( i > 2 ) {
            printf("Ultra Hello World!\n");
            printf("You unlocked the unlockable hello world!\n");
        } else {
            printf("argv[0]: %s\n", argv[0]);
        }
    }

    if( success == -1) {
        printf("Current values in argv are:\n");
        for( int i = 0; i < argc; ++i ) {
            printf("argv[%d]: %s\n", i, argv[i]);
        }
    }
    return success;
}
