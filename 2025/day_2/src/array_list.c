#include "./headers/array_list.h"
#include <stdlib.h>

ArrayList *array_list_create(int initial_capacity) {
  if (initial_capacity < 1) {
    return NULL;
  }

  ArrayList *rv = (ArrayList *)malloc(sizeof(ArrayList));

  rv->_items = malloc(initial_capacity * sizeof(ArrayListItem));
  if (rv->_items == NULL) {
    free(rv);
    return NULL;
  }

  rv->size = 0;
  rv->capacity = initial_capacity;

  return rv;
}

void array_list_add(ArrayList *list, void *item) {
  if (item == NULL || list == NULL) {
    return;
  }

  if (list->size == list->capacity) {
    list->_items =
        realloc(list->_items, list->capacity * 2 * sizeof(ArrayListItem));
  }

  list->_items[list->size++].value = item;
}

void *array_list_get(const ArrayList *list, int index) {
  if (index >= list->size || index < 0) {
    return NULL;
  }

  return list->_items[index].value;
}

void array_list_free(ArrayList *list) {
  if (list == NULL) {
    return;
  }

  if (list->_items != NULL) {
    for (int i = 0; i < list->size; ++i) {
      free(list->_items[i].value);
    }

    free(list->_items);
  }

  free(list);
}
