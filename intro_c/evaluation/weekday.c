#include <stdio.h>
#include <stdint.h>
#include "weekday.h"
#define DEBUG 1

char* weekday(char* charecters, enum day numerical) {
    
    switch (numerical) {
        case SUNDAY:
            charecters = "SUNDAY";
            break;
        case MONDAY:
            charecters = "MONDAY";
            break;
        case TUESDAY:
            charecters = "TUESDAY";
            break;
        case WEDNESDAY:
            charecters = "WEDNESDAY";
            break;
        case THURSDAY:
            charecters = "THURSDAY";
            break;
        case FRIDAY:
            charecters = "FRIDAY";
            break;
        case SATURDAY:
            charecters = "SATURDAY";
            break;
        default:
            charecters = "INVALID DAY";
    }

    #if DEBUG == 1
    printf("Numerical input: %d => Day: %s\n", numerical, charecters);
    #endif

    return charecters;
}
