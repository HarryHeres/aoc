#ifndef _ARRAY_LIST_
#define _ARRAY_LIST_

#include <stdbool.h>
#include <stdint.h>

typedef struct ArrayList {
  uint64_t count;
  uint64_t capacity;
  uint64_t *head;
} ArrayList;

ArrayList *array_list_init(const uint64_t capacity);

void array_list_add(ArrayList *this, const uint64_t value);

uint64_t array_list_get(const ArrayList *this, const uint64_t index);

bool array_list_contains(const ArrayList *this, const uint64_t value);

void array_list_clear(ArrayList *this);

void array_list_print(ArrayList *this);

void array_list_free(ArrayList *this);

#endif
