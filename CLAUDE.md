# CSCI 221 — Computer Science Fundamentals 2

## Simulator
- Use **MARS** (not SPIM). `Mars4_5.jar` is in the project root.
- MARS requires `.globl main` for the entry point.
- MARS does **not** auto-pad `.half` to word alignment — add explicit `.space 2` before a `.word` in the same struct if needed.

## MIPS Assembly Conventions

### Pseudoinstructions
- **Evaluation assignments**: pseudoinstructions are **NOT allowed**.
- **Learning assignments**: pseudoinstructions are allowed.
- Real instructions only (no `li`, `la`, `move`, `blt`, `bgt`, `ble`, `bge`):
  - Use `addiu $t0, $zero, imm` instead of `li`
  - Use `lui` + `ori` for addresses instead of `la`
  - Use `addu $t0, $t1, $zero` instead of `move`
  - Use `slt` + `beq`/`bne` instead of `blt`/`bgt`

### Calling Convention
- **Callee-saved** (save/restore if your function uses them): `$s0–$s7`, `$fp`, `$ra`
- **Caller-saved** (save before `jal` if you need them after): `$t0–$t9`, `$a0–$a3`, `$v0–$v1`
- Stack frames must be **multiples of 32 bytes**.
- Frame layout (typical): `$ra` at top (highest offset), `$fp` below it, then `$s` regs, then `$t` regs.
- Set `$fp`: `addiu $fp, $sp, frame_size - 4`

### Frame Size Reference
| Saved registers | Min bytes needed | Frame size (×32) |
|-----------------|-----------------|------------------|
| $ra + $fp only  | 8               | 32               |
| + $s0–$s7       | 40              | 64               |
| + $t0–$t7       | 72              | 96               |

### Floating Point
- Load float bits: `lw $t0, label; mtc1 $t0, $f0`
- Store float bits back: `mfc1 $t0, $f0`
- Use `c.lt.s` / `c.le.s` + `bc1t` / `bc1f` for float comparisons
- `slt` does **not** work on floats

### Integer Multiply / Divide
- `mult` / `multu` — result in `$hi` (high) and `$lo` (low); use `mfhi` / `mflo`
- Use `multu` for unsigned arithmetic
- 64-bit product: two `multu` calls — one for the low word (capturing carry via `mfhi`), one for the high word

### Array Access
- `uint16_t` (`.half`): offset = `sll $t, $idx, 1` (×2)
- `uint32_t` / pointer (`.word`): offset = `sll $t, $idx, 2` (×4)
- Load halfword zero-extended: `lhu`; sign-extended: `lh`

### Tail Recursion → Loop
- Tail calls use `j` (not `jal`) — no new stack frame needed.
- Add a loop label **after** any one-time initialization so the back-edge skips it.

## Machine Code Encoding
- **R-type**: `opcode(6) | rs(5) | rt(5) | rd(5) | shamt(5) | funct(6)`
- **I-type**: `opcode(6) | rs(5) | rt(5) | imm(16)`  — `beq` offset = (target − (PC+4)) / 4
- **J-type**: `opcode(6) | target(26)` — target = absolute word address = addr >> 2

## Testing Workflow
- C reference implementation in `.c` file; `make test` to run
- MIPS test in `.asm` with a `main:` that calls the function and exits via syscall 10
- Check result in MARS register display (`$v0`) after Run
