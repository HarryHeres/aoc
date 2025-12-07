#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char **lines;
  size_t line_len;
  size_t line_count;
} Diagram;

uint64_t part_one(Diagram *diag) {
  if (diag == NULL || diag->lines == NULL) {
    return 0;
  }

  uint64_t rv = 0;
  for (size_t i = 0; i < diag->line_len; ++i) {
    if (diag->lines[0][i] == 'S') {
      diag->lines[1][i] = '|';
      break;
    }
  }

  for (size_t row = 1; row < diag->line_count - 1; ++row) {
    for (size_t col = 0; col < diag->line_len; ++col) {
      if (diag->lines[row][col] == '|') {
        if (diag->lines[row + 1][col] == '^') {
          diag->lines[row + 1][col - 1] = '|';
          diag->lines[row + 1][col + 1] = '|';
          ++rv;
        } else {
          diag->lines[row + 1][col] = '|';
        }
      }
    }
    printf("%s", diag->lines[row]);
  }
  printf("%s", diag->lines[diag->line_count - 1]);
  return rv;
}

Diagram *parse_input(FILE *input) {
  if (input == NULL) {
    return NULL;
  }

  Diagram *rv = malloc(sizeof(Diagram));
  if (rv == NULL) {
    return rv;
  }

  fseek(input, 0, SEEK_END);
  const long file_len = ftell(input);
  fseek(input, 0, 0);

  char *line = NULL;
  size_t allocated = 0;
  ssize_t read = getline(&line, &allocated, input);

  rv->line_len = strlen(line);
  rv->line_count = file_len / rv->line_len;

  rv->lines = (char **)malloc(rv->line_count * sizeof(char *));
  rv->lines[0] = line;

  for (int i = 1; i < rv->line_count; ++i) {
    line = NULL;
    getline(&line, &allocated, input);
    rv->lines[i] = line;
  }

  return rv;
}

int main() {
  // FILE *input = fopen("data/test.txt", "r");
  FILE *input = fopen("data/input.txt", "r");
  if (input == NULL) {
    return EXIT_FAILURE;
  }

  Diagram *diag = parse_input(input);
  printf("Part one: %llu\n", part_one(diag));

  for (int i = 0; i < diag->line_count; ++i) {
    free(diag->lines[i]);
  }
  free(diag->lines);
  free(diag);

  fclose(input);
  return EXIT_SUCCESS;
}
