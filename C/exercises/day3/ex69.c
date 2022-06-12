/**
 * Find and fix the logic error without dramatically changing the program.
 * @file ex69.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct _sElement{
    char data;
    int value;
};

struct _sElement printBuffer[] = {
    {'o', 93},  {' ', 82},
    {'!', 112}, {'H', 20},
    {'W', 87},  {'l', 50},
    {'o', 75},  {'e', 29},
    {'l', 99},  {'d', 103},
    {'l', 50},  {'\0', 142},
    {'r', 95},
};
int printBufferLength = sizeof(printBuffer)/sizeof(printBuffer[0]);

// Create a function that is passed into the 'SortTheList' function.
// The function will be the comparison component allowing 'SortTheList' to properly
// function
//
// The end result should be 'Hello World!' printed to screen.
// --- Start function below this
int sort_items(int a, int b){
    if(a > b){
        return a;
    }
    else{
        return b;
    }
}
// --- End your function above this




// SortTheList shouldn't require any adjustments
void sort_the_list(struct _sElement *pElements, int (*sorting_function)(int, int), int numberOfElements){
    for(int i=0; i<numberOfElements-1; i++){
        for(int j=i+1; j<numberOfElements; j++){
            if(sorting_function(pElements[i].value, pElements[j].value) > 1){
                struct _sElement tempElement = pElements[i];
                pElements[i] = pElements[j];
                pElements[j] = tempElement;
            }
        }
    }
}

// Nothing inside the main function should need to be changed.
// If anything is changed, it's the name of the function passed in.
int main(int argc, char **argv) {
    char printMessage[100] = {'\0'};
    
    for(int i=0; i<printBufferLength; i++){
        printMessage[i] = printBuffer[i].data;
    }
    printf("Before: %s\n", printMessage);

    // If you change anything, change 'my_amazing_function' name to your
    // own function.
    sort_the_list(printBuffer, sort_items, printBufferLength);
    for(int i=0; i<printBufferLength; i++){
        printMessage[i] = printBuffer[i].data;
    }
    printf("Results: %s\n", printMessage);
    
    return 0;
}
