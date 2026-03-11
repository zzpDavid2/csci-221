#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 1

typedef enum encoding_t {
    NORMALIZED,
    DENORMALIZED,
    SPECIAL
} encoding_t;

void print_binary(uint32_t n) {
    for (int i = 31; i >= 0; i--) {
        putchar(((n >> i) & 1U) ? '1' : '0');
        if (i % 4 == 0 && i != 0) putchar(' ');
    }
    printf("\n");
}

uint32_t mask(uint8_t first, uint8_t last){
    uint32_t left_mask = UINT32_MAX << first;
    uint32_t right_mask = UINT32_MAX >> (31 - last);
    uint32_t result = left_mask & right_mask;

    #if DEBUG == 1
        printf("left_mask:  ");
        print_binary(left_mask);
        printf("right_mask: ");
        print_binary(right_mask);
        printf("result:     ");
        print_binary(result);
    #endif

    return result;
}

encoding_t find_encoding_type(float f){
    // use memcpy to interpret the bits of the float as an unsigned integer
    uint32_t bits;
    memcpy(&bits, &f, sizeof(bits));
    
    uint32_t exponent_mask = mask(23, 30);
    uint32_t exponent_bits = bits & exponent_mask;

    if(exponent_bits == exponent_mask){ // infinity or NaN
        return SPECIAL;
    } else if(exponent_bits == 0){ // zero or denormalized
        return DENORMALIZED;
    } else {
        return NORMALIZED;
    }
}

uint32_t round_to_nearest_even(uint32_t value, uint32_t number_of_bits){
    if(number_of_bits >= 32){
        #if DEBUG == 1
            printf("round_to_nearest_even failed. number_of_bits is greater than or equal to 32.\n");
        #endif
        return value;
    }
    if(number_of_bits == 0){
        return value;
    }
    // this puts a 1 on the last bit to keep.
    uint32_t last_bit_mask = 1U << number_of_bits;

    // this is the number that will be used to determine whether to round up or down.
    uint32_t round_bit = last_bit_mask >> 1;

    uint32_t bits_to_round_mask = last_bit_mask - 1;
    uint32_t bits_to_round = value & bits_to_round_mask;

    value = value & ~bits_to_round_mask; // clear the bits to round

    // if the bits to round is greater than half of the last bit, we round up.
    if(bits_to_round > round_bit){
        value += last_bit_mask;
    } else if (bits_to_round == round_bit){
        // this is the tie-breaking case.
        // If the bits to round is exactly half of the last bit, we round to the nearest even number.
        if(value & last_bit_mask){ // if the last bit is 1, we round up to make it even.
            value += last_bit_mask;
        }
        // if the last bit is 0, we round down to keep it even, so we do nothing.
    }
    return value; 
}

