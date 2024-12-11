#include <hashmap.h>
#include <main.h>
#include <map.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

const uint32_t ROWS = 0;
const uint32_t COLS = 36;

int main(void) {
  FILE* file = fopen("data/input.txt", "r");

  /* printf("Part one: %lld\n", part_one(file)); */
  printf("Part two: %lld\n", part_two(file));

  return EXIT_SUCCESS;
}

uint64_t part_one(FILE* file) {
  char line[COLS + 2];
  fgets(line, sizeof(line), file);

  LinkedList* stones = linked_list_init();

  char* buffer;
  uint64_t value = 0;
  Node* node;
  buffer = strtok(line, " ");
  while (buffer != NULL) {
    value = strtol(buffer, NULL, 10);

    node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;

    linked_list_add(stones, stones->count, node);
    buffer = strtok(NULL, " ");
  }

  for (uint32_t i = 0; i < 25; ++i) {
    printf("Iteration %d\n", i + 1);
    apply_rules(stones);
  }

  /* printf("Stones: "); */
  /* node = stones->head; */
  /* for (uint64_t i = 0; i < stones->count; ++i) { */
  /*   printf("%lld ", node->value); */
  /*   node = node->next; */
  /* } */
  /* printf("\n"); */

  return stones->count;
}

void apply_rules(LinkedList* stones) {
  Node* stone = stones->head;
  char value_string[100];
  memset(value_string, 0, sizeof(value_string));

  const uint64_t stone_count_copy = stones->count;
  for (uint64_t i = 0; i < stone_count_copy; ++i) {
    sprintf(value_string, "%lld", stone->value);

    if (stone->value == 0) {
      stone->value = 1;
    } else if (strlen(value_string) % 2 == 0) {
      char value_buffer[100];
      memset(value_buffer, '\0', sizeof(value_buffer));
      char new_stone_value[100];
      memset(new_stone_value, '\0', sizeof(new_stone_value));

      const uint32_t split_idx = strlen(value_string) / 2;

      strncpy(value_buffer, value_string, split_idx);
      strncpy(new_stone_value, &value_string[split_idx], split_idx);

      Node* new_stone = (Node*)malloc(sizeof(Node));
      new_stone->value = strtoll(new_stone_value, NULL, 10);
      new_stone->next = stone->next;

      stone->value = strtol(value_buffer, NULL, 10);
      stone->next = new_stone;

      ++stones->count;

      stone = new_stone->next;
      continue;
    } else {
      stone->value *= 2024;
    }

    stone = stone->next;
  }
}

uint64_t part_two(FILE* file) {
  char line[COLS + 2];
  fgets(line, sizeof(line), file);

  ArrayList* stones[10000];
  memset(stones, 0, sizeof(stones));

  LinkedList* start = linked_list_init();

  char* buffer;
  uint64_t value = 0;
  Node* node;
  buffer = strtok(line, " ");
  while (buffer != NULL) {
    value = strtol(buffer, NULL, 10);

    node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;

    linked_list_add(start, start->count, node);

    buffer = strtok(NULL, " ");
  }

  for (uint32_t i = 0; i < start->count; ++i) {
    printf("Processed %d. th stone", i + 1);
    process_stone(stones, (&start->head[i])->value, 75);
  }

  uint64_t rv = 0;
  for (uint32_t i = 0; i < sizeof(stones) / sizeof(ArrayList*); ++i) {
    if (stones[i] == NULL) {
      break;
    }
    rv += stones[i]->head[1];
    array_list_free(stones[i]);
  }

  linked_list_free(start);

  return rv;
}

void process_stone(ArrayList** dict, const uint64_t value, const uint32_t iters) {}
