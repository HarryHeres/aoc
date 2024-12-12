#ifndef _ARRAY_LIST_
#define _ARRAY_LIST_

#include <array_list_node.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct ArrayList {
  uint64_t count;
  uint64_t capacity;
  ArrayListNode **head;
} ArrayList;

ArrayList *array_list_init(const uint64_t capacity);

void array_list_add(ArrayList *const this, ArrayListNode *const value);

ArrayListNode *array_list_get(const ArrayList *this, const uint64_t index);

bool array_list_contains(const ArrayList *this, const ArrayListNode *value);

void array_list_clear(ArrayList *this);

void array_list_free(ArrayList *this);

#endif
