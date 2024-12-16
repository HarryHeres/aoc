#ifndef _DIRECTION_
#define _DIRECTION_

#include <stdint.h>

typedef struct Direction {
  int32_t x;
  int32_t y;
} Direction;

const Direction DIRECTIONS[] = {
    (Direction){.x = 0, .y = -1},  // NORTH
    (Direction){.x = 1, .y = 0},   // EAST
    (Direction){.x = 0, .y = 1},   // SOUTH
    (Direction){.x = -1, .y = 0},  // WEST
};

#endif
