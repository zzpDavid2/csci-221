#include <stdio.h>
#include <stdint.h>
#include "weekday.h"
#define DEBUG 1

char* weekday(char* charecters, enum day numerical) {
    char* day_str = NULL;
    size_t str_length = 0;
    
    switch (numerical) {
        case SUNDAY:
            day_str = "SUNDAY";
            str_length = 6;
            break;
        case MONDAY:
            day_str = "MONDAY";
            str_length = 6;
            break;
        case TUESDAY:
            day_str = "TUESDAY";
            str_length = 7;
            break;
        case WEDNESDAY:
            day_str = "WEDNESDAY";
            str_length = 9;
            break;
        case THURSDAY:
            day_str = "THURSDAY";
            str_length = 8;
            break;
        case FRIDAY:
            day_str = "FRIDAY";
            str_length = 6;
            break;
        case SATURDAY:
            day_str = "SATURDAY";
            str_length = 8;
            break;
        default:
            day_str = "INVALID";
            str_length = 7;
    }
    
    // Copy string character by character
    for (uint8_t i = 0; i < str_length; i++) {
        charecters[i] = day_str[i];
    }

    #if DEBUG == 1
    printf("Numerical input: %d => Day: %s\n", numerical, charecters);
    #endif

    return charecters;
}
