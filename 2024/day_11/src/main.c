#include <hash_map.h>
#include <main.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

const uint32_t ROWS = 0;
const uint32_t COLS = 36;
HashMap* LOOKUP_TABLE;

int main(void) {
  FILE* file = fopen("data/input.txt", "r");

  printf("Part one: %lu\n", process_stones(file, 25));

  file = fopen("data/input.txt", "r");
  printf("Part two: %lu\n", process_stones(file, 75));

  return EXIT_SUCCESS;
}

uint64_t process_stones(FILE* file, const uint16_t iters) {
  LOOKUP_TABLE = hash_map_init(UINT32_MAX);

  uint64_t stones[100];
  uint16_t stones_idx = 0;
  memset(stones, 0, sizeof(stones));

  char line[COLS + 2];
  memset(line, 0, sizeof(line));

  fgets(line, sizeof(line), file);

  char* id;

  id = strtok(line, " ");
  while (id != NULL) {
    stones[stones_idx] = strtol(id, NULL, 10);
    ++stones_idx;
    id = strtok(NULL, " ");
  }

  uint64_t sum = 0;
  for (uint16_t i = 0; i < stones_idx; ++i) {
    sum += process_stone(stones[i], iters);
  }

  fclose(file);
  return sum;
}

uint64_t process_stone(const uint64_t stone_id, const uint16_t remaining_iters) {
  if (remaining_iters == 0) {
    return 1;
  }

  // Check if table contains
  HashMapNode* entry = hash_map_get(LOOKUP_TABLE, stone_id);

  while (entry != NULL) {
    if (entry->stone_id == stone_id && entry->remaining_iters == remaining_iters) {
      return entry->count;
    }

    entry = entry->next;
  }

  uint64_t count = 0;
  uint64_t buffer_len = (uint64_t)floor(log10(stone_id)) + 1;

  entry = hash_map_node_init(stone_id, remaining_iters);

  if (stone_id == 0) {
    count = process_stone(1, remaining_iters - 1);
  } else if (buffer_len % 2 == 0) {
    uint64_t first_stone_id = (uint64_t)(stone_id / pow(10, (uint64_t)(buffer_len / 2.0)));
    uint64_t second_stone_id = (uint64_t)(stone_id % (uint64_t)pow(10, (uint64_t)(buffer_len / 2.0)));

    count = process_stone(first_stone_id, remaining_iters - 1) + process_stone(second_stone_id, remaining_iters - 1);
  } else {
    count = process_stone(stone_id * 2024, remaining_iters - 1);
  }

  entry->count = count;
  hash_map_put(LOOKUP_TABLE, stone_id, entry);

  return count;
}
