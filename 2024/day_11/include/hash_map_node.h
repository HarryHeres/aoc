#ifndef _HASH_MAP_NODE_
#define _HASH_MAP_NODE_

#include <stdint.h>

typedef struct HashMapNode {
  uint64_t stone_id;
  uint16_t remaining_iters;
  uint64_t count;
  struct HashMapNode* next;
} HashMapNode;

HashMapNode* hash_map_node_init(const uint64_t stone_id, const uint16_t remaining_iters);

void hash_map_node_free(HashMapNode* this);

#endif
