#include <stdio.h>
#include <stdint.h>
#include "weekday.h"
#define DEBUG 1

char* weekday(char* charecters, enum day numerical) {
    const char* day_str = NULL;
    
    switch (numerical) {
        case SUNDAY:
            day_str = "SUNDAY";
            break;
        case MONDAY:
            day_str = "MONDAY";
            break;
        case TUESDAY:
            day_str = "TUESDAY";
            break;
        case WEDNESDAY:
            day_str = "WEDNESDAY";
            break;
        case THURSDAY:
            day_str = "THURSDAY";
            break;
        case FRIDAY:
            day_str = "FRIDAY";
            break;
        case SATURDAY:
            day_str = "SATURDAY";
            break;
        default:
            day_str = "INVALID";
    }
    
    // Copy string character by character
    int i = 0;
    while (day_str[i] != '\0') {
        charecters[i] = day_str[i];
        i++;
    }
    charecters[i] = '\0';  // null terminate

    #if DEBUG == 1
    printf("Numerical input: %d => Day: %s\n", numerical, charecters);
    #endif

    return charecters;
}
