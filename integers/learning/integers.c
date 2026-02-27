#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define DEBUG 1

void print_binary(uint32_t n) {
    int started = 0;
    for (int i = (int)(sizeof(n) * 8) - 1; i >= 0; i--) {
        uint32_t bit = (n >> i) & 1U;
        if (bit) started = 1;
        if (started || i == 0) putchar(bit ? '1' : '0');
    }
    printf("\n");
}

uint32_t masking(uint8_t first, uint8_t last){
    uint32_t initial_mask = UINT32_MAX;
    uint32_t left_mask = initial_mask << first;
    last = last + 1;
    uint8_t last_shift_one = last / 2;
    uint8_t last_shift_two = last - last_shift_one;
    uint32_t right_mask = initial_mask << last_shift_one;
    right_mask = right_mask << last_shift_two;

    #if DEBUG == 1
        printf("initial_mask: ");
        print_binary(initial_mask);
        printf("left_mask: ");
        print_binary(left_mask);
        printf("right_mask: ");
        print_binary(right_mask);
    #endif

    return left_mask ^ right_mask;
}

uint32_t logical_negation(uint32_t x){
    return x ^ (uint32_t)1;
}

uint64_t handle_overflow(uint32_t a, uint32_t b){
    uint32_t remainder = a + b;
    if (remainder < a || remainder < b){
        return (uint64_t)UINT32_MAX + 1 + remainder;
    }
    return remainder;
}

int main(void) {
    print_binary(masking(3, 5));
    print_binary(masking(0, 30));
    print_binary(masking(0, 31));

    printf("%u\n", masking(0, 30));

    printf("%u\n", logical_negation(0));

    print_binary(logical_negation(0));

    printf("%u\n", UINT32_MAX);
    printf("%llu\n", handle_overflow(UINT32_MAX, 1));

    return 0;
}
