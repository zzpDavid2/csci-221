.text
main:

# a
    addiu $s1, $s0, 128
    
# b
    # setup t0 and t1
    addiu $t1, $zero, 10
    addiu $t0, $zero, 5
    
    subu $v0, $t1, $t0
    
# c
    #setup $a0, $a1, $a2
    addiu $a0, $zero, 1
    addiu $a1, $zero, 2
    addiu $a2, $zero, 1
    
    addu $v0, $zero, $a0
    subu $v0, $v0, $a1
    addu $v0, $v0, $a2
    addiu $v0, $v0, 42
    
# d
    # $s1 should have value 128
    addiu $s0, $zero, 2 # set $s0 to 2
    
    mult $s0, $s1
    mfhi $t0
    mflo $t1
    
# e
    div $s0, $s1
    mfhi $t1 # high is remainder
    mflo $t0 # low is quotient
    
    jr $ra
    
