# Question 1: Procedure Calls

.globl main

# Part (a)
# Function using only $a0-$a3 as inputs, $v0-$v1 as outputs, no nested calls.

main:
    jal FuncA
    jal FuncB
    jal FuncC
    j Exit

FuncA:
    # callee setup: nothing to save
    # $a0-$a3 and $v0-$v1 are caller-saved, so the callee may freely modify them.
    # No $s registers used, so nothing needs to be preserved.
    # No nested calls, so $ra remains valid throughout.

    # ... function body ...

    # callee return
    jr $ra

FuncB:
    # setup stack frame and store values
    addi $sp, $sp, -32 # push frame
    sw $ra, 28($sp) # store ra
    sw $fp, 24($sp) # store fp
    addiu $fp, $sp, 28

    # function call
    jal FuncA

    # load values back and remove stack frame
    lw $fp, 24($sp) # restore fp
    lw $ra, 28($sp) # store ra
    addi $sp, $sp, 32 # pop frame

    # return
    jr $ra

FuncC:
    # setup stack frame and store values
    addi $sp, $sp, -96 # push frame
    sw $ra, 92($sp) # store ra
    sw $fp, 88($sp) # store fp
    addiu $fp, $sp, 92

    # store t0-t7 (caller-saved)
    sw $t0, 84($sp)
    sw $t1, 80($sp)
    sw $t2, 76($sp)
    sw $t3, 72($sp)
    sw $t4, 68($sp)
    sw $t5, 64($sp)
    sw $t6, 60($sp)
    sw $t7, 56($sp)

    # store s0-s7 (callee-saved)
    sw $s0, 52($sp)
    sw $s1, 48($sp)
    sw $s2, 44($sp)
    sw $s3, 40($sp)
    sw $s4, 36($sp)
    sw $s5, 32($sp)
    sw $s6, 28($sp)
    sw $s7, 24($sp)

    # function call
    jal FuncB

    # restore t0-t7
    lw $t0, 84($sp)
    lw $t1, 80($sp)
    lw $t2, 76($sp)
    lw $t3, 72($sp)
    lw $t4, 68($sp)
    lw $t5, 64($sp)
    lw $t6, 60($sp)
    lw $t7, 56($sp)

    # restore s0-s7
    lw $s0, 52($sp)
    lw $s1, 48($sp)
    lw $s2, 44($sp)
    lw $s3, 40($sp)
    lw $s4, 36($sp)
    lw $s5, 32($sp)
    lw $s6, 28($sp)
    lw $s7, 24($sp)

    # load values back and remove stack frame
    lw $fp, 88($sp) # restore fp
    lw $ra, 92($sp) # restore ra
    addi $sp, $sp, 96 # pop frame

    # return
    jr $ra

Exit:
