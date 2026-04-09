#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "tiny_float.h"

static int tests_run = 0;
static int tests_failed = 0;

static void to_binary_string_u8(uint8_t value, char out[10]) {
	out[0] = ((value >> 7) & 1U) ? '1' : '0';
	out[1] = ((value >> 6) & 1U) ? '1' : '0';
	out[2] = ((value >> 5) & 1U) ? '1' : '0';
	out[3] = ((value >> 4) & 1U) ? '1' : '0';
	out[4] = ' ';
	out[5] = ((value >> 3) & 1U) ? '1' : '0';
	out[6] = ((value >> 2) & 1U) ? '1' : '0';
	out[7] = ((value >> 1) & 1U) ? '1' : '0';
	out[8] = (value & 1U) ? '1' : '0';
	out[9] = '\0';
}

static const char *encoding_name(encoding_t value) {
	switch (value) {
		case ZERO:
			return "ZERO";
		case DENORMALIZED:
			return "DENORMALIZED";
		case NORMALIZED:
			return "NORMALIZED";
		case TF_INFTY:
			return "TF_INFTY";
		case TF_NAN:
			return "TF_NAN";
		default:
			return "UNKNOWN";
	}
}

static void print_u8_test(const char *label, uint8_t expected, uint8_t actual) {
	tests_run++;
	const char *pass = (expected == actual) ? "Yes" : "No";
	if (expected != actual) {
		tests_failed++;
	}
	char expected_binary[10];
	char actual_binary[10];
	to_binary_string_u8(expected, expected_binary);
	to_binary_string_u8(actual, actual_binary);
	printf("%-46s | expected: %s | actual: %s | pass: %s\n", label, expected_binary, actual_binary, pass);
}

static void tf_value_string(uint8_t value, char out[32]) {
	float converted = tiny_float_to_float(value);
	if (isnan(converted)) {
		snprintf(out, 32, "NaN");
		return;
	}
	if (isinf(converted)) {
		snprintf(out, 32, "%sinf", converted < 0.0f ? "-" : "+");
		return;
	}
	snprintf(out, 32, "%.9f", converted);
}

static void print_tf_test(const char *label, uint8_t expected, uint8_t actual) {
	tests_run++;
	const char *pass = (expected == actual) ? "Yes" : "No";
	if (expected != actual) {
		tests_failed++;
	}
	char expected_binary[10];
	char actual_binary[10];
	char expected_value[32];
	char actual_value[32];
	to_binary_string_u8(expected, expected_binary);
	to_binary_string_u8(actual, actual_binary);
	tf_value_string(expected, expected_value);
	tf_value_string(actual, actual_value);
	printf("%-46s | expected: %s (%s) | actual: %s (%s) | pass: %s\n",
	       label,
	       expected_binary,
	       expected_value,
	       actual_binary,
	       actual_value,
	       pass);
}

static void print_i8_test(const char *label, int8_t expected, int8_t actual) {
	tests_run++;
	const char *pass = (expected == actual) ? "Yes" : "No";
	if (expected != actual) {
		tests_failed++;
	}
	printf("%-46s | expected: %d | actual: %d | pass: %s\n", label, expected, actual, pass);
}

static void print_bool_test(const char *label, bool expected, bool actual) {
	tests_run++;
	const char *pass = (expected == actual) ? "Yes" : "No";
	if (expected != actual) {
		tests_failed++;
	}
	printf("%-46s | expected: %s | actual: %s | pass: %s\n",
	       label,
	       expected ? "true" : "false",
	       actual ? "true" : "false",
	       pass);
}

static void print_float_test(const char *label, float expected, float actual) {
	tests_run++;
	bool equal = fabsf(expected - actual) <= 1e-7f;
	const char *pass = equal ? "Yes" : "No";
	if (!equal) {
		tests_failed++;
	}
	printf("%-46s | expected: %.9f | actual: %.9f | pass: %s\n", label, expected, actual, pass);
}

