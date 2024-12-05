#include <array_list.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ArrayList* array_list_create(const uint16_t capacity) {
  if (capacity < 1) {
    return NULL;
  }

  ArrayList* list = (ArrayList*)malloc(sizeof(ArrayList));
  list->count = 0;
  list->capacity = capacity;
  list->head = (uint16_t*)malloc(capacity * sizeof(uint16_t));

  memset(list->head, '\0', capacity * sizeof(uint16_t));

  return list;
}

void array_list_add(ArrayList* this, uint16_t value) {
  if (this->count == this->capacity) {
    printf("Array list is full!\n");
    return;
  }
  this->head[this->count++] = value;
}

uint16_t array_list_get(ArrayList* this, const uint16_t index) {
  if (index > this->count) {
    printf("Invalid array list index\n");
    return 0;
  }
  return this->head[index];
}

bool array_list_contains(const ArrayList* this, const uint16_t value) {
  for (uint16_t i = 0; i < this->count; ++i) {
    if (this->head[i] == value) {
      return true;
    }
  }

  return false;
}

void array_list_free(ArrayList* this) {
  free(this->head);
  free(this);
}
