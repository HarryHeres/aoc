#ifndef _ARRAY_LIST_
#define _ARRAY_LIST_

#include <stdbool.h>
#include <stdint.h>

typedef struct ArrayList {
  uint16_t count;
  uint16_t capacity;
  uint16_t* head;
} ArrayList;

ArrayList* array_list_create(const uint16_t capacity);

void array_list_add(ArrayList* this, const uint16_t value);

uint16_t array_list_get(const ArrayList* this, const uint16_t index);

bool array_list_contains(const ArrayList* this, const uint16_t value);

void array_list_free(ArrayList* this);

#endif