static void print_inf_test(const char *label, bool expected_positive_inf, float actual) {
	tests_run++;
	bool actual_positive_inf = isinf(actual) && actual > 0;
	const char *pass = (expected_positive_inf == actual_positive_inf) ? "Yes" : "No";
	if (expected_positive_inf != actual_positive_inf) {
		tests_failed++;
	}
	printf("%-46s | expected: +inf | actual: %s | pass: %s\n",
	       label,
	       actual_positive_inf ? "+inf" : "not +inf",
	       pass);
}

static void print_nan_test(const char *label, float actual) {
	tests_run++;
	bool actual_nan = isnan(actual);
	const char *pass = actual_nan ? "Yes" : "No";
	if (!actual_nan) {
		tests_failed++;
	}
	printf("%-46s | expected: NaN | actual: %s | pass: %s\n", label, actual_nan ? "NaN" : "not NaN", pass);
}

static void print_encoding_test(const char *label, encoding_t expected, encoding_t actual) {
	tests_run++;
	const char *pass = (expected == actual) ? "Yes" : "No";
	if (expected != actual) {
		tests_failed++;
	}
	printf("%-46s | expected: %s | actual: %s | pass: %s\n",
	       label,
	       encoding_name(expected),
	       encoding_name(actual),
	       pass);
}

