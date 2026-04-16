# Question 3: Jump Tables

.data
# Part (a): jump table for inputs 0-7
jump_table: .word Label0, Label1, Label2, Label3, Label4, Label5, Label6, Label7

# Part (b): jump table for even inputs 4-18 (sparse, indexed directly by input value)
# indices 0-3 and all odd indices are unused placeholders (0)
# index 4 = Even4, index 6 = Even6, ..., index 18 = Even18
jump_table_b: .word 0, 0, 0, 0, Even4, 0, Even6, 0, Even8, 0, Even10, 0, Even12, 0, Even14, 0, Even16, 0, Even18

.text

# Part (a)
# $s1 = input (0-7), $s0 = base address of jump table
# Each entry is a 4-byte word pointer, so offset = input * 4

    la $s0, jump_table   # load table address (test setup)
    li $s1, 3            # test input = 3

    sll $t0, $s1, 2      # t0 = s1 * 4 
    addu $t0, $s0, $t0   # t0 = &jump_table[s1]
    lw $t0, 0($t0)       # t0 = jump_table[s1]
    jr $t0               # jump to it

Label0: # input 0 (4)
Label1: # input 1 (6)
Label2: # input 2 (8)
Label3: # input 3 (10)
# Part (b)
    # test setup
    la $s0, jump_table_b  # load table address (test setup)
    li $s1, 14            # test input = 14

    sll $t0, $s1, 2       # t0 = input * 4 (direct byte offset, no normalization needed)
    addu $t0, $s0, $t0    # t0 = &jump_table_b[input]
    lw $t0, 0($t0)        # t0 = target address
    jr $t0
Label4: # input 4 (12)
Label5: # input 5 (14)
Label6: # input 6 (16)
Label7: # input 7 (18)



Even4:
Even6:
Even8:
Even10:
Even12:
Even14:
    # part (c)
    la $s0, jump_table   # load table address (test setup)
    li $s1, 14            # test input = 14

    addiu $t0, $s1, -4 # t0 = s1 - 4
    sll $t0, $t0, 1      # t0 = (input-4) * 2  (byte offset)
    addu $t0, $s0, $t0   # t0 = &jump_table[s1]
    lw $t0, 0($t0)       # t0 = jump_table[s1]
    jr $t0               # jump to it
Even16:
Even18:


