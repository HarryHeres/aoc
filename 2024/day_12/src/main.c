#include <array_list.h>
#include <main.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "direction.h"

const char INPUT_FILENAME[] = "data/input_test_2.txt";
const uint16_t ROWS = 4;
const uint16_t COLS = 4;

int main(void) {
  FILE* file = fopen(INPUT_FILENAME, "r");
  if (access(INPUT_FILENAME, F_OK) != 0) {
    printf("File %s not found. Exiting...\n", INPUT_FILENAME);
    return EXIT_FAILURE;
  }

  fseek(file, 0, SEEK_END);
  if (ftell(file) == 0) {
    fclose(file);
    printf("File %s is empty. Exiting...\n", INPUT_FILENAME);
    return EXIT_FAILURE;
  }

  fseek(file, 0, SEEK_SET);
  printf("Part one: %llu \n", part_one(file));

  fseek(file, 0, SEEK_SET);
  printf("Part two: %llu\n", part_two(file));

  return EXIT_SUCCESS;
}

uint64_t part_one(FILE* file) {
  char line[COLS + 2];
  memset(line, '\0', sizeof(line));

  Point* map[ROWS * COLS];
  memset(map, '\0', sizeof(map));

  uint32_t map_idx = 0;
  while (fgets(line, sizeof(line), file) != NULL) {
    for (uint32_t i = 0; i < COLS; ++i) {
      map[map_idx * COLS + i] = point_init(line[i], i, map_idx);
    }

    ++map_idx;
  }

  uint64_t sum = 0;

  for (uint32_t i = 0; i < ROWS * COLS; ++i) {
    if (map[i]->visited == false) {
      sum += process_region(map, i);
    }
  }

  for (uint32_t i = 0; i < ROWS * COLS; ++i) {
    point_free(map[i]);
  }

  return sum;
}

uint32_t process_region(Point** map, uint32_t start_idx) {
  Point* list[ROWS * COLS];
  memset(list, 0, sizeof(list));

  list[0] = map[start_idx];

  Point* curr = list[0];
  Point* next = NULL;

  int32_t next_x = 0;
  int32_t next_y = 0;
  uint32_t curr_idx = 0;
  uint32_t next_idx = 1;
  uint32_t borders_count = 0;
  while (curr != NULL) {
    const Direction* curr_dir;

    for (uint32_t i = 0; i < sizeof(DIRECTIONS) / sizeof(Direction); ++i) {
      curr_dir = &DIRECTIONS[i];

      next_x = curr->x + curr_dir->x;
      next_y = curr->y + curr_dir->y;

      if (next_x < 0 || next_x >= COLS || next_y < 0 || next_y >= ROWS) {
        ++curr->borders;
        continue;
      }

      next = map[next_x + next_y * COLS];
      if (next->type == curr->type) {
        if (next->visited == false) {
          list[next_idx] = next;
          ++next_idx;
        }
      } else {
        ++curr->borders;
      }
    }

    curr->visited = true;
    borders_count += curr->borders;
    ++curr_idx;
    curr = list[curr_idx];
  }

  printf("%c: %d x %d\n", curr->type, borders_count, curr_idx + 1);

  return borders_count * (curr_idx + 1);
}

uint64_t part_two(FILE* file) {
  return 0;
}
