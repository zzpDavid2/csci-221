#include <stdio.h>
#include <stdlib.h>

// Recursive function to compute the nth Fibonacci number
// Base cases: fibonacci(0) = 0, fibonacci(1) = 1
// For n > 1, returns fibonacci(n-1) + fibonacci(n-2)
int fibonacci(int n){
    if(n <= 1) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}

int main(int argc, char *argv[]) {
    // Check if the user provided a command-line argument
    if (argc < 2) {
        printf("Usage: %s <positive integer>\n", argv[0]);
        return 1;
    }

    // Convert the argument to an integer
    int n = atoi(argv[1]);

    // Validate that the input is a non-negative integer
    if (n < 0) {
        printf("Please enter a positive integer.\n");
        return 1;
    }

    // Compute and print the nth Fibonacci number
    printf("%d\n", fibonacci(n));
    return 0;
}