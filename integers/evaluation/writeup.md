# Integers Evaluation Writeup

## Overview

This project implements three core operations on 32-bit integers: `negate`, `conditional`, and `handle_overflow`. A helper function, `print_binary`, supports debugging by displaying binary representations. I tested the signed integers can also wrap around on a overflow like their unsigned counterparts. However, I opted to cast them into unsigned integers when they can overflow and cast them back afterwards to be safe against UB.

## Function Descriptions

### `negate`

`negate` computes the two's complement negation of a signed 32-bit integer. It works by casting `x` to `uint32_t`, flipping all bits via `~`, and adding 1: $-x = \sim x + 1$. The entire operation is performed in unsigned arithmetic to avoid undefined behavior. When `x` is `INT32_MIN`, `~((uint32_t)INT32_MIN) + 1` produces `INT32_MIN` again — this is the expected result since $-(-2^{31})$ cannot be represented in 32 bits.

### `conditional`

`conditional(x, y, z)` returns `y` if `x` is nonzero, and `z` if `x` is zero, without using any branching or comparison operators. It works by:

1. Casting `x` to `uint32_t` as `ux`, then computing `is_nonzero = ux | (~ux + 1U)`. This is the unsigned equivalent of `x | -x`. If `x` is nonzero, the sign bit of the result is guaranteed to be 1. If `x` is zero, the result is 0. Using unsigned arithmetic avoids undefined behavior when `x` is `INT32_MIN`.
2. Arithmetic right-shifting `is_nonzero` by 31 bits to produce a `mask` that is either all 1s (0xFFFFFFFF) or all 0s.
3. Returning `(mask & y) | (~mask & z)`. When the mask is all 1s, this selects `y`; when all 0s, it selects `z`.

### `handle_overflow`

`handle_overflow(a, b)` adds two `int32_t` values and returns the mathematically correct sum as an `int64_t`, even when the result would overflow a 32-bit integer. The implementation works by:

1. Computing the sum in unsigned arithmetic: `sum = a + b`. This is always well-defined — unsigned addition wraps modulo $2^{32}$.
2. Interpreting the unsigned sum as a signed 32-bit value and widening it to `int64_t`.
3. Detecting and correcting overflow:
   - **Positive overflow**: If both `a` and `b` are positive but `(int32_t)unsigned_sum` is negative, the sum wrapped past `INT32_MAX`. The function adds $2^{32}$ to compensate.
   - **Negative overflow**: If both `a` and `b` are negative but `(int32_t)unsigned_sum` is non-negative, the sum wrapped past `INT32_MIN`. The function subtracts $2^{32}$ to compensate.
4. **No overflow**: If the signs differ or the signed reinterpretation has the expected sign, the result is already correct.

## Tests and Results

The tests exercise all three functions across a range of inputs including typical values, boundary values, and edge cases. All tests produce correct output.

### `conditional` Tests

| Test Call                                | Expected       | Actual         | Pass |
|------------------------------------------|----------------|----------------|------|
| `conditional(0, 1, 2)`                  | 2              | 2              | Yes  |
| `conditional(1, 1, 2)`                  | 1              | 1              | Yes  |
| `conditional(-1, 1, 2)`                 | 1              | 1              | Yes  |
| `conditional(INT32_MIN, 1, 2)`          | 1              | 1              | Yes  |
| `conditional(INT32_MAX, 1, 2)`          | 1              | 1              | Yes  |
| `conditional(0, -5, -10)`               | -10            | -10            | Yes  |
| `conditional(1, -5, -10)`               | -5             | -5             | Yes  |
| `conditional(0, 7, 7)`                  | 7              | 7              | Yes  |
| `conditional(0, INT32_MAX, INT32_MAX-1)` | 2147483646    | 2147483646     | Yes  |
| `conditional(13, INT32_MAX, INT32_MAX-1)`| 2147483647    | 2147483647     | Yes  |

**Coverage rationale:**
- `x = 0` vs `x = 1` verifies the basic zero/nonzero distinction.
- `x = -1`, `x = INT32_MIN`, and `x = INT32_MAX` verify that negative and extreme nonzero values are handled correctly. The `INT32_MIN` case in particular exercises the unsigned arithmetic path that avoids undefined behavior from negating `INT32_MIN`.
- Negative `y`/`z` values confirm the bitwise masking works with negative return values.
- `y == z` confirms the function still returns the correct value when both branches are equal.
- Boundary `y`/`z` values (`INT32_MAX`, `INT32_MAX - 1`) test that large values survive the masking logic.

