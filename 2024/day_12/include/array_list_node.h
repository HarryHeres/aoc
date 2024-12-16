#ifndef _ARRAY_LIST_NODE_
#define _ARRAY_LIST_NODE_

#include <point.h>

typedef struct ArrayListNode {
  Point* value;
} ArrayListNode;

void array_list_node_free(ArrayListNode* this);

#endif
