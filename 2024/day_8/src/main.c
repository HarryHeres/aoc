#include <array_list.h>
#include <main.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

const uint32_t ROWS = 12;
const uint32_t COLS = 12;

int main(void) {
  FILE* file = fopen("data/input_test.txt", "r");

  char map[ROWS * COLS];
  char line[COLS + 2];  // newline + terminator

  uint32_t idx = 0;
  while (fgets(line, sizeof(line), file)) {
    memcpy(&map[idx * COLS], line, COLS);
    ++idx;
  }

  const uint32_t result = find_antinodes(map);
  printf("Result: %d", result);
}

uint32_t find_antinodes(char* map) {
  ArrayList* antinodes = array_list_init(ROWS * COLS);

  char curr_char = '\0';
  for (uint32_t i = 0; i < ROWS * COLS; ++i) {
    curr_char = map[i];
    if (curr_char != '.') {
      check_for_antennas(map, curr_char, i % COLS, i / ROWS, antinodes);
    }
  }

  for (uint32_t i = 0; i < antinodes->count; ++i) {
    map[array_list_get(antinodes, i)] = '#';
  }

  print_map(map, ROWS, COLS);

  return antinodes->count;
}

void check_for_antennas(const char* map, const char frequency, const uint32_t antenna_x, const uint32_t antenna_y,
                        ArrayList* antinodes) {

  for (uint32_t j = antenna_y; j < ROWS; ++j) {
    for (uint32_t i = 0; i < COLS; ++i) {
      if (i == antenna_x && j == antenna_y) {
        continue;
      }
      if (map[i + j * COLS] == frequency) {
        const int32_t diff_x = abs((int32_t)antenna_x - (int32_t)i);
        const int32_t diff_y = abs((int32_t)antenna_y - (int32_t)j);

        uint32_t antinode_x = i - diff_x;
        uint32_t antinode_y = j - diff_y;

        if (antinode_x < COLS && antinode_y < ROWS) {
          if (!array_list_contains(antinodes, antinode_x + antinode_y * COLS)) {
            array_list_add(antinodes, antinode_x + antinode_y * COLS);
          }
        }

        antinode_x = antenna_x + diff_x;
        antinode_y = antenna_y + diff_y;

        if (antinode_x < COLS && antinode_y < ROWS) {
          if (!array_list_contains(antinodes, antinode_x + antinode_y * COLS)) {
            array_list_add(antinodes, antinode_x + antinode_y * COLS);
          }
        }
      }
    }
  }
}

void print_map(char* map, const uint32_t ROWS, const uint32_t COLS) {
  for (uint32_t i = 0; i < ROWS * COLS; ++i) {
    if (i > 0 && i % COLS == 0) {
      printf("\n");
    }
    printf("%c", map[i]);
  }
  printf("\n");
}
