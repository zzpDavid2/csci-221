#ifndef INTEGERS_H
#define INTEGERS_H

#include <stdint.h>

// Negate a signed integer using bitwise operations
int32_t negate(int32_t x);

// If x is nonzero, return y. Otherwise, return z.
int32_t conditional(int32_t x, int32_t y, int32_t z);

// Handle overflow when adding two signed integers.
// If the sum of a and b exceeds the range of int32_t, return the correct result as an int64_t.
int64_t handle_overflow(int32_t a, int32_t b);

#endif // INTEGERS_H
