#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "array.h"

int32_t* initalize_array(int32_t arr[], size_t size, int32_t initial_value) {
    for (size_t i = 0; i < size; i++) {
        arr[i] = initial_value;
    }
    return arr;
}

