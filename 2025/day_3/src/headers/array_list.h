#ifndef _ARRAY_LIST
#define _ARRAY_LIST

#include <stdio.h>

typedef struct {
  void *value;
} ArrayListItem;

typedef struct {
  int size;
  int capacity;
  ArrayListItem *_items;
} ArrayList;

ArrayList *array_list_create(int initial_capacity);

void array_list_add(ArrayList *list, void *item);

void *array_list_get(const ArrayList *list, int index);

void array_list_clear(ArrayList *list);

void array_list_free(ArrayList *list);

#endif
