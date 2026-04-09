# Floating Point Evaluation Writeup

## Overview

This implementation covers an 8-bit tiny floating point format (1 sign bit, 4 exponent bits, 3 significand bits). The tested functionality includes bit extraction/insertion, encoding classification, exponent/significand decoding, construction/packing, normalization, conversion to IEEE `float`, and arithmetic (`add_tiny_floats`, `multiply_tiny_floats`).

## Tests and Results

### Getter and Setter Tests

| Test Call | Expected | Actual | Pass | What this test checks |
|---|---|---|---|---|
| Build with `set_sign_bit`, `set_exponent_bits`, `set_significand_bits` | `0xD5` | `0xD5` | Yes | Packing sign/exponent/significand into one 8-bit value |
| `get_sign_bit(0xD5)` | `true` | `true` | Yes | Sign bit extraction |
| `get_exponent_bits(0xD5)` | `0b1010` | `0b1010` | Yes | Exponent field extraction |
| `get_significand_bits(0xD5)` | `0b101` | `0b101` | Yes | Significand field extraction |
| `set_exponent_bits(0x55, 0b10000)` | `0x55` | `0x55` | Yes | Invalid exponent input is rejected and value is unchanged |
| `set_significand_bits(0xAA, 0b1000)` | `0xAA` | `0xAA` | Yes | Invalid significand input is rejected and value is unchanged |

### Encoding and Decode Helper Tests

| Test Call | Expected | Actual | Pass | What this test checks |
|---|---|---|---|---|
| `find_encoding_type(0x00)` | `ZERO` | `ZERO` | Yes | Positive zero classification |
| `find_encoding_type(0x80)` | `ZERO` | `ZERO` | Yes | Negative zero classification |
| `find_encoding_type(0x01)` | `DENORMALIZED` | `DENORMALIZED` | Yes | Denormal classification |
| `find_encoding_type(0x08)` | `NORMALIZED` | `NORMALIZED` | Yes | Normalized classification |
| `find_encoding_type(0x78)` | `TF_INFTY` | `TF_INFTY` | Yes | Infinity classification |
| `find_encoding_type(0x79)` | `TF_NAN` | `TF_NAN` | Yes | NaN classification |
| `decode_exponent(0x48)` | `2` | `2` | Yes | Bias removal for normalized exponent |
| `decode_exponent(0x03)` | `-6` | `-6` | Yes | Denormal exponent decoding |
| `decode_exponent(0x00)` | `-6` | `-6` | Yes | Zero exponent handling path |
| `decode_significand(0x4A)` | `10` | `10` | Yes | Implicit leading 1 for normalized numbers |
| `decode_significand(0x02)` | `2` | `2` | Yes | No implicit leading 1 for denormals |

### Construction and Conversion Tests

| Test Call | Expected | Actual | Pass | What this test checks |
|---|---|---|---|---|
| `pack(true, 0b0011, 0b101)` | `0x9D` | `0x9D` | Yes | Correct bit layout during construction |
| `tiny_float_to_float(0x00)` | `0.0` | `0.0` | Yes | Positive zero conversion |
| `tiny_float_to_float(0x80)` sign | negative zero sign bit set | negative zero sign bit set | Yes | Preserves `-0.0` sign |
| `tiny_float_to_float(0x01)` | `1/512` | `1/512` | Yes | Denormal numeric conversion |
| `tiny_float_to_float(0x38)` | `1.0` | `1.0` | Yes | Normalized conversion (exact whole value) |
| `tiny_float_to_float(0x3C)` | `1.5` | `1.5` | Yes | Normalized conversion (fractional value) |
| `tiny_float_to_float(0x78)` | `+infinity` | `+infinity` | Yes | Infinity conversion |
| `tiny_float_to_float(0x79)` | `NaN` | `NaN` | Yes | NaN conversion |

### `normalize_and_pack` Tests

| Test Call | Expected | Actual | Pass | What this test checks |
|---|---|---|---|---|
| `normalize_and_pack(false, 0, 0)` | `0000 0000` | `0000 0000` | Yes | Zero input maps to +0 encoding |
| `normalize_and_pack(true, 0, 0)` | `1000 0000` | `1000 0000` | Yes | Zero input maps to -0 encoding |
| `normalize_and_pack(false, -8, 0x8000)` | `0111 0000` | `0111 0000` | Yes | Normalized finite path with expected exponent/significand packing |
| `normalize_and_pack(false, -7, 0x8000)` | `0111 1000` | `0111 1000` | Yes | Overflow path returns +infinity |
| `normalize_and_pack(false, -22, 0x8000)` | `0000 0100` | `0000 0100` | Yes | Underflow-to-denormal path |
| `normalize_and_pack(false, -22, 0xF000)` | `0000 1000` | `0000 1000` | Yes | Denormal rounding path that becomes minimum normalized |
| `normalize_and_pack(true, -40, 0x8000)` | `1000 0000` | `1000 0000` | Yes | Extreme underflow path to signed zero |

### `add_tiny_floats` Tests

