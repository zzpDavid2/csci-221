#ifndef TINY_FLOAT_H
#define TINY_FLOAT_H

#include <stdbool.h>
#include <stdint.h>

typedef enum encoding_t {
	ZERO,
	DENORMALIZED,
	NORMALIZED,
	TF_INFTY,
	TF_NAN
} encoding_t;

void print_binary(uint8_t n);

bool get_sign_bit(uint8_t tiny_float);
uint8_t get_exponent_bits(uint8_t tiny_float);
uint8_t get_significand_bits(uint8_t tiny_float);

uint8_t set_sign_bit(uint8_t tiny_float, bool sign_bit);
uint8_t set_exponent_bits(uint8_t tiny_float, uint8_t exponent_bits);
uint8_t set_significand_bits(uint8_t tiny_float, uint8_t significand_bits);

encoding_t find_encoding_type(uint8_t tf_bits);
int8_t decode_exponent(uint8_t tf_bits);
uint8_t decode_significand(uint8_t tf_bits);

uint8_t add_tiny_floats(uint8_t tf1, uint8_t tf2);
uint8_t multiply_tiny_floats(uint8_t tf1, uint8_t tf2);
uint8_t normalize_and_pack(bool sign, int16_t exponent, uint32_t significand);

uint8_t pack(bool sign_bit, uint8_t exponent_bits, uint8_t significand_bits);
float tiny_float_to_float(uint8_t tiny_float);
void print_tiny_float(uint8_t value);

#endif // TINY_FLOAT_H
