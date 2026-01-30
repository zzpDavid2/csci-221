#include <stdio.h>
#include <math.h>

int powers(int n){
    if(n < 2) return 0; // no powers of integers < 2
    int ret = 0;
    for(int i = 2; i<n; i++){
        int j = 2;
        while (pow(i,j) <= n)
        {
            j++;
            ret++;
        }
        if (pow(i,2) > n) break; //no need to check higher bases
    }
    return ret;
}

int main() {
    // Test the powers function
    printf("%d\n", powers(18)); // Expected output: 5
    printf("%d\n", powers(0)); // Expected output: 0
    printf("%d\n", powers(3)); // Expected output: 0
    printf("%d\n", powers(4)); // Expected output: 1
    return 0;
}