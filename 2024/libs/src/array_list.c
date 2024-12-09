#include <array_list.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ArrayList *array_list_init(const uint64_t capacity) {
  ArrayList *list = (ArrayList *)malloc(sizeof(ArrayList));
  list->count = 0;
  list->capacity = capacity;
  list->head = (uint64_t *)malloc(capacity * sizeof(uint64_t));

  memset(list->head, 0, capacity * sizeof(uint64_t));

  return list;
}

void array_list_add(ArrayList *this, uint64_t value) {
  if (this->count == this->capacity) {
    printf("Array list is full!\n");
    return;
  }

  this->head[this->count] = value;
  ++this->count;
}

uint64_t array_list_get(const ArrayList *this, const uint64_t index) {
  if (index > this->capacity) {
    printf("Invalid array list index\n");
    return 0;
  }
  return this->head[index];
}

bool array_list_contains(const ArrayList *this, const uint64_t value) {
  for (uint64_t i = 0; i < this->count; ++i) {
    if (this->head[i] == value) {
      return true;
    }
  }

  return false;
}

void array_list_print(ArrayList *this) {
  for (uint64_t i = 0; i < this->count; ++i) {
    printf("%d", array_list_get(this, i));
  }
  printf("\n");
}

void array_list_clear(ArrayList *this) {
  memset(this->head, 0, this->capacity * sizeof(uint64_t));
  this->count = 0;
}

void array_list_free(ArrayList *this) {
  free(this->head);
  free(this);
}
