# Assembly Basics Learning Writeup

## 1.asm — Data Movement

**a.** Loads the immediate value `7` into `$v0` using `addiu`.

**b.** Uses `lui` to form the base address of the data segment (`0x10010000`), then loads the word stored at `testval` (42) into `$v0` via `lw`.

**c.** Stores the value in `$a0` (which holds `0x10010000`) to the memory address 16 bytes past the data segment base (`$a1 + 16`).

**d.** Computes a dynamic array index: sets index `i = 8` and element size `2`, multiplies them with `multu` to get a byte offset of 16, adds that offset to the base address in `$a1`, then loads the word at that address into `$a0`. This retrieves the value stored in part (c).

---

## 2.asm — Integer Computation

**a.** Computes `$s1 = $s0 + 128` using `addiu`.

**b.** Sets `$t1 = 10` and `$t0 = 5`, then subtracts to store `$v0 = 5`.

**c.** Sets `$a0 = 1`, `$a1 = 2`, `$a2 = 1`, then computes `$v0 = 1 - 2 + 1 + 42 = 42`.

**d.** Sets `$s0 = 2` and multiplies `$s0 * $s1` (2 × 128 = 256) using `mult`. The 64-bit product is split between `HI` and `LO`; `mfhi` and `mflo` retrieve each half.

**e.** Divides `$s0` by `$s1` (2 ÷ 128) using `div`. `mfhi` retrieves the remainder (2) into `$t1`, and `mflo` retrieves the quotient (0) into `$t0`.

---

## 3.asm — Floating Point

**a.** Loads two double-precision values from the data segment (`val1 = 3.14`, `val2 = 2.71`) into `$f0` and `$f2` using `ldc1`, adds them with `add.d` into `$f4`, and stores the result back to `result` with `sdc1`.

**b.** Moves the integer values in `$a0` and `$a1` into floating-point registers using `mtc1`, converts each to a single-precision float with `cvt.s.w`, multiplies them with `mul.s`, and moves the result back to an integer register `$s0` via `mfc1`.

---

## 4.asm — Control Flow

**1.** Unconditional jump directly to label `L1`.

**2.** Branches to `L1` if `$s0 < $s1` (using `slt` + `bne`).

**3.** Branches to `L1` if `$s0 > $s1` (checks `$s1 < $s0`, then `bne`).

**4a.** Branches to `L1` if `$s0 >= $s1` (checks `$s1 < $s0`; if false, branch on `beq`).

**4b.** Branches to `L1` if `$s1 >= $s0` (checks `$s0 < $s1`; if false, branch on `beq`).

**5.** Iterates over an 8-element integer array (`length = 8`, `start = 3`) using a while-style loop. For each index `i`:
- Tentatively writes `1` to `array[i]`.
- If `i <= start` (i.e., `start < i` is false), overwrites with `0`.

Result: `[0, 0, 0, 0, 1, 1, 1, 1]` — the first four elements are 0 and the remaining four are 1.