int main(void) {
    // ===== Test mask =====
    printf("===== mask tests =====\n");
    printf("mask(3, 5): \n");
    print_binary(mask(3, 5));   // bits 3-5 → 0b111000 = 56
    printf("Expected:   111000\n\n");

    printf("mask(0, 30): \n");
    print_binary(mask(0, 30));  // bits 0-30 → 0x7FFFFFFF
    printf("Expected:   1111111111111111111111111111111\n\n");

    printf("mask(0, 0): \n");
    print_binary(mask(0, 0));   // just bit 0 → 1
    printf("Expected:   1\n\n");

    printf("mask(31, 31): \n");
    print_binary(mask(31, 31)); // just bit 31 → sign bit
    printf("Expected:   10000000000000000000000000000000\n\n");

    printf("mask(23, 30): \n");
    print_binary(mask(23, 30)); // exponent mask
    printf("Expected:   1111111100000000000000000000000\n\n");

    // ===== Test find_encoding_type =====
    printf("===== find_encoding_type tests =====\n");
    encoding_t enc;

    enc = find_encoding_type(1.0f);
    printf("1.0f → %s (expected NORMALIZED)\n\n",
           enc == NORMALIZED ? "NORMALIZED" : enc == DENORMALIZED ? "DENORMALIZED" : "SPECIAL");

    enc = find_encoding_type(-42.5f);
    printf("-42.5f → %s (expected NORMALIZED)\n\n",
           enc == NORMALIZED ? "NORMALIZED" : enc == DENORMALIZED ? "DENORMALIZED" : "SPECIAL");

    enc = find_encoding_type(0.0f);
    printf("0.0f → %s (expected DENORMALIZED)\n\n",
           enc == NORMALIZED ? "NORMALIZED" : enc == DENORMALIZED ? "DENORMALIZED" : "SPECIAL");

    enc = find_encoding_type(-0.0f);
    printf("-0.0f → %s (expected DENORMALIZED)\n\n",
           enc == NORMALIZED ? "NORMALIZED" : enc == DENORMALIZED ? "DENORMALIZED" : "SPECIAL");

    // smallest denormalized positive float
    uint32_t denorm_bits = 1;
    float denorm;
    memcpy(&denorm, &denorm_bits, sizeof(denorm));
    enc = find_encoding_type(denorm);
    printf("smallest denorm → %s (expected DENORMALIZED)\n\n",
           enc == NORMALIZED ? "NORMALIZED" : enc == DENORMALIZED ? "DENORMALIZED" : "SPECIAL");

    enc = find_encoding_type(INFINITY);
    printf("INFINITY → %s (expected SPECIAL)\n\n",
           enc == NORMALIZED ? "NORMALIZED" : enc == DENORMALIZED ? "DENORMALIZED" : "SPECIAL");

    enc = find_encoding_type(-INFINITY);
    printf("-INFINITY → %s (expected SPECIAL)\n\n",
           enc == NORMALIZED ? "NORMALIZED" : enc == DENORMALIZED ? "DENORMALIZED" : "SPECIAL");

    enc = find_encoding_type(NAN);
    printf("NAN → %s (expected SPECIAL)\n\n",
           enc == NORMALIZED ? "NORMALIZED" : enc == DENORMALIZED ? "DENORMALIZED" : "SPECIAL");

    // ===== Test round_to_nearest_even =====
    printf("===== round_to_nearest_even tests =====\n");

    // Round 0b1011 (11) by 2 bits → truncated portion is 0b11 (3), round_bit = 2
    // 3 > 2, so round up → 0b1100 (12)
    printf("round(11, 2) = %u (expected 12)\n",
           round_to_nearest_even(11, 2));

    // Round 0b1001 (9) by 2 bits → truncated portion is 0b01 (1), round_bit = 2
    // 1 < 2, so round down → 0b1000 (8)
    printf("round(9, 2) = %u (expected 8)\n",
           round_to_nearest_even(9, 2));

    // Tie-breaking: round 0b1010 (10) by 2 bits → truncated = 0b10 (2), round_bit = 2
    // Tie → last kept bit is bit 2 of value-after-clear 8 = 0b1000 → bit 2 is 0 (even), round down → 8
    printf("round(10, 2) = %u (expected 8, tie rounds down to even)\n",
           round_to_nearest_even(10, 2));

    // Tie-breaking: round 0b0110 (6) by 2 bits → truncated = 0b10 (2), round_bit = 2
    // Tie → last kept bit is bit 2 of value-after-clear 4 = 0b0100 → bit 2 is 1 (odd), round up → 8
    printf("round(6, 2) = %u (expected 8, tie rounds up to even)\n",
           round_to_nearest_even(6, 2));

    // Tie-breaking: round 0b0010 (2) by 2 bits → truncated = 0b10 (2), round_bit = 2
    // Tie → last kept bit is bit 2 of 2 = 0b0010 → bit 2 is 0, so round down → 0
    printf("round(2, 2) = %u (expected 0, tie rounds down to even)\n",
           round_to_nearest_even(2, 2));

    // Round 0 → should stay 0
    printf("round(0, 3) = %u (expected 0)\n",
           round_to_nearest_even(0, 3));

    // Round by 0 bits → no change
    printf("round(15, 0) = %u (expected 15)\n",
           round_to_nearest_even(15, 0));

    // Round by 1 bit: 0b11 (3) → truncated = 1, round_bit = 1
    // 1 == 1 → tie → last kept bit (bit 1 of 3 = 0b11) is 1, round up → 4
    printf("round(3, 1) = %u (expected 4, tie rounds up to even)\n",
           round_to_nearest_even(3, 1));

    // Round by 1 bit: 0b01 (1) → truncated = 1, round_bit = 1
    // 1 == 1 → tie → last kept bit (bit 1 of 1 = 0b01) is 0, round down → 0
    printf("round(1, 1) = %u (expected 0, tie rounds down to even)\n",
           round_to_nearest_even(1, 1));

}
