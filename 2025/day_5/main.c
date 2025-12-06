#include "src/headers/array_list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  unsigned long long start;
  unsigned long long end;
} Range;

unsigned long long part_two(ArrayList *ranges) {
  if (ranges == NULL || ranges->size < 1) {
    return 0;
  }

  unsigned long long rv = 0;
  Range *curr;
  for (size_t i = 0; i < ranges->size; ++i) {
    curr = array_list_get(ranges, i);
    rv += curr->end - curr->start + 1;
  }

  return rv;
}

uint32_t part_one(ArrayList *ranges, FILE *input) {
  if (ranges == NULL || ranges->size < 1 || input == NULL) {
    return 0;
  }

  uint32_t rv = 0;

  char *line = NULL;
  size_t allocated = 0;
  ssize_t read = getline(&line, &allocated, input);

  Range *range;
  unsigned long long curr = 0;
  while (read > 0) {
    curr = strtoull(line, NULL, 10);

    for (size_t i = 0; i < ranges->size; ++i) {
      range = array_list_get(ranges, i);

      if (curr == range->start) {
        ++rv;
        break;
      } else if (curr == range->end) {
        ++rv;
        break;
      } else if (curr >= range->start && curr <= range->end) {
        ++rv;
        break;
      }
    }

    line = NULL;
    read = getline(&line, &allocated, input);
  }

  return rv;
}

size_t merge_ranges(ArrayList *ranges) {
  Range *curr, *start_overlapping, *end_overlapping;

  for (int i = 0; i < ranges->size; ++i) {
    curr = array_list_get(ranges, i);

    for (size_t j = 0; j < ranges->size; ++j) {
      start_overlapping = array_list_get(ranges, j);
      if (start_overlapping != curr &&
          curr->start >= start_overlapping->start &&
          curr->start <= start_overlapping->end) {
        start_overlapping->end = start_overlapping->end > curr->end
                                     ? start_overlapping->end
                                     : curr->end;
        array_list_delete(ranges, curr);
        return 1;
      }
    }
  }

  return 0;
}

ArrayList *parse_ranges(FILE *input) {
  if (input == NULL) {
    return NULL;
  }

  ArrayList *rv = array_list_create(20);

  char *line = NULL;
  size_t allocated = 0;
  Range *curr;
  Range *existing;
  unsigned long long curr_end = 0, existing_end = 0;
  getline(&line, &allocated, input);

  while (line[0] != '\n') {
    curr = (Range *)malloc(sizeof(Range));

    curr->start = strtoull(strtok(line, "-"), NULL, 10);
    curr->end = strtoull(strtok(NULL, "-"), NULL, 10);

    array_list_add(rv, curr);

    line = NULL;
    getline(&line, &allocated, input);
  }

  while (merge_ranges(rv) > 0)
    ;

  return rv;
}

int main() {
  // FILE *input = fopen("data/test.txt", "r");
  FILE *input = fopen("data/input.txt", "r");
  if (input == NULL) {
    return EXIT_FAILURE;
  }

  ArrayList *ranges = parse_ranges(input);
  if (ranges == NULL || ranges->size < 1) {
    return EXIT_FAILURE;
  }

  Range *curr;
  for (size_t i = 0; i < ranges->size; ++i) {
    curr = array_list_get(ranges, i);
    printf("Range starting at %llu and ending at %llu\n", curr->start,
           curr->end);
  }

  printf("Part one: %d\n", part_one(ranges, input));
  printf("Part two: %llu\n", part_two(ranges));

  fclose(input);
  array_list_free(ranges);
  return EXIT_SUCCESS;
}
