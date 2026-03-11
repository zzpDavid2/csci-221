# Integer Operations Writeup



## `masking(uint8_t first, uint8_t last)`
This function creates a bitmask with bits set from position `first` to position `last` (inclusive).

**Implementation Strategy:**
- Start with `UINT32_MAX` (all bits set to 1)
- Create a left mask by shifting left by `first` positions, clearing all bits below `first`
- Create a right mask by shifting left by `last+1` positions, clearing all bits from `last+1` onward
- XOR the two masks to isolate the desired bit range

**Test Cases:**
- `masking(3, 5)` → `111000` (binary) = 56 (decimal) - bits 3, 4, 5 are set
- `masking(0, 30)` → 2,147,483,647 - all bits except the sign bit
- `masking(0, 31)` → 4,294,967,295 (UINT32_MAX) - all bits set

## `logical_negation(uint32_t x)`
This function performs logical negation by XORing with UINT32_MAX. 

## `handle_overflow(uint32_t a, uint32_t b)`
This function handles overflow when adding two 32-bit unsigned integers by returning the result as a 64-bit unsigned integer.

**Implementation:**
- Performs addition of two uint32_t values
- Checks if overflow occurred by verifying if the result is less than either operand
- If overflow is detected, returns the sum plus 2^32 (UINT32_MAX + 1) to represent the overflow into the next word
- Otherwise, returns the sum as-is

**Test Case:**
- `handle_overflow(UINT32_MAX, 1)` → `4,294,967,296` (2^32)
  - This correctly represents that UINT32_MAX + 1 exceeds a 32-bit value and must be stored in 64 bits
