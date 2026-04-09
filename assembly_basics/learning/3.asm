.data
val1: .double 3.14
val2: .double 2.71
result: .double 0.0

.text
main:
    # setup
    lui $a0, 0x1001          # $a0 points to val1
    addiu $a1, $a0, 8        # $a1 points to val2 (8 bytes later, since doubles are 64-bit)
    addiu $a3, $a0, 16       # $a3 points to result

# a
    ldc1 $f0, 0($a0)
    ldc1 $f2, 0($a1)
    add.d $f4, $f0, $f2
    sdc1 $f4, 0($a3)
    
# b 
    mtc1 $a0, $f0          # copy $a0's bits into $f0
    cvt.s.w $f0, $f0       # convert integer to single float
    
    mtc1 $a1, $f2          # copy $a1's bits into $f2
    cvt.s.w $f2, $f2       # convert integer to single float
    
    mul.s $f4, $f0, $f2    # multiply the two floats
    
    mfc1 $s0, $f4          # move result back to integer register