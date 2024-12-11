#include <complex.h>
#include <map.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

HashMap *hashmap_create(const uint64_t capacity) {
  if (capacity < 1) {
    return NULL;
  }

  HashMap *map = (HashMap *)malloc(sizeof(HashMap));

  map->capacity = capacity;

  map->values = (MapNode **)malloc(capacity * sizeof(MapNode *));
  memset(map->value, 0, capacity * sizeof(MapNode *));

  return map;
}

void map_put(Map *this, const uint64_t key, const MapNode *value) {
  map->values[i] = value;
}

MapNode *map_get(const Map *this, const uint64_t key) {
  return this->values[key];
}

bool map_contains(const Map *this, const uint64_t key, const uint64_t value) {
  const MapNode *value = this->values[key];
  return value != NULL;
}

void map_free(Map *this) {
  for (uint64_t i = 0; i < this->capacity; ++i) {
    if (this->values[i] != NULL) {
      map_node_free(this->value[i]);
    }
  }

  free(this->values);
}
