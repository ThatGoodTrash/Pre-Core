/**
 * A macro is utilized to enable and disable segments of code.
 * Your goal is to have "Hello World!" printed to the console screen.
 * @file ex12.c
 */


#include <stdio.h>

#define _DEBUG 1

#ifdef PRODUCTION
#define MODE 1
#else
#define MODE 0
#endif

int main(int argc, char **argv) {
    #ifdef _DEBUG
    #if MODE == 0
    printf("Hello World!\n");
    
    #endif
    #else
    printf("This application is in production\n");
    #endif

    return 0;
}
