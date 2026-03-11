#include <stdio.h>
#include <stdlib.h>
#include "integers.h"

int main(void) {
    printf("Testing conditional function:\n");
    printf("%d\n", conditional(0, 1, 2));       // x=0 → return z=2
    printf("%d\n", conditional(1, 1, 2));       // x=1 → return y=1
    printf("%d\n", conditional(-1, 1, 2));      // x=-1 → return y=1
    printf("%d\n", conditional(INT32_MIN, 1, 2)); // x=INT32_MIN → return y=1
    printf("%d\n", conditional(INT32_MAX, 1, 2)); // x=INT32_MAX → return y=1
    printf("%d\n", conditional(0, -5, -10));    // x=0, negative y/z → return z=-10
    printf("%d\n", conditional(1, -5, -10));    // x=1, negative y/z → return y=-5
    printf("%d\n", conditional(0, 7, 7));       // x=0, y==z → return 7

    printf("%d\n", INT32_MAX);

    printf("%d\n", conditional(0, INT32_MAX, INT32_MAX-1));
    printf("%d\n", conditional(13, INT32_MAX, INT32_MAX-1));

    printf("\nTesting negate function:\n");
    printf("%d\n", negate(0));
    printf("%d\n", negate(1));
    printf("%d\n", negate(-1));
    printf("%d\n", negate(INT32_MAX));
    printf("%d\n", negate(INT32_MIN));

    printf("\nTesting handle_overflow function:\n");

    // Both positive, overflow
    printf("%d\n", INT32_MAX);
    printf("%lld\n", handle_overflow(INT32_MAX, 1));
    printf("%lld\n", handle_overflow(INT32_MAX, INT32_MAX));

    // Both negative, overflow
    printf("%d\n", INT32_MIN);
    printf("%lld\n", handle_overflow(INT32_MIN, -1));
    printf("%lld\n", handle_overflow(INT32_MIN, INT32_MIN));

    // Both positive, no overflow
    printf("%lld\n", handle_overflow(5, 10));
    printf("%lld\n", handle_overflow(1, 1));

    // Both negative, no overflow
    printf("%lld\n", handle_overflow(-5, -10));
    printf("%lld\n", handle_overflow(-1, -1));

    // Mixed positive and negative
    printf("%lld\n", handle_overflow(INT32_MAX, -1));
    printf("%lld\n", handle_overflow(INT32_MIN, 1));
    printf("%lld\n", handle_overflow(INT32_MAX, INT32_MIN));
    printf("%lld\n", handle_overflow(INT32_MIN, INT32_MAX));
    printf("%lld\n", handle_overflow(100, -50));
    printf("%lld\n", handle_overflow(-100, 50));

    // Zero cases
    printf("%lld\n", handle_overflow(0, 0));
    printf("%lld\n", handle_overflow(0, INT32_MAX));
    printf("%lld\n", handle_overflow(INT32_MIN, 0));

    return 0;
}
