#include <complex.h>
#include <map.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

Map *map_create(const uint32_t capacity) {
  if (capacity < 1) {
    return NULL;
  }

  Map *map = (Map *)malloc(sizeof(Map));
  map->capacity = capacity;
  map->values = (ArrayList **)malloc(capacity * sizeof(ArrayList *));

  for (uint32_t i = 0; i < capacity; ++i) {
    map->values[i] = array_list_init(capacity);
  }
  return map;
}

void map_put(Map *this, const uint16_t key, const uint16_t value) {
  ArrayList *values = map_get(this, key);
  array_list_add(values, value);
}

ArrayList *map_get(const Map *this, const uint16_t key) {
  return this->values[key];
}

bool map_contains(const Map *this, const uint16_t key, const uint16_t value) {
  const ArrayList *values = this->values[key];
  return array_list_contains(values, value);
}

void map_free(Map *this) {
  for (uint32_t i = 0; i < this->capacity; ++i) {
    array_list_free(this->values[i]);
  }

  free(this->values);
}
