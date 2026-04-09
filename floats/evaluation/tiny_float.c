#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "tiny_float.h"
#define DEBUG 1

// tiny_float is an 8-bit floating point representation with 1 sign bit, 4 exponent bits, and 3 significand bits.

void print_binary(uint8_t n) {
    for (int i = 7; i >= 0; i--) {
        putchar(((n >> i) & 1U) ? '1' : '0');
        if (i % 4 == 0 && i != 0) putchar(' ');
    }
    printf("\n");
}

bool get_sign_bit(uint8_t tiny_float){
    return (tiny_float >> 7) & 1;
}

uint8_t get_exponent_bits(uint8_t tiny_float){
    return (tiny_float >> 3) & 0b1111;
}

uint8_t get_significand_bits(uint8_t tiny_float){
    return tiny_float & 0b111;
}

uint8_t set_sign_bit(uint8_t tiny_float, bool sign_bit){
    if (sign_bit){
        return (tiny_float & 0b01111111) | (1U << 7);
    }
    return (tiny_float & 0b01111111) & ~(1U << 7);
}

uint8_t set_exponent_bits(uint8_t tiny_float, uint8_t exponent_bits){
    if (exponent_bits > 0b1111){
        #if DEBUG == 1
            printf("set_exponent_bits failed. exponent_bits is greater than 0b1111.\n");
        #endif
        return tiny_float;
    }
    return (uint8_t)((tiny_float & 0b10001111) | (exponent_bits << 3));
}

uint8_t set_significand_bits(uint8_t tiny_float, uint8_t significand_bits){
    if (significand_bits > 0b111){
        #if DEBUG == 1
            printf("set_significand_bits failed. significand_bits is greater than 0b111.\n");
        #endif
        return tiny_float;
    }
    return (tiny_float & 0b11111000) | significand_bits;
}

encoding_t find_encoding_type(uint8_t tf_bits){
    uint8_t exponent_bits = get_exponent_bits(tf_bits);
    uint8_t significand_bits = get_significand_bits(tf_bits);
    if( exponent_bits == 0b1111){ // infinity or NaN
        if (significand_bits == 0){
            return TF_INFTY;
        }
        return TF_NAN;
    } else if(exponent_bits == 0){ // zero or denormalized
        if(significand_bits == 0) {
            return ZERO;       
        }
        return DENORMALIZED;
    }
    return NORMALIZED;
}

int8_t decode_exponent(uint8_t tf_bits){
    // returns the exponent value as a signed integer.

    uint8_t exponent_bits = get_exponent_bits(tf_bits);

    // the exponent encoding has 4 bits, so the bias is 2^(4-1) - 1 = 7
    encoding_t encoding = find_encoding_type(tf_bits);
    if (encoding == TF_INFTY || encoding == TF_NAN){
        #if DEBUG == 1
            printf("decode_exponent failed. tiny_float is special.\n");
        #endif
        return 0;
    } else if (encoding == DENORMALIZED || encoding == ZERO){
        // For denormalized numbers, the exponent value is always 1-7 = -6
        return -6;
    } else {
        // For normalized numbers, the exponent value is the exponent bits minus the bias
        return (int8_t)exponent_bits - 7; // bias of 7
    }
}

uint8_t decode_significand(uint8_t tf_bits){
    // returns the significand value as an integer with the implicit leading 1 for normalized numbers
    uint8_t exponent_bits = get_exponent_bits(tf_bits);
    uint8_t significand_bits = get_significand_bits(tf_bits);
    // Returns 4-bit integer: implicit bit prepended
    if (exponent_bits == 0) return significand_bits;          // denorm: 0.mmm -> 0mmm
    return (1 << 3) | significand_bits;                  // norm:   1.mmm -> 1mmm
}

// Don't need this code since we have the find_encoding_type function, but keeping it here just in case.
// bool is_nan(uint8_t tiny_float){
//     uint8_t significand_bits = get_significand_bits(tiny_float);
//     uint8_t exponent_bits = get_exponent_bits(tiny_float);

//     encoding_t encoding = find_encoding_type(exponent_bits);
    
//     return (encoding == SPECIAL) && (significand_bits != 0);
// }

// bool is_infinity(uint8_t tiny_float){
//     uint8_t significand_bits = get_significand_bits(tiny_float);
//     uint8_t exponent_bits = get_exponent_bits(tiny_float);

//     encoding_t encoding = find_encoding_type(exponent_bits);
    
//     return (encoding == SPECIAL) && (significand_bits == 0);
// }

const uint8_t NAN_VAL = 0b01111001; // exponent bits are 0b1111 and significand bits are not 0
const uint8_t POS_INF = 0b01111000; // exponent bits are 0b1111 and significand bits are 0
const uint8_t NEG_INF = 0b11111000; // exponent bits are 0b1111 and significand bits are 0
// const uint8_t POS_ZERO = 0b00000000; // exponent bits are 0b1111 and significand bits are 0
// const uint8_t NEG_ZERO = 0b10000000; // exponent bits are 0b1111 and significand bits are 0

