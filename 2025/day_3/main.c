#include "src/headers/array_list.h"
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const uint8_t BATTS_TO_FIND = 12;

typedef struct {
  size_t idx;
  uint8_t value;
} Battery;

unsigned long long part_two(ArrayList *lines, size_t number_of_batteries) {
  if (lines == NULL || lines->size == 0) {
    return 0;
  }

  unsigned long long rv = 0;

  const size_t WINDOW_SIZE = number_of_batteries - BATTS_TO_FIND;

  Battery cadidate;
  uint8_t curr_val = 0;
  size_t start = 0;
  char *line;

  for (size_t i = 0; i < lines->size; ++i) {
    line = array_list_get(lines, i);
    start = 0;

    for (size_t j = 0; j < BATTS_TO_FIND; ++j) {
      cadidate.value = 0;
      cadidate.idx = 0;

      for (size_t k = start; k <= WINDOW_SIZE + j; ++k) {
        curr_val = line[k] - '0';

        if (curr_val > cadidate.value) {
          cadidate.value = curr_val;
          cadidate.idx = k;
        }
      }

      printf("%d", cadidate.value);
      rv += cadidate.value * pow(10, BATTS_TO_FIND - j - 1);
      start = cadidate.idx + 1;
    }
    printf("\n");
  }

  return rv;
}

size_t part_one(ArrayList *lines) {
  if (lines == NULL || lines->size == 0) {
    return 0;
  }

  size_t rv = 0;
  char *line = NULL;
  uint8_t char_idx = 0, curr = 0, first_max = 0, second_max = 0;

  for (size_t i = 0; i < lines->size; ++i) {
    line = (char *)array_list_get(lines, i);

    char_idx = 1;
    curr = line[char_idx] - '0';
    first_max = line[0] - '0';
    second_max = line[1] - '0';

    while (line[char_idx] != '\n') {
      if (curr > first_max && line[char_idx + 1] != '\n') {
        first_max = curr;
        second_max = line[char_idx + 1] - '0';
      } else if (curr > second_max) {
        second_max = curr;
      }

      curr = line[++char_idx] - '0';
    }

    printf("Found max in line %ld: %d\n", i, first_max * 10 + second_max);
    rv += first_max * 10 + second_max;
  }

  return rv;
}

ArrayList *parse_input(FILE *input, size_t *no_batteries) {
  if (input == NULL) {
    return NULL;
  }

  fseek(input, 0, SEEK_END);
  const int file_size = ftell(input);
  fseek(input, 0, 0);

  char *line = NULL;
  size_t allocated = 0;
  ssize_t read = getline(&line, &allocated, input);
  *no_batteries = read - 1;

  ArrayList *rv = array_list_create(file_size / read);

  while (read > 0) {
    printf("%s", line);

    array_list_add(rv, line);
    line = NULL;
    read = getline(&line, &allocated, input);
  }

  return rv;
}

int main() {
  FILE *input = fopen("data/test.txt", "r");
  // FILE *input = fopen("data/input.txt", "r");

  if (input == NULL) {
    return EXIT_FAILURE;
  }

  size_t no_batteries;
  ArrayList *lines = parse_input(input, &no_batteries);
  if (lines == NULL) {
    return EXIT_FAILURE;
  }

  printf("Part one: %ld\n\n", part_one(lines));
  printf("Part two: %lld\n", part_two(lines, no_batteries));

  array_list_free(lines);
  return EXIT_SUCCESS;
}
