#include <hash_map.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

HashMap *hash_map_init(const uint32_t capacity) {
  if (capacity < 1) {
    return NULL;
  }

  HashMap *map = (HashMap *)malloc(sizeof(HashMap));
  if (map == NULL) {
    printf("ERROR: Unable to allocate memory for HashMap\n");
    return NULL;
  }

  map->capacity = capacity;

  map->values = (HashMapNode **)malloc(capacity * sizeof(HashMapNode *));
  if (map->values == NULL) {
    printf("Unable to allocate memory for HashMap values\n");
    return NULL;
  }
  memset(map->values, 0, capacity * sizeof(HashMapNode *));

  return map;
}

void hash_map_put(HashMap *this, uint32_t key, HashMapNode *const value) {
  if (this == NULL) {
    printf("Cannot add values to a NULL hash map\n");
  }

  key %= this->capacity;
  HashMapNode *curr = this->values[key];
  if (curr == NULL) {
    this->values[key] = value;
    return;
  }

  while (curr->next != NULL) {
    curr = curr->next;
  }

  curr->next = value;
}

HashMapNode *hash_map_get(HashMap *const this, const uint32_t key) {
  if (this == NULL) {
    printf("Cannot return values from a NULL hash map\n");
    return NULL;
  }

  return this->values[key];
}

void hash_map_free(HashMap *this) {
  for (uint32_t i = 0; i < this->capacity; ++i) {
    if (this->values[i] != NULL) {
      hash_map_node_free(this->values[i]);
    }
  }

  free(this->values);
  free(this);
}
