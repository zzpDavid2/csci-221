# Floats Learning Writeup

## Function Descriptions

### `find_encoding_type`

`find_encoding_type(f)` classifies a `float` as `NORMALIZED`, `DENORMALIZED`, or `SPECIAL` based on its IEEE 754 exponent field. It uses `memcpy` to reinterpret the float's bits as a `uint32_t`, then extracts the exponent bits (bits 23–30) using `mask(23, 30)`:
- If all exponent bits are 1 → `SPECIAL` (infinity or NaN).
- If all exponent bits are 0 → `DENORMALIZED` (zero or subnormal).
- Otherwise → `NORMALIZED`.

### `round_to_nearest_even`

`round_to_nearest_even(value, number_of_bits)` rounds a `uint32_t` value by discarding the lowest `number_of_bits` bits, using the IEEE 754 "round to nearest, ties to even" rule:
1. If the discarded bits represent a value greater than half the rounding boundary, **round up**.
2. If less than half, **round down** (truncate).
3. If exactly half (tie), round to whichever direction makes the last retained bit 0 (even).

## Tests and Results

### `find_encoding_type` Tests

| Test Input        | Expected       | Actual         | Pass |
|-------------------|----------------|----------------|------|
| `1.0f`            | NORMALIZED     | NORMALIZED     | Yes  |
| `-42.5f`          | NORMALIZED     | NORMALIZED     | Yes  |
| `0.0f`            | DENORMALIZED   | DENORMALIZED   | Yes  |
| `-0.0f`           | DENORMALIZED   | DENORMALIZED   | Yes  |
| smallest denorm   | DENORMALIZED   | DENORMALIZED   | Yes  |
| `INFINITY`        | SPECIAL        | SPECIAL        | Yes  |
| `-INFINITY`       | SPECIAL        | SPECIAL        | Yes  |
| `NAN`             | SPECIAL        | SPECIAL        | Yes  |

**Coverage rationale:**
- `1.0f` and `-42.5f` test typical normalized values (positive and negative).
- `0.0f` and `-0.0f` test both signed zeros, which have all-zero exponent bits.
- The smallest denormalized float (bit pattern `0x00000001`) confirms that a nonzero value with a zero exponent is classified as denormalized.
- `INFINITY`, `-INFINITY`, and `NAN` test all three special encodings (positive infinity, negative infinity, and NaN).

### `round_to_nearest_even` Tests

| Test Call          | Expected | Actual | Rounding Case        | Pass |
|--------------------|----------|--------|----------------------|------|
| `round(11, 2)`     | 12       | 12     | Round up             | Yes  |
| `round(9, 2)`      | 8        | 8      | Round down           | Yes  |
| `round(10, 2)`     | 8        | 8      | Tie → round down (even) | Yes  |
| `round(6, 2)`      | 8        | 8      | Tie → round up (even)   | Yes  |
| `round(2, 2)`      | 0        | 0      | Tie → round down (even) | Yes  |
| `round(0, 3)`      | 0        | 0      | Zero input           | Yes  |
| `round(15, 0)`     | 15       | 15     | No rounding          | Yes  |
| `round(3, 1)`      | 4        | 4      | Tie → round up (even)   | Yes  |
| `round(1, 1)`      | 0        | 0      | Tie → round down (even) | Yes  |

**Coverage rationale:**
- **Round up** (`11 → 12`): Discarded bits exceed half the rounding boundary.
- **Round down** (`9 → 8`): Discarded bits are less than half.
- **Tie to even** (`10 → 8`, `6 → 8`, `2 → 0`, `3 → 4`, `1 → 0`): Five tie-breaking cases cover both "round up to make even" and "round down to keep even" with different bit widths (1 and 2 bits).
- **Edge cases** (`0` and `number_of_bits = 0`): Zero input stays zero; rounding by zero bits is a no-op.

## What Is Working

All three functions produce correct results for every test case:

- `mask` correctly generates bitmasks for all tested ranges, including single-bit and near-full-width cases.
- `find_encoding_type` correctly classifies normalized, denormalized, and special float values including signed zeros, denormals, infinities, and NaN.
- `round_to_nearest_even` correctly handles round-up, round-down, and all tie-breaking scenarios with the "ties to even" rule.

## Known Limitations

- **`round_to_nearest_even` with `number_of_bits >= 32`**: The function returns the value unchanged with a debug message, since shifting by 32+ bits is undefined behavior in C.

