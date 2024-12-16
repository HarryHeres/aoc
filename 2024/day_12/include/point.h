#ifndef _POINT_
#define _POINT_

#include <stdbool.h>
#include <stdint.h>

typedef struct Point {
  uint32_t x;
  uint32_t y;
  char type;
  bool visited;
  uint32_t borders;
} Point;

Point* point_init(const char type, const uint32_t x, const uint32_t y);

void point_free(Point* this);

#endif
