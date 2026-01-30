#include <stdio.h>

//Define constants for box sizes and prices
int a_box = 23;
int a_price = 200;
int b_box = 30;
int b_price = 260;

char choose_mover(int n){

    // Calculate the total price for each mover
    a_price = 200 * (n/a_box+1); //the +1 is to account for partial boxes
    b_price = 260 * (n/b_box+1);

    // Compare the total prices and choose the cheaper mover
    if (a_price < b_price) {
        return 'A';
    } else {
        return 'B';
    }
}

int main() {
    // Test the choose_mover function
    printf("%c\n", choose_mover(1)); // Expected output: A
    printf("%c\n", choose_mover(24)); // Expected output: B
    printf("%c\n", choose_mover(31)); // Expected output: A
    return 0;
}