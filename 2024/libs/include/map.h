#ifndef _MAP_
#define _MAP_

#include <hashmapnode.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct HashMap {
  uint64_t capacity;
  HashMapNode *values;
} HashMap;

HashMap *hashmap_create(const uint32_t capacity);

void hashmap_put(HashMap *this, HashMapNode *key);

HashMapNode *hashmap_get(const HashMap *this, const HashMapNode *key);

bool hashmap_contains(const HashMap *this, const HashMapNode *key);

void hashmap_free(HashMap *this);

#endif
