.data
        array:        .word 10, 20, 30, 40, 50   # test array
        permutations: .word 1, 2, 3, 4, 0        # swap indices: reverses the array
        length:       .word 5

.text
main:
	# input setup
	la  $a0, array
	la  $a1, permutations
	lw  $a2, length

	# code
        addiu $t0, $zero, 0 # t0 = 0, index
Cond:   slt $t1, $t0, $a2
        beq $t1, $zero, Exit
        # get array[i]
Loop:   sll $t2, $t0, 2 # t2 = t0 * 4
        addu $t3, $a0, $t2 # t3 = &(array[i])
        lw $t4, 0($t3) # t4 = array[i]
        # get array[permutations[i]]
        addu $t5, $a1, $t2 # t5 = &(permutations[i])
        lw $t6, 0($t5) # t6 = permutations[i]
        sll $t6, $t6, 2 # t6 = t6 * 4
        addu $t6, $a0, $t6 # t6 = &array[permutations[i]]
        lw $t7, 0($t6) # t7 = array[permutations[i]]
        # swap
        sw $t7, 0($t3) # array[i] = array[permutations[i]]
        sw $t4, 0($t6) # array[permutations[i]] = array[i], swaped

        addiu $t0, $t0, 1 #t0++
        j Cond
Exit:   
        
