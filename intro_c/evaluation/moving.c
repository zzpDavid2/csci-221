#include <stdio.h>
#include <stdint.h>
#include "moving.h"
#define DEBUG 0

char choose_mover(uint32_t n){

    //Define constants for box sizes and prices
    uint16_t a_box_size = 23;
    uint16_t a_box_price = 200;

    uint16_t b_box_size = 30;
    uint16_t b_box_price = 260;

    // Calculate the total price for each mover
    uint32_t a_quantity = n/a_box_size;
    if (n % a_box_size != 0) {
        a_quantity += 1; // Account for partial boxes for mover A
    }
    uint32_t b_quantity = n/b_box_size;
    if (n % b_box_size != 0){
        b_quantity += 1; // Account for partial boxes for mover B
    }
    
    uint32_t a_total_price = a_box_price * a_quantity;
    uint32_t b_total_price = b_box_price * b_quantity;

    #if DEBUG == 1
    printf("Mover A: Quantity = %u, Total Price = $%u\n", a_quantity, a_total_price);
    printf("Mover B: Quantity = %u, Total Price = $%u\n", b_quantity, b_total_price);
    #endif

    // Compare the total prices and choose the cheaper mover
    if (a_total_price < b_total_price) {
        return 'A';
    } else {
        return 'B';
    }
}