// Using a struct might violate the requirement
// typedef struct tiny_float_t {
//     uint8_t representation;
//     bool sign_bit;
//     uint8_t exponent_bits;
//     uint8_t significand_bits;
//     int8_t exponent_value;
//     int16_t significand_value;
//     encoding_t encoding;
// } tiny_float_t;

// This function is from the learning homework
// Rounds the value to the nearest even number, rounding the number_of_bits least significant bits. 
// The bit at position number_of_bits is the last bit to keep, and the bits below it are the bits to round.
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

uint8_t pack(bool sign_bit, uint8_t exponent_bits, uint8_t significand_bits){
    uint8_t tiny_float = 0;
    tiny_float = set_sign_bit(tiny_float, sign_bit);
    tiny_float = set_exponent_bits(tiny_float, exponent_bits);
    tiny_float = set_significand_bits(tiny_float, significand_bits);
    return tiny_float;
}

uint8_t normalize_and_pack(bool sign, int16_t exponent, uint32_t significand) {
    // Handle zero
    if (significand == 0){
        return pack(sign, 0, 0); // zero encoding
    }
    // Shift significand until it's of the form 1.mmm
    // Left align the significand so that the leading 1 is in bit 30, and adjust the exponent accordingly. 
    // bit: 31 30 29 28 27 ... 0
    //      0  1  m  m  m  ... 0
    uint32_t leading_one_mask = 1U << 30;
    while ((significand & leading_one_mask) == 0){
        significand <<= 1;
        exponent--;
    }

    // For final_exponent, the left most bit of the significand represents 2^0 instead of 2^30
    int16_t final_exponent = exponent + 30;

    // we only have 3 bits for the significand
    // bit: 31 30 29 28 27 ... 0
    //      0  1  m  m  m  ... 0
    uint32_t significand_mask = 0b111U << 27; 

    // Check for underflow → try denorm, or return ±0
    // The smallest exponent we can represent is 1 - bias(7) = -6, 
    // so if the exponent is less than -6, we have underflow.
    if (final_exponent < -6){
        // We can try to represent it as a denormalized number by shifting the significand to the right and increasing the exponent until the exponent is -6.
        int16_t shift_amount = (int16_t)(-6 - final_exponent);
        if (shift_amount < 0 || shift_amount >= 32){
            // this prevents us from shifting more than the size of the significand.
            return pack(sign, 0, 0); // zero encoding
        }
        // Now we have a denormalized number with an exponent of -6
        significand >>= (uint8_t)shift_amount;
        // bit: 31 30 29 28 27 ... 0
        //      0  ?  m  m  m [... ] round 27 bits
        significand = round_to_nearest_even(significand, 27);
        if (significand & leading_one_mask){
            // if the rounding caused the significand to become normalized, 
            // we will return the smallest normalized number instead of the denormalized number.
            return pack(sign, 0b0001, 0); // smallest normalized encoding
        }
        return pack(sign, 0, (uint8_t)((significand & significand_mask) >> 27)); // denorm encoding
    }

    // Normalized numbers
    // Round to nearest even
    // Shift the significand to the right by 1 to make space in case of overflow from rounding
    // bit: 31 30 29 28 27 26 ... 0
    //      0  0  1  m  m  m  ... 0    round 26 bits
    significand >>= 1;
    final_exponent++; // compensate for the shift
    
    significand = round_to_nearest_even(significand, 26);
    if ((significand & leading_one_mask) == 0){ 
        // shift it back when there is no overflow from rounding, and adjust the exponent accordingly.
        significand <<= 1;
        final_exponent--;
    }

    // The largest exponent we can represent is 0b1110 - bias(7) = 7,
    if (final_exponent > 7){
        // Overflow to infinity
        return pack(sign, 0b1111, 0); // infinity encoding
    }

    // Pack the sign, exponent, and significand into the tiny float format.
    return pack(sign, (uint8_t)(final_exponent + 7), (uint8_t)((significand & significand_mask) >> 27)); // normalized encoding
}

