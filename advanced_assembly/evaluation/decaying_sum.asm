# uint32_t decaying_sum(uint16_t* values, uint16_t length, uint16_t decay)
# $a0 = values (pointer to uint16_t array)
# $a1 = length (treated as uint32_t in loop)
# $a2 = decay
# Returns: $v0 = decaying sum

.data
test_arr: .half 10, 20, 30, 40

.text
.globl main
main:
    la   $a0, test_arr
    li   $a1, 4
    li   $a2, 2
    jal  decaying_sum           # result in $v0, expected: 32
    j Exit

decaying_sum:
    move $a3, $zero             # prev = 0
Loop:
    blez $a1, Ret               # if length <= 0, return prev

    divu $a3, $a2               # prev / decay
    mflo $a3                    # $a3 = prev / decay

    addiu $a1, $a1, -1          # length--

    sll $t0, $a1, 1             # byte offset = length * 2 (uint16_t = 2 bytes)
    addu $t0, $a0, $t0          # &values[length]
    lhu $t0, 0($t0)             # values[length] (zero-extended)
    addu $a3, $a3, $t0          # prev += values[length]

    j Loop

Ret:
    move $v0, $a3
    jr $ra

# Test: [10,20,30,40], decay=2 -> expected 32
Exit:
