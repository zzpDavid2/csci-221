#include <stdio.h>
#include <stdint.h>
#include "distance.h"
#define DEBUG 0

float distance_english_to_metric(distance_t distance) {
    // Define conversion factors
    const float inches_to_meters = 0.0254;
    const float feets_to_meters = 0.3048;
    const float yards_to_meters = 0.9144;
    const float miles_to_meters = 1609.344;

    // Convert each unit to meters and sum them up

    float inches_in_meters = distance.inches * inches_to_meters;
    float feets_in_meters = distance.feets * feets_to_meters;
    float yards_in_meters = distance.yards * yards_to_meters;
    float miles_in_meters = distance.miles * miles_to_meters;

    float total_distance = inches_in_meters + feets_in_meters + yards_in_meters + miles_in_meters;

    #if DEBUG == 1
    printf("Inches: %u => %f meters\n", distance.inches, inches_in_meters);
    printf("Feets: %u => %f meters\n", distance.feets, feets_in_meters);
    printf("Yards: %u => %f meters\n", distance.yards, yards_in_meters);
    printf("Miles: %u => %f meters\n", distance.miles, miles_in_meters);
    printf("Total Distance: %f meters\n", total_distance);
    #endif

    return total_distance;
}
