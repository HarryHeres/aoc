#ifndef _MAP_
#define _MAP_

#include <hash_map_node.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct HashMap {
  uint32_t capacity;
  HashMapNode **values;
} HashMap;

HashMap *hash_map_init(const uint32_t capacity);

void hash_map_put(HashMap *this, uint32_t key, HashMapNode *const value);

HashMapNode *hash_map_get(HashMap *const this, const uint32_t key);

void hash_map_free(HashMap *this);

#endif
