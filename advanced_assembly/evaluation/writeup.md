# Advanced Assembly Assignment — Writeup

---

## Q1: Decaying Sum

### Part (a): Tail-Recursive C Implementation

The tail-recursive rewrite uses a helper `decaying_sum_tail` with an extra `prev` parameter. Instead of recursing left-to-right and unwinding right-to-left, the helper processes the array right-to-left, computing `prev = prev/decay + values[length-1]` at each step. The recursive call is the final operation, so no stack frame is needed.

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

Because the function is tail-recursive, no stack frame is needed. Register mapping:

- `$a0` = `values` pointer
- `$a1` = `length`
- `$a2` = `decay`
- `$a3` = `prev` accumulator
- `$v0` = return value


Testing was done with`decay=2 len=4, array = [10, 20, 30, 40]` case. It matches the C output of 32.

---

## Q2: Days of the Week

**Tests:**

| Input (`$a1`) | Expected `$v0` | Expected buffer | Result |
|---------------|----------------|-----------------|--------|
| -1 | 0 | (unchanged) | PASS |
| 0 | 1 | `"Sunday\0"` | PASS |
| 3 | 1 | `"Wednesday\0"` | PASS |
| 6 | 1 | `"Saturday\0"` | PASS |
| 7 | 0 | (unchanged) | PASS |

All tests pass.

---

## Q3: Overflow in a Tree

### Part (a): `add_overflows`

This is a leaf procedure, so no stack frame is needed.

### Part (b): `tree_overflows`

The function:
1. Returns 0 immediately on a null pointer (`beq $a2, $zero, ReturnZero`).
2. Saves `$ra`, `$fp`, `$a2`, and `$f12` in a 32-byte stack frame. `$f12` is stored at offset 12 so that its address is 8-byte aligned (MARS initializes `$sp` at `0x7fffeffc`, which is 4 mod 8).
3. Loads the node's double value into `$f14` and calls `add_overflows`. If overflow is found, jumps to `Return` immediately.
4. Restores `$a2` and `$f12` from the stack, loads the left child pointer, and recurses. Again early-exits if overflow is found.
5. Restores `$a2` and `$f12`, loads the right child pointer, and recurses.
6. Pops stack frame and returns.

**Tests:**

| Test | Function | Input | Expected `$v0` | Result |
|------|----------|-------|----------------|--------|
| Overflow on add | `add_overflows` | `1.7e308 + 1.7e308` | 1 | PASS |
| Single overflow node | `tree_overflows` | `node_right` (1.7e308), d=1.7e308 | 1 | PASS |
| Overflow in right subtree | `tree_overflows` | `node_root` (1.0, left=2.0, right=1.7e308), d=1.7e308 | 1 | PASS |
| No overflow anywhere | `tree_overflows` | `node_root`, d=1.0 | 0 | PASS |

All tests pass.

---

## Q4: Assembly Representation
We are converting the following code into binary representation:
```
Loop:   sll $t0, $s0, 2 	
        addu $t1, $t0, $s3 	
        lw $t2, 0($t1) 
        blt $t2, $s2, Exit 
        addu $s0, $s0, $s1 
        j Loop 
Exit:
```
For `sll $t0, $s0, 2`, `sll` is in R-format. The opcode is $000000$ and the funct code is $000000$. The first source register is `$s0`, which is $16_{10}=10000_2$. The second source register does not exist so its $00000$. The destination register is `$t0`, which is $8_{10}=01000_2$. The shift value $2$ is $00010_2$. Thus, the representation is:

| opcode (6) | rs (5) | rt (5) | rd (5) | shamt (5) | funct (6) |
|:----------:|:------:|:------:|:------:|:---------:|:---------:|
| 000000     | 00000  | 10000  | 01000  | 00010     | 000000    |

`000000 00000 10000 01000 00010 000000` = `0x00104080`

