# Assembly Basics Assignment Writeup

## Overview

All four problems are implemented and working correctly based on testing. No known errors remain. Some test setup uses pseudoinstructions like `la` but the implementations never used pseudoinstructions.

---

## Question 1: Fibonacci

The code uses a count-down loop, initializing the current value to 1 and the result ($v0) to 0, then iterating $a0 times. Each iteration computes the next Fibonacci number by summing the previous two, shifts the values forward, and decrements the counter.

### Tests

| Input (n) | Expected $v0 | Result |
|-----------|-------------|--------|
| 0         | 0           | 0 ✓    |
| 1         | 1           | 1 ✓    |
| 7         | 13          | 13 ✓   |
| 8         | 21          | 21 ✓   |
| 10        | 55          | 55 ✓   |

The n=0 and n=1 cases test boundary conditions.

---

## Question 2: Array Counting

The code iterates the array from index length-1 down to 0. For each element, it uses floating-point comparisons (`c.lt.s`) to classify it into one of three buckets: smaller than low ($s0), in [low, high) ($s1), or >= high ($s2).

### Tests

**Test:** array = [0.5, 1.0, 2.0, 3.5, 4.0], low = 1.0, high = 3.5

- 0.5 < 1.0 → smaller
- 1.0 is in [1.0, 3.5) → between
- 2.0 is in [1.0, 3.5) → between
- 3.5 >= 3.5 → larger
- 4.0 >= 3.5 → larger

Expected: $s0=1, $s1=2, $s2=2. Got: $s0=1, $s1=2, $s2=2 ✓

This test exercises all three buckets and specifically tests the boundary values (1.0 and 3.5) to verify the inclusive/exclusive logic is correct.

---

## Question 3: Array Permutation

The code iterates from index 0 to length-1. For each index i, it loads array[i] and array[permutations[i]], then stores them back in swapped positions.

### Tests

**Test:** array = [10, 20, 30, 40, 50], permutations = [1, 2, 3, 4, 0]

Tracing the swaps:
- i=0: swap(array[0], array[1]) → [20, 10, 30, 40, 50]
- i=1: swap(array[1], array[2]) → [20, 30, 10, 40, 50]
- i=2: swap(array[2], array[3]) → [20, 30, 40, 10, 50]
- i=3: swap(array[3], array[4]) → [20, 30, 40, 50, 10]
- i=4: swap(array[4], array[0]) → [10, 30, 40, 50, 20]

Expected: [10, 30, 40, 50, 20]. Got: [10, 30, 40, 50, 20] ✓

---

## Question 4: Linked List Product

The code traverses the linked list, multiplying a running 64-bit product (stored in $v1:$v0 as high:low) by each node's 16-bit value. Each step requires two `multu` instructions: one to multiply the low word and capture the carry into HI, and one to multiply the high word, then the new high word is the sum of those two results.

Node layout in memory: 16-bit value at offset 0, 2 bytes of explicit padding, 32-bit next pointer at offset 4 (8 bytes total per node). 

### Tests

**Test 1:** 2 → 3 → 4 → null

Expected: $v0=24, $v1=0. Got: $v0=24, $v1=0 ✓

**Test 2:** 2000 → 2000 → 2000 → null (product = 8,000,000,000, exceeds 32 bits)

Expected: $v0=0xDCD65000, $v1=0x1. Got: $v0=0xDCD65000, $v1=0x1 ✓

Test 2 specifically verifies that the 64-bit overflow case is handled correctly, confirming that the carry from the low word multiplication is correctly propagated into the high word.
