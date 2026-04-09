# put 42 in memory to be loaded by (b)
.data
testval: .word 42

.text
main:

# a
    addiu $v0, $zero, 7
    
# b
    lui $a0, 0x1001 # now $a0 points to testval
    lw $v0, 0($a0)
    
# c
    lui $a1, 0x1001 # now $a1 points to testval
    sw $a0, 16($a1)
    
# d 
    # $a1 have value 0x10010000
    # reset $a0 to 0 so we can see it when it gets set to 0x10010000 again
    addu $a0, $zero, $zero
    # set $t0 to 8, so we will load the value we stored from the previous part
    addiu $t0, $zero, 8
    # compute the array index
    addiu $t1, $zero, 2 # load constant 2
    multu $t1, $t0 # 16-bit integer so 2 byte offset
    mflo $t1
    addu $t1, $t1, $a1 # add to base
    lw $a0, 0($t1) # load value

    jr $ra
    
    