uint8_t add_tiny_floats(uint8_t tf1, uint8_t tf2){
    encoding_t enc1 = find_encoding_type(tf1);
    encoding_t enc2 = find_encoding_type(tf2);

    if (enc1 == TF_NAN || enc2 == TF_NAN){
        // If either is NaN, return NaN
        return NAN_VAL;
    }
    if (enc1 == TF_INFTY){
        if (enc2 == TF_INFTY){
            // If both are infinity, check their sign bits
            if (get_sign_bit(tf1) == get_sign_bit(tf2)){
                // If both have the same sign bit, return infinity with that sign
                return get_sign_bit(tf1) ? NEG_INF : POS_INF;
            }
            // If they have different sign bits, return NaN
            return NAN_VAL;
        }
        return tf1; // If only tf1 is SPECIAL, return tf1
    } else if (enc2 == TF_INFTY){
        return tf2; // If only tf2 is SPECIAL, return tf2
    }
    
    // Handle addition for normalized and denormalized numbers 
    uint32_t mag1 = decode_significand(tf1);
    uint32_t mag2 = decode_significand(tf2);
    int16_t exp1 = decode_exponent(tf1) - 3;
    int16_t exp2 = decode_exponent(tf2) - 3;

    // Align unsigned
    int16_t exp_diff = exp1 - exp2;
    int16_t result_exp;
    if (exp_diff > 0) {
        mag1 <<= exp_diff;
        result_exp = exp2;
    } else {
        mag2 <<= -exp_diff;
        result_exp = exp1;
    }

    // Apply signs and add
    int32_t sig1 = get_sign_bit(tf1) ? -(int32_t)mag1 : (int32_t)mag1;
    int32_t sig2 = get_sign_bit(tf2) ? -(int32_t)mag2 : (int32_t)mag2;
    int32_t result_sig = sig1 + sig2;

    bool result_sign = result_sig < 0;
    uint32_t result_mag;
    if (result_sign){
        result_mag = (uint32_t)(-result_sig);
    } else {
        result_mag = (uint32_t)result_sig;
    }

    return normalize_and_pack(result_sign, result_exp, result_mag);
}

uint8_t multiply_tiny_floats(uint8_t tf1, uint8_t tf2){
    encoding_t enc1 = find_encoding_type(tf1);
    encoding_t enc2 = find_encoding_type(tf2);

    if (enc1 == TF_NAN || enc2 == TF_NAN){
        // If either is NaN, return NaN
        return NAN_VAL;
    }
    if (enc1 == TF_INFTY){
        if (enc2 == TF_INFTY){
            // If both are infinity, check their sign bits
            bool sign = get_sign_bit(tf1) ^ get_sign_bit(tf2);
            return sign ? NEG_INF : POS_INF;
        } else if (enc2 == ZERO){
            // If tf1 is infinity and tf2 is zero, return NaN
            return NAN_VAL;
        }
        // If only tf1 is infinity, return infinity with the appropriate sign
        bool sign = get_sign_bit(tf1) ^ get_sign_bit(tf2);
        return sign ? NEG_INF : POS_INF;
    } else if (enc2 == TF_INFTY){
        if (enc1 == ZERO){
            // If tf2 is infinity and tf1 is zero, return NaN
            return NAN_VAL;
        }
        // If only tf2 is infinity, return infinity with the appropriate sign
        bool sign = get_sign_bit(tf1) ^ get_sign_bit(tf2);
        return sign ? NEG_INF : POS_INF;
    }
    
    // Handle multiplication for normalized and denormalized numbers 
    uint32_t result_significand = decode_significand(tf1) * decode_significand(tf2);
    // The result exponent is the sum of the exponents.
    // We subtract 6 from it since each exponent is shifted left by 3 when we decode it.
    int16_t result_exponent = decode_exponent(tf1) + decode_exponent(tf2) - 6;
    bool result_sign = get_sign_bit(tf1) ^ get_sign_bit(tf2);
    return normalize_and_pack(result_sign, result_exponent, result_significand);
}

float tiny_float_to_float(uint8_t tiny_float){
    bool sign_bit = get_sign_bit(tiny_float);
    uint8_t exponent_bits = get_exponent_bits(tiny_float);
    uint8_t significand_bits = get_significand_bits(tiny_float);

    // deternine the encoding type of the tiny float
    encoding_t encoding = find_encoding_type(tiny_float);
    int16_t exponent = 0;
    float significand = 0.0f;
    if(encoding == TF_INFTY){
        return sign_bit == 0 ? INFINITY : -INFINITY;
    } else if (encoding == TF_NAN){
        return NAN;
    } else if (encoding == ZERO){
        return sign_bit == 0 ? 0.0f : -0.0f;
    } else if (encoding == DENORMALIZED){
        // Means our exponent is actually 1 - bias, and we don't have the implicit leading 1 in the significand
        exponent = 1 - 7; // bias of 7
        significand = (float)significand_bits / 8.0f; // 3 bits of significand, so divide by 2^3 = 8
    } else{
        exponent = (int16_t)exponent_bits - 7; // bias of 7
        significand = 1.0f + (float)significand_bits / 8.0f; // 3 bits of significand, so divide by 2^3 = 8
    }

    float value = significand * powf(2.0f, exponent);
    if (sign_bit){
        value = -value;
    }

    return value;
}

void print_tiny_float(uint8_t value){
    float float_value = tiny_float_to_float(value);
    printf("tiny_float value: %f\n", float_value);
    #if DEBUG == 1
        bool sign_bit = get_sign_bit(value);
        uint8_t exponent_bits = get_exponent_bits(value);
        uint8_t significand_bits = get_significand_bits(value);
        printf("sign: %d, exponent: %u, significand: %u\n", (int)sign_bit, exponent_bits, significand_bits);
    #endif
}
