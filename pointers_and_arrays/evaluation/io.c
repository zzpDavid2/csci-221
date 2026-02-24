#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define DEBUG 1

void reverse_print(char *str){
    if(*str!='\0'){
        reverse_print(str + 1);
    }else{
        return;
    }
    printf("%c", *str);
}

int main(int argc, char *argv[]) {
    printf("Please input a string:\n");
    char output_str[30];
    scanf("%s", output_str);

    printf("Please input an integer:\n");
    char int_str[30];
    scanf("%s", int_str);

    char *end_ptr;
    uint32_t repeat_num = strtol(int_str, &end_ptr, 10);

    bool is_reversed = false;

    if(argc > 1){
        is_reversed = (strcmp(argv[1], "-r") == 0);
    }

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
