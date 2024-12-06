#ifndef _DIRECTION_
#define _DIRECTION_

#include <stdint.h>

typedef struct Direction {
  int32_t x;
  int32_t y;
} Direction;

// NORTH, EAST, SOUTH, WEST
const Direction DIRECTIONS[] = {(Direction){.x = 0, .y = -1}, (Direction){.x = 1, .y = 0}, (Direction){.x = 0, .y = 1},
                                (Direction){.x = -1, .y = 0}};

#endif
