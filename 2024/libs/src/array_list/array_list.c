#include <array_list.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ArrayList *array_list_init(const uint64_t capacity) {
  if (capacity < 1) {
    printf("ERROR: Array list capacity cannot be lower than 1\n");
    return NULL;
  }

  ArrayList *list = (ArrayList *)malloc(sizeof(ArrayList));
  if (list == NULL) {
    printf("ERROR: Unable to allocate space for array list\n");
    return NULL;
  }

  list->count = 0;
  list->capacity = capacity;
  list->head = (ArrayListNode **)malloc(capacity * sizeof(ArrayListNode *));
  if (list->head == NULL) {
    printf("ERROR: Unable to allocate space for array list nodes\n");
    return NULL;
  }

  memset(list->head, 0, capacity * sizeof(ArrayListNode *));

  return list;
}

void array_list_add(ArrayList *const this, ArrayListNode *const value) {
  if (this == NULL) {
    printf("ERROR: Cannot add element to a NULL array list\n");
    return;
  }
  if (this->count == this->capacity) {
    printf("ERROR: Array list is full\n");
    return;
  }

  if (value == NULL) {
    printf("ERROR: Adding a NULL value to array list is not allowed\n");
    return;
  }

  this->head[this->count] = value;
  ++this->count;
}

ArrayListNode *array_list_get(const ArrayList *const this,
                              const uint64_t index) {
  if (this == NULL) {
    printf("ERROR: Cannot get elements from NULL array list\n");
    return NULL;
  }

  if (index > this->capacity) {
    printf("ERROR: Index out of bounds for this array list\n");
    return NULL;
  }

  return this->head[index];
}

bool array_list_contains(const ArrayList *const this,
                         const ArrayListNode *const value) {
  if (this == NULL) {
    printf("ERROR: Cannot check if element is present in a NULL array list\n");
    return false;
  }

  for (uint64_t i = 0; i < this->count; ++i) {
    if (this->head[i] == value) {
      return true;
    }
  }

  return false;
}

void array_list_remove(const ArrayList *this, const uint64_t index) {
  if (index > this->count) {
    printf("Invalid index to remove");
    return;
  }

  this->head[index] = NULL;
}

void array_list_clear(ArrayList *const this) {
  memset(this->head, 0, this->capacity * sizeof(ArrayListNode *));
  this->count = 0;
}

void array_list_free(ArrayList *this) {
  array_list_node_free(this->head);
  free(this);
}
