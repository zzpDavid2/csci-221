#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define DEBUG 1

void reverse_print(char *str){
    // Recurse to end of string, then print characters on way back up
    if(*str!='\0'){
        reverse_print(str + 1);
    }else{
        return;
    }
    printf("%c", *str);
}

uint32_t input_integer(void){
    // Ask user for integer input
    printf("Please input an integer:\n");
    char int_str[30];
    scanf("%29s", int_str);

    // Process integer string
    char *end_ptr;
    // Convert string to integer using strtol
    int64_t repeat_num = strtol(int_str, &end_ptr, 10);
    if(end_ptr == int_str) {
        printf("Invalid integer input. Try again.\n");
        // Recursively retry
        return input_integer();
    }else if(repeat_num < 0){
        printf("Only positive integers allowed. Try again.\n");
        // Recursively retry
        return input_integer();
    }
    return repeat_num;
}

int main(int argc, char *argv[]) {
    // Get string from user
    printf("Please input a string:\n");
    char output_str[30];
    scanf("%29s", output_str);

    // Get repeat count from user
    uint32_t repeat_num = input_integer();

    bool is_reversed = false;

    // Check for optional -r flag
    if(argc > 1){
        is_reversed = (strcmp(argv[1], "-r") == 0);
    }

    // Print string repeat_num times, either normal or reversed
    for (uint32_t i = 0; i < repeat_num; i++)
    {   
        if(is_reversed){
            reverse_print(output_str);
            printf("\n");
        }else{
            printf("%s\n", output_str);
        }
    }
}