| Test Call | Strategy | Input Floats (a, b) | Expected (binary) | Actual (binary) | Output Float | Pass | What this test checks |
|---|---|---|---|---|---|---|---|
| `add_tiny_floats(0x38, 0x30)` | Equivalence class | `(1.0, 0.5)` | `0011 1100` | `0011 1100` | `1.5` | Yes | Exact finite addition (`1.0 + 0.5 = 1.5`) |
| `add_tiny_floats(0x30, 0x38)` | Equivalence class | `(0.5, 1.0)` | `0011 1100` | `0011 1100` | `1.5` | Yes | Commutativity for finite-finite inputs |
| `add_tiny_floats(0x3C, 0xB8)` | Equivalence class | `(1.5, -1.0)` | `0011 0000` | `0011 0000` | `0.5` | Yes | Mixed-sign finite result not crossing encoding boundary |
| `add_tiny_floats(0x38, 0xB8)` | Boundary | `(1.0, -1.0)` | `0000 0000` | `0000 0000` | `0.0` | Yes | Exact cancellation to zero |
| `add_tiny_floats(0x01, 0x81)` | Boundary | `(0.001953125, -0.001953125)` | `0000 0000` | `0000 0000` | `0.0` | Yes | Smallest denormal cancellation |
| `add_tiny_floats(0x00, 0x38)` | Boundary | `(0.0, 1.0)` | `0011 1000` | `0011 1000` | `1.0` | Yes | `+0` identity |
| `add_tiny_floats(0x80, 0x38)` | Boundary | `(-0.0, 1.0)` | `0011 1000` | `0011 1000` | `1.0` | Yes | `-0` identity |
| `add_tiny_floats(0x01, 0x01)` | Boundary | `(0.001953125, 0.001953125)` | `0000 0010` | `0000 0010` | `0.00390625` | Yes | Denormal + denormal stays denormal |
| `add_tiny_floats(0x07, 0x01)` | Boundary | `(0.013671875, 0.001953125)` | `0000 1000` | `0000 1000` | `0.015625` | Yes | Denormal max + min crossing to smallest normalized |
| `add_tiny_floats(0x08, 0x87)` | Boundary | `(0.015625, -0.013671875)` | `0000 0001` | `0000 0001` | `0.001953125` | Yes | Smallest normalized minus largest denormal |
| `add_tiny_floats(0x77, 0x01)` | Boundary | `(240.0, 0.001953125)` | `0111 0111` | `0111 0111` | `240.0` | Yes | Large exponent-gap (tiny addend does not perturb max finite) |
| `add_tiny_floats(0x77, 0x81)` | Boundary | `(240.0, -0.001953125)` | `0111 0111` | `0111 0111` | `240.0` | Yes | Large exponent-gap with negative tiny addend |
| `add_tiny_floats(0x77, 0x77)` | Boundary | `(240.0, 240.0)` | `0111 1000` | `0111 1000` | `+inf` | Yes | Positive finite overflow to +infinity |
| `add_tiny_floats(0xF7, 0xF7)` | Boundary | `(-240.0, -240.0)` | `1111 1000` | `1111 1000` | `-inf` | Yes | Negative finite overflow to -infinity |
| `add_tiny_floats(0x78, 0x38)` | Control flow | `(+inf, 1.0)` | `0111 1000` | `0111 1000` | `+inf` | Yes | Branch: first operand is +infinity |
| `add_tiny_floats(0xF8, 0x38)` | Control flow | `(-inf, 1.0)` | `1111 1000` | `1111 1000` | `-inf` | Yes | Branch: first operand is -infinity |
| `add_tiny_floats(0xF8, 0xF8)` | Control flow | `(-inf, -inf)` | `1111 1000` | `1111 1000` | `-inf` | Yes | Branch: both infinities same sign |
| `add_tiny_floats(0x78, 0xF8)` | Control flow | `(+inf, -inf)` | `0111 1001` | `0111 1001` | `NaN` | Yes | Branch: infinities opposite sign returns NaN |
| `add_tiny_floats(0x79, 0x38)` | Control flow | `(NaN, 1.0)` | `0111 1001` | `0111 1001` | `NaN` | Yes | NaN propagation (left operand) |
| `add_tiny_floats(0x38, 0x79)` | Control flow | `(1.0, NaN)` | `0111 1001` | `0111 1001` | `NaN` | Yes | NaN propagation (right operand) |

### `multiply_tiny_floats` Tests

