#include <stdint.h>

#ifndef MOVING_H
#define MOVING_H

char choose_mover(uint32_t n);
/*
Determines which mover is cheaper based on the number of items to be moved (n).
Returns 'A' if mover A is cheaper, and 'B' if mover B is cheaper.
Mover A charges $200 for every 23 items (or part thereof), while mover B charges $260 for every 30 items (or part thereof).
*/

#endif // MOVING_H
