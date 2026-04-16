.data
# Node layout in memory:
#   offset 0: 16-bit value  (.half)
#   offset 2: padding       (.space 2)
#   offset 4: next pointer  (.word)
# Total: 8 bytes per node
#
# List: 2 -> 3 -> 4 -> null  (product = 24)

# node3:  .half 4
#         .space 2
#         .word 0        # null pointer (end of list)

# node2:  .half 3
#         .space 2
#         .word node3

# node1:  .half 2
#         .space 2
#         .word node2

# List: 2000 -> 2000 -> 2000 -> null  (product = 8,000,000,000)

node3:  .half 2000
        .space 2
        .word 0

node2:  .half 2000
        .space 2
        .word node3

node1:  .half 2000
        .space 2
        .word node2

.text
main:
	    # input setup
	    la $a0, node1    # $a0 = pointer to head of list

	    # code
        # initalize 64 bit product to 1
        addiu $v0, $zero, 1 # low = 1
        addiu $v1, $zero, 0 # high = 0

Loop:   lh $t0, 0($a0) # t0 = node.value
        multu  $v0, $t0       # low * val → HI:LO
        mflo  $v0            # new low word
        mfhi  $t1            # carry from low * val

        multu $v1, $t0       # high * val → HI:LO (only need lower 32 bits)
        mflo  $t2            # new high word (from old high * val)

        addu  $v1, $t1, $t2  # new high = carry + (old high * val)
        lw $a0, 4($a0) # a0 = node.next
        bne $a0, $zero, Loop


