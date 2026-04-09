.data
array: .word 0, 0, 0, 0, 0, 0, 0, 0    # 8 elements

.text
main:
# 1
	j L1
    
# 2
	slt $t0, $s0, $s1
	bne $t0, $zero, L1
    
# 3
	slt $t0, $s1, $s0
	bne $t0, $zero, L1
    
# 4
	slt $t0, $s1, $s0
	beq $t0, $zero, L1
    
# 4
	slt $t0, $s0, $s1
	beq $t0, $zero, L1
    
# 5
	# setup
L1:	lui $a0, 0x1001 # array pointer
	addiu $a1, $zero, 8 # length = 8
	addiu $a2, $zero, 3 # start = 3

	addiu $t3, $zero, 1 # $t3 = 1
	addiu $s2, $zero, 0 #i=0
	j Cond
Loop:	sll $t1, $s2, 2 # $t1 = 4*i
	add $t2, $a0, $t1 # $t2 = &(array[i])
	slt $t4, $a2, $s2 # $t4 = (start < i)
	sw $t3, 0($t2) # array[i] = 1
	bne $t4, $zero, Star # jump to Star if start < i
	sw $zero, 0($t2) # array[i] = 0
Star:	addiu $s2, $s2, 1 # i++
Cond:	slt $t5, $s2, $a1 # $t5 = (i < length)
	bne $t5, $zero, Loop
    
	jr $ra