#include <array_list.h>
#include <direction.h>
#include <main.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <trail.h>

const uint32_t ROWS = 59;
const uint32_t COLS = 59;
const uint32_t EMPTY_SPACE_HEIGHT = 100;

int main(void) {
  FILE* file = fopen("data/input.txt", "r");

  TrailPoint map[ROWS * COLS];
  memset(map, '\0', sizeof(map));

  char line[COLS + 2];
  memset(line, '\0', sizeof(line));

  uint32_t map_idx = 0;
  ArrayList* starting_points = array_list_init(ROWS * COLS);
  while (fgets(line, sizeof(line), file) != NULL) {
    for (uint32_t i = 0; i < COLS; ++i) {
      map[map_idx * COLS + i].height = line[i] == '.' ? EMPTY_SPACE_HEIGHT : line[i] - '0';
      map[map_idx * COLS + i].visited = line[i] == '.' ? true : false;

      if (line[i] == '0') {
        array_list_add(starting_points, map_idx * COLS + i);
      }
    }

    ++map_idx;
  }

  uint64_t sum = 0;
  for (uint32_t i = 0; i < starting_points->count; ++i) {
    sum += find_trails(map, array_list_get(starting_points, i));
    reset_map(map);
  }

  printf("Result: %lld\n", sum);

  array_list_free(starting_points);
}

uint32_t find_trails(TrailPoint* map, const uint32_t start_idx) {
  uint32_t rv = 0;

  map[start_idx].visited = true;

  if (map[start_idx].height == 9) {
    return 1;
  }

  int32_t x = 0;
  int32_t y = 0;
  const Direction* curr_direction;
  TrailPoint* curr_neighbour;
  for (uint32_t i = 0; i < DIRECTIONS_COUNT; ++i) {
    curr_direction = &DIRECTIONS[i];
    x = (start_idx % COLS) + curr_direction->x;
    y = (start_idx / COLS) + curr_direction->y;

    if (x < 0 || x == COLS || y < 0 || y == ROWS) {
      continue;
    }

    curr_neighbour = &map[x + y * COLS];

    if (curr_neighbour->visited == false && curr_neighbour->height - map[start_idx].height == 1) {
      rv += find_trails(map, x + y * COLS);
    }
  }

  return rv;
}

void reset_map(TrailPoint* map) {
  for (uint32_t i = 0; i < ROWS * COLS; ++i) {
    if (map[i].height != EMPTY_SPACE_HEIGHT) {
      map[i].visited = false;
    }
  }
}