### `negate` Tests

| Test Call            | Expected                | Actual         | Pass |
|----------------------|-------------------------|----------------|------|
| `negate(0)`          | 0                       | 0              | Yes  |
| `negate(1)`          | -1                      | -1             | Yes  |
| `negate(-1)`         | 1                       | 1              | Yes  |
| `negate(INT32_MAX)`  | -2147483647             | -2147483647    | Yes  |
| `negate(INT32_MIN)`  | -2147483648 (unchanged) | -2147483648    | Yes  |

**Coverage rationale:**
- `negate(0)` confirms the identity $-0 = 0$ in two's complement.
- `negate(1)` and `negate(-1)` verify basic positive and negative inputs.
- `negate(INT32_MAX)` tests the largest representable positive value, whose negation (-2147483647) still fits in `int32_t`.
- `negate(INT32_MIN)` returns `INT32_MIN` because $-(-2^{31})$ wraps back to itself in unsigned arithmetic. This is the mathematically expected behavior of two's complement — the function does not guard against it but produces the correct bit pattern.

### `handle_overflow` Tests

| Test Call                              | Expected       | Actual         | Pass |
|----------------------------------------|----------------|----------------|------|
| `handle_overflow(INT32_MAX, 1)`        | 2147483648     | 2147483648     | Yes  |
| `handle_overflow(INT32_MAX, INT32_MAX)`| 4294967294     | 4294967294     | Yes  |
| `handle_overflow(INT32_MIN, -1)`       | -2147483649    | -2147483649    | Yes  |
| `handle_overflow(INT32_MIN, INT32_MIN)`| -4294967296    | -4294967296    | Yes  |
| `handle_overflow(5, 10)`              | 15             | 15             | Yes  |
| `handle_overflow(1, 1)`               | 2              | 2              | Yes  |
| `handle_overflow(-5, -10)`            | -15            | -15            | Yes  |
| `handle_overflow(-1, -1)`             | -2             | -2             | Yes  |
| `handle_overflow(INT32_MAX, -1)`       | 2147483646     | 2147483646     | Yes  |
| `handle_overflow(INT32_MIN, 1)`        | -2147483647    | -2147483647    | Yes  |
| `handle_overflow(INT32_MAX, INT32_MIN)` | -1            | -1             | Yes  |
| `handle_overflow(INT32_MIN, INT32_MAX)` | -1            | -1             | Yes  |
| `handle_overflow(100, -50)`            | 50             | 50             | Yes  |
| `handle_overflow(-100, 50)`            | -50            | -50            | Yes  |
| `handle_overflow(0, 0)`               | 0              | 0              | Yes  |
| `handle_overflow(0, INT32_MAX)`        | 2147483647     | 2147483647     | Yes  |
| `handle_overflow(INT32_MIN, 0)`        | -2147483648    | -2147483648    | Yes  |

**Coverage rationale:**
- **Positive overflow** (rows 1-2): Minimal overflow (`INT32_MAX + 1`) and maximal overflow (`INT32_MAX + INT32_MAX`).
- **Negative overflow** (rows 3-4): Minimal overflow (`INT32_MIN - 1`) and maximal overflow (`INT32_MIN + INT32_MIN`).
- **Same sign, no overflow** (rows 5-8): Both positive and both negative cases where the sum fits in 32 bits, verifying that the overflow detection correctly falls through.
- **Mixed signs** (rows 9-14): Overflow is impossible when signs differ. These tests include boundary values (`INT32_MAX + INT32_MIN = -1`) and typical values.
- **Zero operands** (rows 15-17): Zero with zero, zero with `INT32_MAX`, and `INT32_MIN` with zero confirm the identity $a + 0 = a$.

## What Is Working

All implemented functions produce correct results for every test case:

- `conditional` correctly selects between two values for zero, positive, negative, and boundary inputs including `INT32_MIN` and `INT32_MAX`, as well as negative return values.
- `negate` correctly negates positive, negative, and zero inputs. For `INT32_MIN`, the unsigned wrap-around returns `INT32_MIN` itself, which is the expected two's complement behavior.
- `handle_overflow` correctly computes sums across all four categories: positive overflow, negative overflow, same-sign no-overflow, and mixed-sign inputs, including zero operands and extreme boundary values.

## Known Limitations

- **`negate(INT32_MIN)`**: Two's complement negation of `INT32_MIN` (-2147483648) cannot be represented as a positive `int32_t` because `INT32_MAX` is 2147483647. The function returns `INT32_MIN` unchanged.
