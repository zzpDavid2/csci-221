#include <stdio.h>

int test1[] = {3, 8, 12, 20};
int test2[] = {5, 3, 1};
int test3[] = {5, 6, 7, 6};
int test4[] = {6, 7, 8};
int test5[] = {4};
int test6[] = {};

int find_divisors(int numbers[], int length){
    for (int i =0; i<length; i++){
        for (int j = 0; j < length; j++) {
            if(i==j) continue; //skip if same index
            if (numbers[i] % numbers[j] == 0) {
                return numbers[j] + numbers[i];
            }
        }
    }
    return 0;
}

int main() {
    // Test the choose_mover function

    printf("%d\n", find_divisors(test1, 4)); // Expected output: 15
    printf("%d\n", find_divisors(test2, 3)); // Expected output: 6 or 4
    printf("%d\n", find_divisors(test3, 4)); // Expected output: 12
    printf("%d\n", find_divisors(test4, 3)); // Expected output: 0
    printf("%d\n", find_divisors(test5, 1)); // Expected output: 0
    printf("%d\n", find_divisors(test6, 0)); // Expected output: 0
    return 0;
}