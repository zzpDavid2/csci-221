#include <stdint.h>
#include <stdio.h>
#include "moving.h"
#include "powers.h"
#include "distance.h"
#include "weekday.h"

int main(void) {
    // Test the choose_mover function
    printf("Testing choose_mover:\n");
    printf("%c\n", choose_mover(1)); // Expected output: A
    printf("%c\n", choose_mover(24)); // Expected output: B
    printf("%c\n", choose_mover(31)); // Expected output: A
    printf("%c\n", choose_mover(690)); // Expected output: B

    // Test the powers function
    printf("\nTesting powers:\n");
    printf("%u\n", powers(1)); // Expected output: 0
    printf("%u\n", powers(4)); // Expected output: 1 (2^2 = 4)
    printf("%u\n", powers(10)); // Expected output: 2 (2^2 = 4, 2^3=6, 3^2 = 9)
    printf("%u\n", powers(18)); // Expected output: 5

    // Test the distance_english_to_metric function
    printf("\nTesting distance_english_to_metric:\n");
    distance_t distance1 = {0, 0, 0, 0}; // Expected output: 0.000000 meters
    distance_t distance2 = {12, 3, 2, 1}; // Expected output: 1619.392 meters
    distance_t distance3 = {36, 0, 1, 0}; // Expected output: 1.828800 meters
    printf("%f\n", distance_english_to_metric(distance1));
    printf("%f\n", distance_english_to_metric(distance2));
    printf("%f\n", distance_english_to_metric(distance3));

    // Test the weekday function
    printf("\nTesting weekday:\n");
    char day_name[10]; // Char array to hold the day name
    weekday(day_name, SUNDAY); // Expected output: SUNDAY
    printf("%s\n", day_name);
    weekday(day_name, MONDAY); // Expected output: MONDAY
    printf("%s\n", day_name);
    weekday(day_name, 11); // Expected output: INVALID DAY
    printf("%s\n", day_name); 

    return 0;
}
