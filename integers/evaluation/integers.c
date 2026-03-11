#include <stdio.h>
#include <stdlib.h>
#include "integers.h"

#define DEBUG 1

// Helper function to print the binary representation of a number
void print_binary(uint32_t n) {
    for (int i = 31; i >= 0; i--) {
        putchar(((n >> i) & 1U) ? '1' : '0');
        if (i % 4 == 0 && i != 0) putchar(' ');
    }
    printf("\n");
}

int32_t negate(int32_t x){
    // We cast the number into an unsigned integer to avoid undefined behavior when x is INT32_MIN,
    // When x is INT32_MIN its negation is INT32_MAX,
    // and adding 1 to INT32_MAX will wrap around to INT32_MIN,
    return (int32_t)(~((uint32_t)x) + 1);
}

int32_t conditional(int32_t x, int32_t y, int32_t z){
    // If x is nonzero, return y. Otherwise, return z.

    // If x is nonzero, is_nonzero will have its most significant bit set to 1. 
    // If x is zero, is_nonzero will be 0.
    // Cast to unsigned to avoid undefined behavior when x is INT32_MIN (negating INT32_MIN overflows int32_t).
    uint32_t unsigned_x = (uint32_t)x;
    int32_t is_nonzero = (int32_t)(unsigned_x | (~unsigned_x + 1U)); 

    int32_t mask = is_nonzero >> 31;
    // Shift the is_nonzero to the right by 31 bits.
    // If x is nonzero, is_nonzero will have its most significant bit set to 1, 
    // and shifting it right by 31 bits will result in a mask of all 1s.

    // if mask is all 1s, then mask & y will be y and ~mask & z will be 0, so we will return y.
    // If mask is all 0s, then mask & y will be 0 and ~mask & z will be z, so we will return z.
    int32_t result = (int32_t)((uint32_t)(mask & y) | (~((uint32_t)mask) & (uint32_t)z));
    #if DEBUG == 1
        printf("x: %d, y: %d, z: %d, is_nonzero: ", x, y, z);
        print_binary((uint32_t)is_nonzero);
        printf("mask: ");
        print_binary((uint32_t)mask);
        printf("result: %d\n", result);
    #endif

    return result;
}

int64_t handle_overflow(int32_t a, int32_t b){
    uint32_t unsigned_sum = (uint32_t)a + (uint32_t)b;

    // When a and b are both positive, if their sum exceeds INT32_MAX, 
    // the unsigned sum will exceed INT32_MAX but not UINT32_MAX.
    // When a and b are both negative, if their sum is less than INT32_MIN,
    // the unsigned sum will be exceeed UINT32_MAX and wrap around

    int64_t result = (int64_t)(int32_t)unsigned_sum;

    if (a > 0 && b > 0 && ((int32_t)unsigned_sum < 0)) {
        result += ((int64_t)1 << 32);  // positive overflow: add 2^32
    }
    if (a < 0 && b < 0 && ((int32_t)unsigned_sum) >= 0) {
        result -= ((int64_t)1 << 32);  // negative overflow: subtract 2^32
    }

    return result;

    // The follow implementation might be the intended way to solve this problem
    // // If a and b are both positive
    // // and the distance between a and INT32_MAX is less than b, we have an overflow.
    // if(a>0 && b>0){
    //     int32_t distance_to_max = INT32_MAX - a;
    //     if(distance_to_max < b){
    //         int32_t remainder = b - distance_to_max;
    //         return (int64_t)INT32_MAX + (int64_t)remainder;
    //         // The total sum is 
    //         // INT32_MAX + (b - (INT32_MAX - a)) 
    //         // = INT32_MAX + b - INT32_MAX + a 
    //         // = a + b.
    //     }
    // }
    // // If a and b are both negative and their sum is less than INT32_MIN, we have an overflow.
    // if(a<0 && b<0){
    //     int32_t distance_to_min = INT32_MIN - a; // this is negative
    //     if(distance_to_min > b){ 
    //         // what I really mean is the absolute value of distance_to_min is less than the absolute value of b, 
    //         // but since both are negative, we can just compare them directly.
    //         int32_t remainder = b - distance_to_min;
    //         return (int64_t)INT32_MIN + (int64_t)remainder;
    //         // The total sum is 
    //         // INT32_MIN + (b - (a - INT32_MIN)) 
    //         // = INT32_MIN + b - a + INT32_MIN 
    //         // = a + b.
    //     }
    // }
    // // These two conditionals are very similar, 
    // // but combineing them will make the logic more complicated and less readable.

    // return (int64_t)(a + b);
}
