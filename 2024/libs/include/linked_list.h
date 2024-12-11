#ifndef _LINKED_LIST_
#define _LINKED_LIST_

#include <stdint.h>

typedef struct Node {
  uint64_t value;
  struct Node *next;
} Node;

typedef struct LinkedList {
  Node *head;
  uint64_t count;
} LinkedList;

LinkedList *linked_list_init(void);

void linked_list_add(LinkedList *this, const uint64_t idx, Node *to_add);

Node *linked_list_get(LinkedList *this, const uint64_t idx);

void linked_list_free(LinkedList *this);

void node_free(Node *this);

#endif
