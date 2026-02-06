#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "array.h"
#define ARRAY_SIZE 2026

#define DEBUG 0

int main (void) {
    //-Werror does not like unused parameters
    
    printf("Hello, World!\n");

    int32_t arr[ARRAY_SIZE];

    initalize_array(arr, ARRAY_SIZE, 0);

    // Tests
    #if DEBUG == 1
    printf("The first element of the array is: %d\n", arr[0]);
    printf("The last element of the array is: %d\n", arr[ARRAY_SIZE - 1]);
    // printf("This value should be out of bounds: %d\n", arr[ARRAY_SIZE]); // This is undefined behavior, but we want to see what happens
    #endif

    return 0;
}
// -Werror requires a new line at the end of the file
