# int days_of_the_week(char* list, int day)
# $a0 = list (pointer to char[10])
# $a1 = day  (0=Sunday ... 6=Saturday)
# Returns: $v0 = 1 if valid enum value, 0 if not

.data
jump_table: .word Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday

# test
test_buf: .space 10

.text
.globl main
main:
    # test setup
    la   $a0, test_buf
    li   $a1, 3                 # Wednesday -> expected "Wednesday", $v0=1
    jal  days_of_the_week
    j Exit

days_of_the_week:
    # bounds check: valid range is 0..6
    bltz  $a1, Invalid
    li    $t0, 6
    bgt   $a1, $t0, Invalid

    # jump table
    sll   $t0, $a1, 2           # byte offset = day * 4
    la    $t1, jump_table
    addu  $t1, $t1, $t0
    lw    $t0, 0($t1)
    jr    $t0

Sunday:
    li $t0, 'S'
    sb $t0, 0($a0)
    li $t0, 'u'
    sb $t0, 1($a0)
    li $t0, 'n'
    sb $t0, 2($a0)
    li $t0, 'd'
    sb $t0, 3($a0)
    li $t0, 'a'
    sb $t0, 4($a0)
    li $t0, 'y'
    sb $t0, 5($a0)
    sb $zero, 6($a0)
    j Valid

Monday:
    li $t0, 'M'
    sb $t0, 0($a0)
    li $t0, 'o'
    sb $t0, 1($a0)
    li $t0, 'n'
    sb $t0, 2($a0)
    li $t0, 'd'
    sb $t0, 3($a0)
    li $t0, 'a'
    sb $t0, 4($a0)
    li $t0, 'y'
    sb $t0, 5($a0)
    sb $zero, 6($a0)
    j Valid

Tuesday:
    li $t0, 'T'
    sb $t0, 0($a0)
    li $t0, 'u'
    sb $t0, 1($a0)
    li $t0, 'e'
    sb $t0, 2($a0)
    li $t0, 's'
    sb $t0, 3($a0)
    li $t0, 'd'
    sb $t0, 4($a0)
    li $t0, 'a'
    sb $t0, 5($a0)
    li $t0, 'y'
    sb $t0, 6($a0)
    sb $zero, 7($a0)
    j Valid

Wednesday:
    li $t0, 'W'
    sb $t0, 0($a0)
    li $t0, 'e'
    sb $t0, 1($a0)
    li $t0, 'd'
    sb $t0, 2($a0)
    li $t0, 'n'
    sb $t0, 3($a0)
    li $t0, 'e'
    sb $t0, 4($a0)
    li $t0, 's'
    sb $t0, 5($a0)
    li $t0, 'd'
    sb $t0, 6($a0)
    li $t0, 'a'
    sb $t0, 7($a0)
    li $t0, 'y'
    sb $t0, 8($a0)
    sb $zero, 9($a0)
    j Valid

Thursday:
    li $t0, 'T'
    sb $t0, 0($a0)
    li $t0, 'h'
    sb $t0, 1($a0)
    li $t0, 'u'
    sb $t0, 2($a0)
    li $t0, 'r'
    sb $t0, 3($a0)
    li $t0, 's'
    sb $t0, 4($a0)
    li $t0, 'd'
    sb $t0, 5($a0)
    li $t0, 'a'
    sb $t0, 6($a0)
    li $t0, 'y'
    sb $t0, 7($a0)
    sb $zero, 8($a0)
    j Valid

Friday:
    li $t0, 'F'
    sb $t0, 0($a0)
    li $t0, 'r'
    sb $t0, 1($a0)
    li $t0, 'i'
    sb $t0, 2($a0)
    li $t0, 'd'
    sb $t0, 3($a0)
    li $t0, 'a'
    sb $t0, 4($a0)
    li $t0, 'y'
    sb $t0, 5($a0)
    sb $zero, 6($a0)
    j Valid

Saturday:
    li $t0, 'S'
    sb $t0, 0($a0)
    li $t0, 'a'
    sb $t0, 1($a0)
    li $t0, 't'
    sb $t0, 2($a0)
    li $t0, 'u'
    sb $t0, 3($a0)
    li $t0, 'r'
    sb $t0, 4($a0)
    li $t0, 'd'
    sb $t0, 5($a0)
    li $t0, 'a'
    sb $t0, 6($a0)
    li $t0, 'y'
    sb $t0, 7($a0)
    sb $zero, 8($a0)
    j Valid # could also fall through to Valid

Valid:
    li    $v0, 1
    jr    $ra

Invalid:
    li    $v0, 0
    jr    $ra

Exit:
