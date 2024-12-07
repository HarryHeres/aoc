#ifndef _MAP_
#define _MAP_

#include <array_list.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
  uint32_t capacity;
  ArrayList** values;
} Map;

Map* map_create(const uint32_t capacity);

void map_put(Map* this, const uint16_t key, const uint16_t value);

ArrayList* map_get(const Map* this, const uint16_t key);

bool map_contains(const Map* this, const uint16_t key, const uint16_t value);

void map_free(Map* this);

#endif
