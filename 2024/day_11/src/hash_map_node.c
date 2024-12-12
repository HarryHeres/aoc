#include <hash_map_node.h>
#include <stdlib.h>

HashMapNode* hash_map_node_init(const uint64_t stone_id, const uint16_t remaining_iters) {
  HashMapNode* this = (HashMapNode*)malloc(sizeof(HashMapNode));

  this->stone_id = stone_id;
  this->remaining_iters = remaining_iters;
  this->count = 0;
  this->next = NULL;

  return this;
}

void hash_map_node_free(HashMapNode* this) {
  if (this->next != NULL) {
    hash_map_node_free(this->next);
  }

  free(this);
}
