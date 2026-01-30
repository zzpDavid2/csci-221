#include <stdio.h>
#include <stdlib.h>

// Recursive function to compute the nth Fibonacci number
// Base cases: fibonacci(0) = 0, fibonacci(1) = 1
// For n > 1, returns fibonacci(n-1) + fibonacci(n-2)
int string_length(char string[]){
    int n=0;
    while(string[n] != '\0'){
        n++; // count characters
    }
    n++; // count the null terminator
    return n;
}

char* copy_string(char string[]){
    int n = string_length(string);
    char* ret = malloc(n * sizeof(char));
    for(int i=0; i<n; i++){
        ret[i] = string[i];
    }
    return ret;
}

int main() {
    char str[] = "Hello, World!";
    char* copy = copy_string(str);
    printf("Original: %s\n", str);
    printf("Copy: %s\n", copy);
    printf("Length: %d\n", string_length(str));
    free(copy);
    return 0;
}