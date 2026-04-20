# Node layout (16 bytes total):
#   offset  0: double value    (8 bytes)
#   offset  8: left  child ptr (4 bytes)
#   offset 12: right child ptr (4 bytes)
.data
test_d: .double 1.7e308       # adding this to 1.7e308 should overflow
test_1: .double 1.0

# tree:
#        [1.0]
#       /     \
#   [2.0]   [1.7e308]
# With d=1.7e308: root and left don't overflow, right does
node_left:  .double 2.0
             .word 0, 0
node_right: .double 1.7e308
             .word 0, 0
node_root:  .double 1.0
             .word node_left, node_right


.text
.globl main
main:
    # Test add_overflows: 1.7e308 + 1.7e308 -> should return $v0=1
    l.d  $f12, test_d
    l.d  $f14, test_d
    jal  add_overflows
    # $v0 expected: 1

    # Test tree_overflows: tree with 1.7e308, d=1.7e308 -> should return $v0=1
    l.d  $f12, test_d
    la   $a2,  node_right
    jal  tree_overflows
    $v0 expected: 1

    # Test: overflow only in right subtree -> expected $v0=1
    l.d  $f12, test_d        # d = 1.7e308
    la   $a2,  node_root
    jal  tree_overflows
    $v0 expected: 1

    # Test: no overflow anywhere (d=1.0)
    l.d  $f12, test_1        # d = 1.0
    la   $a2,  node_root
    jal  tree_overflows
    # $v0 expected: 0

    j Exit

# Part (a)
# input:
# $f12 = first double
# $f14 = second double
# output:
# $v0  = boolean
add_overflows:
    # input: a0, pointer to float
    # output: v0, boolean
    # leaf procedure
    add.d $f12, $f12, $f14
    mfc1 $t0, $f13 
    li $t1, 0x7FF00000
    and $t0, $t0, $t1
    seq $v0, $t0, $t1      # returns 1 only when masked result == mask

    jr $ra

# Part (b)
# input:
# $f12 = input double
# $a2  = node pointer
# output:
# $v0 = boolean
tree_overflows:
    beq $a2, $zero, ReturnZero # Null pointer check

    # Stack frame (32 bytes):
    #   28($sp) = $ra
    #   24($sp) = $fp
    #   20($sp) = $a2 (node pointer)
    #   12($sp) = $f12 (double, 8 bytes) 8-byte aligned 

    addi $sp, $sp, -32
    sw $ra, 28($sp)
    sw $fp, 24($sp)
    s.d $f12, 12($sp)    # save the input double (8 bytes)
    sw $a2, 20($sp)      # save node pointer
    addiu $fp, $sp, 28

    addiu $v0, $zero, 0 # set v0 to zero

    l.d $f14, 0($a2)    # load double from tree node
    jal add_overflows   # call add_overflows
    bne $v0, $zero, Return 
    
    # these restores are technically unnesesary since we know add_overflows didn't change them
    # but we are following the calling convention
    lw $a2, 20($sp) # restore node pointer from stack
    l.d $f12, 12($sp)    # restore caller saved f12 from stack
    lw $a2, 8($a2)  # set node pointer to left child
    jal tree_overflows  # recursive call for left child
    bne $v0, $zero, Return

    lw $a2, 20($sp) # restore node pointer from stack
    l.d $f12, 12($sp)    # restore caller saved f12 from stack
    lw $a2, 12($a2) # set node pointer to right child
    jal tree_overflows
    # fall through to Return
Return:
    lw $fp, 24($sp)
    lw $ra, 28($sp)
    addi $sp, $sp, 32
    jr $ra

ReturnZero:
    addiu $v0, $zero, 0 # set v0 to zero
    jr $ra

Exit:
