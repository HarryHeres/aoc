#ifndef _MAP_NODE_
#define _MAP_NODE_

#include <stdint.h>

typedef struct HashMapNode {
  char* key;
  uint64_t value;
} HashMapNode;

#endif
