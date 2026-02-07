#include <stdio.h>
#include <stdint.h>
#include "powers.h"
#define DEBUG 1

uint32_t powers(uint64_t n){

    uint32_t count = 0;
    for (uint32_t a = 2; a <= n; a++) {
        for (uint32_t b = 2; b <= (n/2); b++) {
            uint64_t power = 1;
            for (uint32_t i = 0; i < b; i++) {
                power *= a;
                if (power > n) {
                    break; // No need to continue if power exceeds n
                }
            }
            if (power <= n) {
                count++;
                #if DEBUG == 1
                printf("Found pair: (a=%u, b=%u) => %llu\n", a, b, power);
                #endif
            } else {
                break; // No need to continue with larger b values
            }
        }
    }

    return count;
}
