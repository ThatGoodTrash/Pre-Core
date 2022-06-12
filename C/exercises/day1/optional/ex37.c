/**
 * Find and fix the type logic error.
 * @file ex37.c
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
    // Try to explain the puzzling behavior below.
    // Correct the code where need be, however the goal for this
    // exercise is more to understand why it happens.
    unsigned int max = 654321;
    short min =        123456;

    if( max > min ) {
        printf("Hello World! %d > %d\n", max, (unsigned int)min);
    } else {
        printf("Something is not quite right... %d > %d\n",
                max, 
                (unsigned int)min);
        return -1;
    }

    return 0;
}
