#include <linked_list.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

LinkedList *linked_list_init(void) {
  LinkedList *this = (LinkedList *)malloc(sizeof(Node));

  this->head = NULL;
  this->count = 0;

  return this;
}

void linked_list_add(LinkedList *this, const uint64_t idx, Node *to_add) {
  if (idx > this->count) {
    printf("Invalid index\n");
    return;
  }

  ++this->count;
  if (this->head == NULL) {
    this->head = to_add;
    return;
  }

  if (idx == 0) {
    to_add->next = this->head;
    this->head = to_add;
    return;
  }

  Node *curr = this->head;
  for (uint64_t i = 0; i < idx - 1; ++i) {
    curr = curr->next;
    if (curr == NULL) {
      printf("Invalid next node\n");
      return;
    }
  }

  to_add->next = curr->next;
  curr->next = to_add;
}

Node *linked_list_get(LinkedList *this, const uint64_t idx) {
  if (idx > this->count) {
    printf("Invalid index\n");
    return NULL;
  }

  Node *rv = this->head;
  for (uint64_t i = 0; i < idx; ++i) {
    if (rv->next == NULL) {
      printf("Invalid next node\n");
      return NULL;
    }

    rv = rv->next;
  }

  return rv;
}

void linked_list_free(LinkedList *this) {
  node_free(this->head);
  free(this);
}

void node_free(Node *this) {
  if (this == NULL) {
    return;
  }

  if (this->next != NULL) {
    node_free(this->next);
  }
  free(this);
}
