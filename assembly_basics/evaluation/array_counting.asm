.data
	array:  .float 0.5, 1.0, 2.0, 3.5, 4.0   # test array
	length: .word  5
	low:    .float 1.0                          # lower threshold (inclusive)
	high:   .float 3.5                          # upper threshold (exclusive)

.text
main:
	# input setup
	la   $a0, array       # $a0 = pointer to array
	lw   $a1, length      # $a1 = array length

	lwc1 $f0, low         # load float into float register
	mfc1 $a2, $f0         # move float bits into $a2

	lwc1 $f0, high        # load float into float register
	mfc1 $a3, $f0         # move float bits into $a3
	
	# code
	# load floats into float registers
	mtc1 $a2, $f0    # $f0 = low
	mtc1 $a3, $f1    # $f1 = high
	
	addiu $s0, $zero, 0 # smaller = 0
	addiu $s1, $zero, 0 # between = 0
	addiu $s2, $zero, 0 # larger = 0
	
Loop:	addi $a1, $a1, -1 # a1 -= 1, start the loop with index = length-1
	# a1 is the index and starts high and go to 0
	sll $t0, $a1, 2 # t0 = a1 * 4
	addu $t0, $a0, $t0 # t0 = &(array[i])
	lwc1 $f2, 0($t0) # f2 = array[i]
	
	# conditionals
	c.lt.s $f2, $f1 # if f2 < f1
	bc1t NoLa # if true the result is not larger
	# larger
	addiu $s2, $s2, 1
	j Exit
	
	# the float is either between or smaller
NoLa:	c.lt.s $f2, $f0 # if f2 < f0
	bc1t NoBe # if true the result is not between
	# between
	addiu $s1, $s1, 1
	j Exit
	
	# smaller
NoBe:	addiu $s0, $s0, 1

Exit:	bne $a1, $zero, Loop # goto Loop if $a1 neq 0

	
	
