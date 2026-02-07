#include <stdint.h>

#ifndef DISTANCE_H
#define DISTANCE_H

typedef struct distance_t {
    uint32_t inches;
    uint32_t feets;
    uint32_t yards;
    uint32_t miles;
} distance_t;

float distance_english_to_metric(distance_t distance);
/*
    Takes a distance structure in English units (inches, feets, yards, miles) 
    and returns the total distance as a sum in meters.
*/

#endif // DISTANCE_H
