#include <stdint.h>
#include <stddef.h>

#ifndef ARRAY_H
#define ARRAY_H

int32_t* initalize_array(int32_t arr[], size_t size, int32_t initial_value);
/*
Initializes an array of int32_t values to a specified initial value. 
The first argument is the array to be initialized, 
the second argument is the size of the array, 
and the third argument is the initial value to set for each element in the array.
The function returns the initialized array.
*/

#endif // ARRAY_H
