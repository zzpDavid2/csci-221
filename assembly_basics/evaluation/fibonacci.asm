.text
main:
	# store input in $a0
        addiu $a0, $zero, 10 # $a0 = n
	
        addiu $t0, $zero, 1 # $t0 = 1, current
        addiu $v0, $zero, 0 # $v0 = 0, previous (result)
        j Cond
Loop:   addu $t1, $t0, $v0 # $t1 = $v0 + $t0, next = current + previous
	addu $v0, $zero, $t0 # $v0 = $t0, previous = current
	addu $t0, $zero, $t1 # $t0 = $t1, current = next
        addi $a0, $a0, -1 # $a0 -= 1
Cond:   bne $a0, $zero, Loop # goto Loop if $a0 neq 0
