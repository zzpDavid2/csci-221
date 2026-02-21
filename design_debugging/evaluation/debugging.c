#include <stdio.h>
#include <stdint.h>

unsigned int f(unsigned int x, unsigned int y) {
    int r = 1;
    int s = x;
    while (y > 1) {
        if (y % 2 == 1) {
            r = x * r;
        }
        s = s * s;
        y = y / 2;
        printf("r=%u\n", r);
        printf("s=%u\n", s);
        printf("y=%u\n\n", y);
    }
    return r * s;
}

// 7=(6)+1 = (3*2)+1 =  ((2+1)*2)+1 = 4 + 2 + 1

uint32_t exponent(uint32_t base, uint32_t power){
    // the function compute base^power in a fasion similar to converting numbers into binary
    uint32_t result = 1;
    // I call this the current_digit_value 
    // because it resembles the 2^n value represented by the nth digit in binary.
    uint32_t current_digit_value = base; 

    while (power > 0){ // allows the loop to run once when power=1 
        if ((power % 2) == 1){ // use () here to make clear
            // multiply the result by the current power if the remainder is 1
            result = current_digit_value * result; 
            // this is unnecessary but makes the removal of the remainder more clear
            power -= 1; 
        }
        //grow the current_power by power of 2
        current_digit_value = current_digit_value * current_digit_value; 
        power = power / 2;
        printf("power=%u\n\n", power);
    }
    // don't multiply by current_power at the end so that 0th power will be correctly 1.
    return result; 
}


int main(void) {
    //2^7
    printf("%u\n", f(2,7));
    printf("%u\n\n", exponent(2,7));

    //2^1
    printf("%u\n", f(2,1));
    printf("%u\n\n", exponent(2,1));

    //2^0
    printf("%u\n", f(2,0));
    printf("%u\n\n", exponent(2,0));

    //3^13
    printf("%u\n", f(3,13));
    printf("%u\n\n", exponent(3,13));
    return 0;
}
