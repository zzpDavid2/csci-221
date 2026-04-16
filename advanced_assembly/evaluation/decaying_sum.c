#include <stdio.h>
#include <stdint.h>

// Original
uint32_t decaying_sum_original(uint16_t* values, uint16_t length, uint16_t decay) {
    if (length <= 0) {
        return 0;
    }
    uint32_t rest = decaying_sum_original(&values[1], length - 1, decay);
    uint32_t decayed = rest / decay;
    return values[0] + decayed;
}

uint32_t decaying_sum_tail(uint16_t* values, uint32_t length, uint16_t decay, uint32_t prev){
    // works from the end of the array instead
    // prev is the decaying sum from the back that is already computed
    if (length <= 0) {
        return prev;
    }
    // decay
    prev = prev / decay;
    // reduce length
    length--;
    prev = prev + values[length];
    return decaying_sum_tail(values, length, decay, prev);
}

uint32_t decaying_sum(uint16_t* values, uint16_t length, uint16_t decay) {
    return decaying_sum_tail(values, length, decay, 0);
}

// Testing

static void run_test(const char* name, uint16_t* values, uint16_t length, uint16_t decay) {
    uint32_t expected = decaying_sum_original(values, length, decay);
    uint32_t actual   = decaying_sum(values, length, decay);
    const char* status = (expected == actual) ? "PASS" : "FAIL";
    printf("[%s] %s  expected=%u  got=%u\n", status, name, expected, actual);
}

int main(void) {
    // empty array
    run_test("empty",          (uint16_t[]){},               0, 2);

    // single element
    run_test("single",         (uint16_t[]){42},             1, 3);

    // decay=1 (sum unchanged by decay)
    run_test("decay=1",        (uint16_t[]){5, 10, 15},      3, 1);

    // decay=2, length=4
    // f([10,20,30,40]) = 10 + (20 + (30 + 40/2)/2)/2 = 32
    run_test("decay=2 len=4",  (uint16_t[]){10, 20, 30, 40}, 4, 2);

    // larger decay
    run_test("decay=10 len=3", (uint16_t[]){100, 50, 25},    3, 10);

    return 0;
}