For `addu $t1, $t0, $s3`, `addu` is in R-format. The opcode is `000000` and the funct code is `100001`. The first source register is `$t0`, which is $8_{10}=01000_2$. The second source register is `$s3`, which is $19_{10}=10011_2$. The destination register is `$t1`, which is $9_{10}=01001_2$. The shift amount does not apply so it is `00000`. Thus, the representation is:

| opcode (6) | rs (5) | rt (5) | rd (5) | shamt (5) | funct (6) |
|:----------:|:------:|:------:|:------:|:---------:|:---------:|
| 000000     | 01000  | 10011  | 01001  | 00000     | 100001    |

`000000 01000 10011 01001 00000 100001` = `0x01134821`

For `lw $t2, 0($t1)`, `lw` is in I-format. The opcode is `100011`. The base register is `$t1`, which is $9_{10}=01001_2$ (rs). The destination register is `$t2`, which is $10_{10}=01010_2$ (rt). The immediate offset is `0`, which is `0000000000000000`. Thus, the representation is:

| opcode (6) | rs (5) | rt (5) | imm (16)           |
|:----------:|:------:|:------:|:------------------:|
| 100011     | 01001  | 01010  | 0000000000000000   |

`100011 01001 01010 0000000000000000` = `0x8D2A0000`

`blt $t2, $s2, Exit` is a pseudoinstruction that expands into two real instructions: `slt $at, $t2, $s2` followed by `bne $at, $zero, Exit`.

For `slt $at, $t2, $s2`, `slt` is in R-format. The opcode is `000000` and the funct code is `101010`. The first source register is `$t2`, which is $10_{10}=01010_2$. The second source register is `$s2`, which is $18_{10}=10010_2$. The destination register is `$at`, which is $1_{10}=00001_2$. The shift amount does not apply so it is `00000`. Thus, the representation is:

| opcode (6) | rs (5) | rt (5) | rd (5) | shamt (5) | funct (6) |
|:----------:|:------:|:------:|:------:|:---------:|:---------:|
| 000000     | 01010  | 10010  | 00001  | 00000     | 101010    |

`000000 01010 10010 00001 00000 101010` = `0x0152082A`

For `bne $at, $zero, Exit`, `bne` is in I-format. The opcode is `000101`. The first register is `$at`, which is $1_{10}=00001_2$ (rs field). The second register is `$zero`, which is $0_{10}=00000_2$ (rt field). This instruction has $2$ commands between itself and `Exit`, giving a offset of $2 = 0000000000000010_2$. Thus, the representation is:

| opcode (6) | rs (5) | rt (5) | imm (16)           |
|:----------:|:------:|:------:|:------------------:|
| 000101     | 00001  | 00000  | 0000000000000010   |

`000101 00001 00000 0000000000000010` = `0x14200002`

For `addu $s0, $s0, $s1`, `addu` is in R-format. The opcode is `000000` and the funct code is `100001`. The first source register is `$s0`, which is $16_{10}=10000_2$. The second source register is `$s1`, which is $17_{10}=10001_2$. The destination register is also `$s0`, which is $16_{10}=10000_2$. The shift amount does not apply so it is `00000`. Thus, the representation is:

| opcode (6) | rs (5) | rt (5) | rd (5) | shamt (5) | funct (6) |
|:----------:|:------:|:------:|:------:|:---------:|:---------:|
| 000000     | 10000  | 10001  | 10000  | 00000     | 100001    |

`000000 10000 10001 10000 00000 100001` = `0x02118021`

For `j Loop`, `j` is in J-format. The opcode is `000010`. Loop is at address `0x3080`, so the 26-bit target field is $3080_{16} \div 4 = 00\ 0000\ 0000\ 0000\ 1100\ 0010\ 0000_2$. Thus, the representation is:

| opcode (6) | target (26)                        |
|:----------:|:----------------------------------:|
| 000010     | 00000000000000110000100000         |

`000010 00000000000000110000100000` = `0x08000C20`
