#include <direction.h>
#include <main.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int main(void) {
  FILE* file = fopen("data/input_test.txt", "r");
  const uint16_t rows = 10;
  const uint16_t columns = 10;
  const uint32_t map_size = rows * columns;

  char map[map_size];
  char line_buffer[columns + 2];  // newline + terminating character

  memset(map, '\0', sizeof(map));
  memset(line_buffer, '\0', sizeof(line_buffer));

  int32_t start_x = -1;
  int32_t start_y = -1;
  uint16_t row_idx = 0;
  while (fgets(line_buffer, sizeof(line_buffer), file) != NULL) {
    memcpy(&map[row_idx * columns], line_buffer, columns);

    if (start_x < 0) {
      for (uint16_t i = 0; i < rows; ++i) {
        if (line_buffer[i] == '^') {
          printf("Found starting point at [%d, %d]\n", row_idx, i);
          start_x = i;
          start_y = row_idx;
        }
      }
    }

    ++row_idx;
  }

  if (start_x < 0 || start_y < 1) {
    printf("Unable to find the starting point. Exiting...]\n");
    fclose(file);
    return EXIT_FAILURE;
  }

  // Part one
  /* const uint32_t result = traverse_map(map, rows, columns, start_x, start_y); */
  /* printf("Result: %d\n", result); */

  // Part two
  const uint32_t result = find_obstruction_places(map, rows, columns, start_x, start_y);
  printf("Result: %d\n", result);

  fclose(file);
  return EXIT_SUCCESS;
}

uint32_t find_obstruction_places(char* map, const uint32_t rows, const uint32_t columns, const uint32_t start_x,
                                 const uint32_t start_y) {
  uint32_t result = 0;
  for (uint32_t i = 0; i < rows * columns; ++i) {
    if (map[i] == '.') {
      printf("Testing %d\n", i);
      map[i] = '#';

      if (contains_cycle(map, rows, columns, start_x, start_y) == true) {
        ++result;
        printf("Cycle found on %d\n", i);
      }

      map[i] = '.';
    }
  }

  return result;
}

bool contains_cycle(char* map, const uint32_t rows, const uint32_t columns, const uint32_t start_x,
                    const uint32_t start_y) {
  bool rv = false;
  uint16_t direction = 0;

  uint32_t curr_x = start_x;
  uint32_t curr_y = start_y;

  char* curr_char = NULL;
  char next_char;
  char map_copy[rows * columns];
  memcpy(map_copy, map, rows * columns);

  while (true) {
    if (curr_x == 0 || curr_x == rows || curr_y == 0 || curr_y == columns) {
      break;
    }

    curr_char = &map_copy[curr_x + (curr_y * columns)];
    next_char = map_copy[(curr_x + DIRECTIONS[direction].x) + ((curr_y + DIRECTIONS[direction].y) * columns)];
    if (next_char == '#') {
      direction = (direction + 1) % (sizeof(DIRECTIONS) / sizeof(Direction));
      next_char = map_copy[(curr_x + DIRECTIONS[direction].x) + ((curr_y + DIRECTIONS[direction].y) * columns)];
    }

    if (*curr_char == 'X' && next_char == 'X') {
      rv = true;
      break;
    }

    if (*curr_char != 'X') {
      *curr_char = 'X';
    }

    curr_x += DIRECTIONS[direction].x;
    curr_y += DIRECTIONS[direction].y;
  }

  if (rv == true) {
    for (uint32_t i = 0; i < rows * columns; ++i) {
      if (i > 0 && i % columns == 0) {
        printf("\n");
      }
      printf("%c", map_copy[i]);
    }
    printf("\n");
    printf("\n");
  }

  return rv;
}

uint32_t traverse_map(char* map, const uint32_t rows, const uint32_t columns, const uint32_t start_x,
                      const uint32_t start_y) {
  uint32_t result = 0;
  uint16_t direction = 0;

  uint32_t curr_x = start_x;
  uint32_t curr_y = start_y;

  char* curr_char = NULL;
  char next_char;
  while (true) {
    curr_char = &map[curr_x + (curr_y * columns)];
    if (curr_x == 0 || curr_x == rows || curr_y == 0 || curr_y == columns) {
      break;
    }

    next_char = map[(curr_x + DIRECTIONS[direction].x) + ((curr_y + DIRECTIONS[direction].y) * columns)];
    if (next_char == '#') {
      direction = (direction + 1) % (sizeof(DIRECTIONS) / sizeof(Direction));
    }

    if (*curr_char != 'X') {
      *curr_char = 'X';
      ++result;
    }

    curr_x += DIRECTIONS[direction].x;
    curr_y += DIRECTIONS[direction].y;
  }

  for (uint32_t i = 0; i < rows * columns; ++i) {
    if (i > 0 && i % columns == 0) {
      printf("\n");
    }
    printf("%c", map[i]);
  }
  printf("\n");

  return result;
}
