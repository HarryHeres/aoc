#include <array_list.h>
#include <main.h>
#include <sequence.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int main(void) {
  FILE* file = fopen("data/input.txt", "r");
  const uint16_t line_len = 100;

  char line[line_len];
  memset(line, 0, sizeof(line));

  char line_copy[line_len];
  memset(line, 0, sizeof(line_copy));

  uint64_t result = 0;

  char* tmp_buffer;
  uint64_t calibration_value;
  Sequence* equation = sequence_init(100, 0);
  while (fgets(line, sizeof(line), file) != NULL) {
    memcpy(line_copy, line, sizeof(line_copy));

    calibration_value = strtol(strtok(line_copy, ":"), NULL, 10);
    if (calibration_value == 0L) {
      printf("Skipping...\n");
      continue;
    }

    sequence_clear(equation, calibration_value);
    while ((tmp_buffer = strtok(NULL, " ")) != NULL) {
      sequence_add_value(equation, strtol(tmp_buffer, NULL, 10));
    }

    if (sequence_is_valid(equation)) {
      printf("Sequence %ld is valid\n", calibration_value);
      result += calibration_value;
    }
  }

  free(equation);

  printf("Result: %ld\n", result);
}
