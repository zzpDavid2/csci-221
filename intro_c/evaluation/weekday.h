#include <stdint.h>

#ifndef WEEKDAY_H
#define WEEKDAY_H

typedef enum day {
    SUNDAY=1,
    MONDAY=2,
    TUESDAY=3,
    WEDNESDAY=4,
    THURSDAY=5,
    FRIDAY=6,
    SATURDAY=7
} day;

char* weekday(char* charecters, enum day numerical);
/*
    Sets the value of the charecters array to the name of the day corresponding to the numerical input.
*/

#endif // DISTANCE_H
