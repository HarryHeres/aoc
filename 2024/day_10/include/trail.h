#ifndef _TRAIL_
#define _TRAIL_

#include <stdbool.h>
#include <stdint.h>
typedef struct TrailPoint {
  uint32_t height;
  bool visited;
} TrailPoint;

#endif
