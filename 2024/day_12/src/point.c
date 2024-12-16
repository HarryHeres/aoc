
#include <point.h>
#include <stdlib.h>

Point* point_init(const char type, const uint32_t x, const uint32_t y) {
  Point* const this = (Point*)malloc(sizeof(Point));

  this->x = x;
  this->y = y;
  this->type = type;
  this->visited = false;
  this->borders = 0;

  return this;
}

void point_free(Point* this) {
  free(this);
}
