#include "src/headers/array_list.h"
#include <_stdio.h>
#include <_string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  long start;
  long end;
} Range;

long part_one(const ArrayList *ranges) {
  long rv = 0;

  Range *curr_range;
  char curr[100] = {0};
  char first_half[50], second_half[50];
  long curr_len;

  for (int i = 0; i < ranges->size; ++i) {
    curr_range = array_list_get(ranges, i);

    printf("Current range: %ld -> %ld\n", curr_range->start, curr_range->end);

    for (long j = curr_range->start; j <= curr_range->end; ++j) {
      sprintf(curr, "%ld", j);
      curr_len = strlen(curr);

      if (curr_len % 2 == 0) {
        memset(first_half, 0, sizeof(first_half));
        memset(second_half, 0, sizeof(second_half));

        strncpy(first_half, curr, curr_len / 2);
        strncpy(second_half, &(curr[curr_len / 2]), curr_len / 2);

        if (strcmp(first_half, second_half) == 0) {
          printf("  Invalid ID: %s\n", curr);
          rv += strtol(curr, NULL, 10);
        }
      }
    }
  }

  return rv;
}

long part_two(const ArrayList *ranges) {
  long rv = 0;

  Range *curr_range;
  char curr[100] = {0}, first_chunk[50] = {0}, curr_chunk[50] = {0};
  long curr_len;
  bool repeating = true;

  for (int i = 0; i < ranges->size; ++i) {
    curr_range = array_list_get(ranges, i);

    printf("Current range: %ld -> %ld\n", curr_range->start, curr_range->end);

    for (long j = curr_range->start; j <= curr_range->end; ++j) {
      memset(curr, 0, sizeof(curr));
      sprintf(curr, "%ld", j);
      curr_len = strlen(curr);

      for (int chunk_size = curr_len / 2; chunk_size > 0; --chunk_size) {
        if (curr_len % chunk_size != 0) {
          continue;
        }

        repeating = true;
        memset(first_chunk, 0, sizeof(first_chunk));
        strncpy(first_chunk, curr, chunk_size);

        // printf("        Chunk size: %d\n", chunk_size);
        for (int k = 1; k < (curr_len / chunk_size); ++k) {
          memset(curr_chunk, 0, sizeof(curr_chunk));
          strncpy(curr_chunk, curr + k * chunk_size, chunk_size);

          // printf("        Comparing: %s to %s\n", first_chunk, curr_chunk);
          if (strcmp(first_chunk, curr_chunk) != 0) {
            repeating = false;
            break;
          }
        }

        if (repeating) {
          printf("  Invalid ID: %s\n", curr);
          rv += strtol(curr, NULL, 10);
          break;
        }
      }
    }
  }

  return rv;
}

ArrayList *parse_input(FILE *input_file) {
  if (input_file == NULL) {
    return NULL;
  }

  fseek(input_file, 0, SEEK_END);

  const long line_len = ftell(input_file);
  char *line = (char *)malloc(line_len * sizeof(char));

  fseek(input_file, 0, 0);
  fgets(line, line_len, input_file);

  ArrayList *rv = array_list_create(16);

  char *curr_save_ptr, *range_save_ptr,
      *curr = strtok_r(line, ",", &curr_save_ptr);
  Range *range;
  while (curr != NULL) {
    range = (Range *)malloc(sizeof(Range));
    range->start = strtol(strtok_r(curr, "-", &range_save_ptr), NULL, 10);
    range->end = strtol(strtok_r(NULL, "-", &range_save_ptr), NULL, 10);
    array_list_add(rv, range);

    curr = strtok_r(NULL, ",", &curr_save_ptr);
  }

  return rv;
}

int main() {
  // FILE *input_file = fopen("data/test.txt", "r");
  FILE *input_file = fopen("data/input.txt", "r");

  ArrayList *ranges = parse_input(input_file);

  // printf("Part 1: %ld\n\n", part_one(ranges));
  printf("Part 2: %ld\n", part_two(ranges));

  array_list_free(ranges);
  return 0;
}