int main(void) {
	printf("Testing getter/setter helper functions:\n");
	uint8_t value = 0;
	value = set_sign_bit(value, true);
	value = set_exponent_bits(value, 0b1010);
	value = set_significand_bits(value, 0b101);

	print_u8_test("setters build packed value", 0xD5, value);
	print_bool_test("get_sign_bit", true, get_sign_bit(value));
	print_u8_test("get_exponent_bits", 0b1010, get_exponent_bits(value));
	print_u8_test("get_significand_bits", 0b101, get_significand_bits(value));

	print_u8_test("set_exponent_bits invalid input unchanged", 0x55, set_exponent_bits(0x55, 0b10000));
	print_u8_test("set_significand_bits invalid input unchanged", 0xAA, set_significand_bits(0xAA, 0b1000));

	printf("\nTesting encoding/decode helper functions:\n");
	print_encoding_test("find_encoding_type(0x00)", ZERO, find_encoding_type(0x00));
	print_encoding_test("find_encoding_type(0x80)", ZERO, find_encoding_type(0x80));
	print_encoding_test("find_encoding_type(0x01)", DENORMALIZED, find_encoding_type(0x01));
	print_encoding_test("find_encoding_type(0x08)", NORMALIZED, find_encoding_type(0x08));
	print_encoding_test("find_encoding_type(0x77)", NORMALIZED, find_encoding_type(0x77));
	print_encoding_test("find_encoding_type(0x78)", TF_INFTY, find_encoding_type(0x78));
	print_encoding_test("find_encoding_type(0x7F)", TF_NAN, find_encoding_type(0x7F));
	print_encoding_test("find_encoding_type(0x79)", TF_NAN, find_encoding_type(0x79));

	print_i8_test("decode_exponent normalized", 2, decode_exponent(0x48));
	print_i8_test("decode_exponent denormal", -6, decode_exponent(0x03));
	print_i8_test("decode_exponent zero", -6, decode_exponent(0x00));

	print_u8_test("decode_significand normalized", 10, decode_significand(0x4A));
	print_u8_test("decode_significand denormal", 2, decode_significand(0x02));

	printf("\nTesting create/convert helper functions:\n");
	print_tf_test("pack bits", 0x9D, pack(true, 0b0011, 0b101));

	print_float_test("tiny_float_to_float(0x00)", 0.0f, tiny_float_to_float(0x00));
	print_bool_test("tiny_float_to_float(0x80) keeps -0 sign", true, signbit(tiny_float_to_float(0x80)) != 0);
	print_float_test("tiny_float_to_float(0x01)", 1.0f / 512.0f, tiny_float_to_float(0x01));
	print_float_test("tiny_float_to_float(0x07)", 7.0f / 512.0f, tiny_float_to_float(0x07));
	print_float_test("tiny_float_to_float(0x08)", 1.0f / 64.0f, tiny_float_to_float(0x08));
	print_float_test("tiny_float_to_float(0x38)", 1.0f, tiny_float_to_float(0x38));
	print_float_test("tiny_float_to_float(0x3C)", 1.5f, tiny_float_to_float(0x3C));
	print_float_test("tiny_float_to_float(0x77)", 240.0f, tiny_float_to_float(0x77));
	print_inf_test("tiny_float_to_float(0x78)", true, tiny_float_to_float(0x78));
	print_bool_test("tiny_float_to_float(0xF8) is -inf", true, isinf(tiny_float_to_float(0xF8)) && tiny_float_to_float(0xF8) < 0.0f);
	print_nan_test("tiny_float_to_float(0x79)", tiny_float_to_float(0x79));

	printf("\nTesting normalize_and_pack:\n");
	print_tf_test("normalize_and_pack zero -> +0", 0x00, normalize_and_pack(false, 0, 0));
	print_tf_test("normalize_and_pack zero -> -0", 0x80, normalize_and_pack(true, 0, 0));
	print_tf_test("normalize_and_pack finite normalized", 0x70, normalize_and_pack(false, -8, 0x8000));
	print_tf_test("normalize_and_pack largest finite", 0x77, normalize_and_pack(false, -8, 0xF000));
	print_tf_test("normalize_and_pack smallest normalized", 0x08, normalize_and_pack(false, -21, 0x8000));
	print_tf_test("normalize_and_pack overflow -> +inf", 0x78, normalize_and_pack(false, -7, 0x8000));
	print_tf_test("normalize_and_pack overflow -> -inf", 0xF8, normalize_and_pack(true, -7, 0x8000));
	print_tf_test("normalize_and_pack underflow -> denorm", 0x04, normalize_and_pack(false, -22, 0x8000));
	print_tf_test("normalize_and_pack largest denorm", 0x07, normalize_and_pack(false, -22, 0xE000));
	print_tf_test("normalize_and_pack denorm rounds to min norm", 0x08, normalize_and_pack(false, -22, 0xF000));
	print_tf_test("normalize_and_pack underflow -> -0", 0x80, normalize_and_pack(true, -40, 0x8000));

	printf("\nTesting add_tiny_floats:\n");
	// Equivalence class: finite + finite (exact representable)
	print_tf_test("add: 1.0 + 0.5", 0x3C, add_tiny_floats(0x38, 0x30));
	print_tf_test("add: 0.5 + 1.0 (commutative)", 0x3C, add_tiny_floats(0x30, 0x38));
	print_tf_test("add: 1.5 + (-1.0)", 0x30, add_tiny_floats(0x3C, 0xB8));

	// Boundary: cancellation and zero behavior
	print_tf_test("add: 1.0 + (-1.0)", 0x00, add_tiny_floats(0x38, 0xB8));
	print_tf_test("add: min denorm + (-min denorm)", 0x00, add_tiny_floats(0x01, 0x81));
	print_tf_test("add: +0 + 1.0", 0x38, add_tiny_floats(0x00, 0x38));
	print_tf_test("add: -0 + 1.0", 0x38, add_tiny_floats(0x80, 0x38));

	// Boundary: denormal/normal edge transitions
	print_tf_test("add: min denorm + min denorm", 0x02, add_tiny_floats(0x01, 0x01));
	print_tf_test("add: max denorm + min denorm -> min norm", 0x08, add_tiny_floats(0x07, 0x01));
	print_tf_test("add: min norm + (-max denorm)", 0x01, add_tiny_floats(0x08, 0x87));

	// Boundary: exponent-gap and overflow
	print_tf_test("add: max finite + min denorm", 0x77, add_tiny_floats(0x77, 0x01));
	print_tf_test("add: max finite + (-min denorm)", 0x77, add_tiny_floats(0x77, 0x81));
	print_tf_test("add: max finite + max finite -> +inf", 0x78, add_tiny_floats(0x77, 0x77));
	print_tf_test("add: -max finite + -max finite -> -inf", 0xF8, add_tiny_floats(0xF7, 0xF7));

	// Control flow: special-value branches
	print_tf_test("add: +inf + finite -> +inf", 0x78, add_tiny_floats(0x78, 0x38));
	print_tf_test("add: -inf + finite -> -inf", 0xF8, add_tiny_floats(0xF8, 0x38));
	print_tf_test("add: -inf + -inf -> -inf", 0xF8, add_tiny_floats(0xF8, 0xF8));
	print_tf_test("add: +inf + -inf -> NaN", 0x79, add_tiny_floats(0x78, 0xF8));
	print_tf_test("add: NaN + 1.0 -> NaN", 0x79, add_tiny_floats(0x79, 0x38));
	print_tf_test("add: 1.0 + NaN -> NaN", 0x79, add_tiny_floats(0x38, 0x79));

	printf("\nTesting multiply_tiny_floats:\n");
	// Equivalence class: finite * finite (exact representable)
	print_tf_test("mul: 1.5 * 2.0", 0x44, multiply_tiny_floats(0x3C, 0x40));
	print_tf_test("mul: 2.0 * 1.5 (commutative)", 0x44, multiply_tiny_floats(0x40, 0x3C));
	print_tf_test("mul: (-1.0) * (-1.0)", 0x38, multiply_tiny_floats(0xB8, 0xB8));
	print_tf_test("mul: 2.0 * 0.5", 0x38, multiply_tiny_floats(0x40, 0x30));

	// Boundary: denormal and underflow edges
	print_tf_test("mul: min denorm * 1.0", 0x01, multiply_tiny_floats(0x01, 0x38));
	print_tf_test("mul: max denorm * 1.0", 0x07, multiply_tiny_floats(0x07, 0x38));
	print_tf_test("mul: min norm * min norm -> +0", 0x00, multiply_tiny_floats(0x08, 0x08));
	print_tf_test("mul: min denorm * min denorm -> +0", 0x00, multiply_tiny_floats(0x01, 0x01));
	print_tf_test("mul: max finite * min denorm", 0x2F, multiply_tiny_floats(0x77, 0x01));

	// Boundary: overflow
	print_tf_test("mul: max finite * 2.0 -> +inf", 0x78, multiply_tiny_floats(0x77, 0x40));
	print_tf_test("mul: +inf * (-2.0) -> -inf", 0xF8, multiply_tiny_floats(0x78, 0xC0));
	print_tf_test("mul: -inf * (-2.0) -> +inf", 0x78, multiply_tiny_floats(0xF8, 0xC0));

	// Control flow: special-value branches
	print_tf_test("mul: +inf * +inf -> +inf", 0x78, multiply_tiny_floats(0x78, 0x78));
	print_tf_test("mul: +inf * -inf -> -inf", 0xF8, multiply_tiny_floats(0x78, 0xF8));
	print_tf_test("mul: +inf * finite -> +inf", 0x78, multiply_tiny_floats(0x78, 0x38));
	print_tf_test("mul: +inf * 0 -> NaN", 0x79, multiply_tiny_floats(0x78, 0x00));
	print_tf_test("mul: -inf * -0 -> NaN", 0x79, multiply_tiny_floats(0xF8, 0x80));
	print_tf_test("mul: NaN * 1.0 -> NaN", 0x79, multiply_tiny_floats(0x79, 0x38));
	print_tf_test("mul: max finite * max finite -> +inf", 0x78, multiply_tiny_floats(0x77, 0x77));

	printf("\nSummary: %d run, %d failed.\n", tests_run, tests_failed);
	return (tests_failed == 0) ? 0 : 1;
}
