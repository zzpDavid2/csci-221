#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main (int argc, char *argv[]) {
    //-Werror does not like unused parameters
    (void)argc;
    (void)argv;
    
    printf("Hello, World!");

    u_int64_t arr[2026];
    size_t arr_size = 2026;

    for (size_t i = 0; i < arr_size; i++)
    {
        arr[i] = 0;
    }
    

    return 0;
}
// -Werror requires a new line at the end of the file