| Test Call | Strategy | Input Floats (a, b) | Expected (binary) | Actual (binary) | Output Float | Pass | What this test checks |
|---|---|---|---|---|---|---|---|
| `multiply_tiny_floats(0x3C, 0x40)` | Equivalence class | `(1.5, 2.0)` | `0100 0100` | `0100 0100` | `3.0` | Yes | Exact finite multiplication (`1.5 * 2.0 = 3.0`) |
| `multiply_tiny_floats(0x40, 0x3C)` | Equivalence class | `(2.0, 1.5)` | `0100 0100` | `0100 0100` | `3.0` | Yes | Commutativity for finite-finite inputs |
| `multiply_tiny_floats(0xB8, 0xB8)` | Equivalence class | `(-1.0, -1.0)` | `0011 1000` | `0011 1000` | `1.0` | Yes | Negative × negative sign class |
| `multiply_tiny_floats(0x40, 0x30)` | Equivalence class | `(2.0, 0.5)` | `0011 1000` | `0011 1000` | `1.0` | Yes | Finite identity-style exact case (`2.0 * 0.5 = 1.0`) |
| `multiply_tiny_floats(0x01, 0x38)` | Boundary | `(0.001953125, 1.0)` | `0000 0001` | `0000 0001` | `0.001953125` | Yes | Min denorm preserved by multiply-by-one |
| `multiply_tiny_floats(0x07, 0x38)` | Boundary | `(0.013671875, 1.0)` | `0000 0111` | `0000 0111` | `0.013671875` | Yes | Max denorm preserved by multiply-by-one |
| `multiply_tiny_floats(0x08, 0x08)` | Boundary | `(0.015625, 0.015625)` | `0000 0000` | `0000 0000` | `0.0` | Yes | Smallest normalized underflow to zero |
| `multiply_tiny_floats(0x01, 0x01)` | Boundary | `(0.001953125, 0.001953125)` | `0000 0000` | `0000 0000` | `0.0` | Yes | Min denorm squared underflow |
| `multiply_tiny_floats(0x77, 0x01)` | Boundary | `(240.0, 0.001953125)` | `0010 1111` | `0010 1111` | `0.46875` | Yes | Boundary finite × min denorm still finite |
| `multiply_tiny_floats(0x77, 0x40)` | Boundary | `(240.0, 2.0)` | `0111 1000` | `0111 1000` | `+inf` | Yes | Positive finite overflow to +infinity |
| `multiply_tiny_floats(0x78, 0xC0)` | Control flow | `(+inf, -2.0)` | `1111 1000` | `1111 1000` | `-inf` | Yes | Infinity branch with negative finite sign propagation |
| `multiply_tiny_floats(0xF8, 0xC0)` | Control flow | `(-inf, -2.0)` | `0111 1000` | `0111 1000` | `+inf` | Yes | Infinity branch with negative × negative sign propagation |
| `multiply_tiny_floats(0x78, 0x78)` | Control flow | `(+inf, +inf)` | `0111 1000` | `0111 1000` | `+inf` | Yes | Branch: both infinities same sign |
| `multiply_tiny_floats(0x78, 0xF8)` | Control flow | `(+inf, -inf)` | `1111 1000` | `1111 1000` | `-inf` | Yes | Branch: both infinities opposite sign |
| `multiply_tiny_floats(0x78, 0x38)` | Control flow | `(+inf, 1.0)` | `0111 1000` | `0111 1000` | `+inf` | Yes | Branch: infinity with finite nonzero |
| `multiply_tiny_floats(0x78, 0x00)` | Control flow | `(+inf, +0.0)` | `0111 1001` | `0111 1001` | `NaN` | Yes | Branch: infinity × zero returns NaN |
| `multiply_tiny_floats(0xF8, 0x80)` | Control flow | `(-inf, -0.0)` | `0111 1001` | `0111 1001` | `NaN` | Yes | Branch: infinity × negative zero returns NaN |
| `multiply_tiny_floats(0x79, 0x38)` | Control flow | `(NaN, 1.0)` | `0111 1001` | `0111 1001` | `NaN` | Yes | NaN propagation |
| `multiply_tiny_floats(0x77, 0x77)` | Boundary | `(240.0, 240.0)` | `0111 1000` | `0111 1000` | `+inf` | Yes | Max finite squared overflow |

## How Tests Were Run

From `floats/evaluation`:

1. `make`
2. `make test`

Summary from test program:
- `81 run, 0 failed`

## What Is Working

- All currently implemented functionality passes the executed test suite (`81 run, 0 failed`).
- Bit extraction/insertion and encoding helpers are supported by the tables in **Getter and Setter Tests** and **Encoding and Decode Helper Tests**.
- Conversion behavior is supported by **Construction and Conversion Tests**, including `+0`, `-0`, denormal values, normalized values, `+inf`, `-inf`, and `NaN`.
- Normalization/packing behavior is supported by **normalize_and_pack Tests**, including underflow-to-denorm, denorm-to-norm rounding boundary, and overflow-to-infinity.
- Arithmetic behavior is supported by **add_tiny_floats Tests** and **multiply_tiny_floats Tests**, which cover equivalence classes (typical finite arithmetic), boundary cases (denorm/normal edges, underflow/overflow, exponent-gap inputs), and control-flow branches (NaN/infinity special-case paths).

## Bugs Identified During Testing

- **Stale documentation (fixed):** writeup now reflects the expanded arithmetic testing set and current results.

## Known Limitations

- The current evidence is based on hand-picked tests documented above; coverage is broad but not exhaustive over all $256 \times 256$ input pairs for `add_tiny_floats` and `multiply_tiny_floats`.
