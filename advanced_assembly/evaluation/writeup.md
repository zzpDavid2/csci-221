# Advanced Assembly Assignment — Writeup

---

## Q1: Decaying Sum

### Part (a): Tail-Recursive C Implementation

The original `decaying_sum` is not tail-recursive because work happens *after* the recursive call: the result must be divided by `decay` and added to `values[0]` before returning. This means the call stack must be preserved at every level.

The tail-recursive rewrite uses a helper `decaying_sum_tail` with an extra `prev` accumulator parameter. Instead of recursing left-to-right and unwinding right-to-left, the helper processes the array *right-to-left*, computing `prev = prev/decay + values[length-1]` at each step. The recursive call is the final operation, so no stack frame is needed.

**Tests (run via `make test`):**

| Test | Input | Decay | Expected | Result |
|------|-------|-------|----------|--------|
| empty | `[]` | 2 | 0 | PASS |
| single | `[42]` | 3 | 42 | PASS |
| decay=1 | `[5, 10, 15]` | 1 | 30 | PASS |
| decay=2 len=4 | `[10, 20, 30, 40]` | 2 | 32 | PASS |
| decay=10 len=3 | `[100, 50, 25]` | 10 | 105 | PASS |

All tests pass. The tail-recursive version matches the original on all cases.

### Part (b): MIPS Assembly

The MIPS implementation in `decaying_sum.asm` directly mirrors the tail-recursive C code. Because the function is tail-recursive, **no stack frame is needed** — the tail call is implemented with a plain `j` instead of `jal`, reusing the same `$ra` from the caller. Register mapping:

- `$a0` = `values` pointer
- `$a1` = `length`
- `$a2` = `decay`
- `$a3` = `prev` accumulator
- `$v0` = return value

Key instructions used:
- `lhu` to load a zero-extended `uint16_t` (2-byte) value from the array
- `divu` / `mflo` for unsigned integer division
- `blez` for the base-case check (`length <= 0`)

**Status:** Implementation is complete. Testing was done by tracing the `decay=2 len=4` case manually: the assembly produces prev=40→50→45→32 on each iteration, matching the C output of 32.

---

## Q2: Days of the Week

TODO

---

## Q3: Overflow in a Tree

TODO

---

## Q4: Assembly Representation

TODO
