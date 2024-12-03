#include "main.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char **argv) {
  FILE *input = fopen("input.txt", "r");
  const uint file_size = 20000;
  char buffer[file_size];

  fread(buffer, 1, file_size, input);

  long long rv = 0;
  for (int i = 0; i < file_size; ++i) {
    if (buffer[i] != 'm') {
      continue;
    }

    const uint skip = check_for_match(file_size, buffer, i, &rv);
    if (skip > 0) {
      printf("\nSkipping %d...\n", skip);
      i += skip;
    }
  }

  printf("Result: %lld\n", rv);
}

const uint check_for_match(const uint buffer_size, const char buffer[],
                           const uint start_idx, long long *result) {

  bool first_number = true;
  char first_multiplier[10] = {'\0'};
  char second_multiplier[10] = {'\0'};
  uint multiplier_idx = 0;
  for (int i = 1; i < buffer_size - start_idx; ++i) {
    const char curr_char = buffer[start_idx + i];
    if (first_number) {
      switch (i) {
      case 1: {
        if (curr_char != 'u') {
          return i;
        }
        break;
      }
      case 2: {
        if (curr_char != 'l') {
          return i;
        }
        break;
      }
      case 3: {
        if (curr_char != '(') {
          return i;
        }
        break;
      }
      default: {
        if (curr_char >= '0' && curr_char <= '9') {
          first_multiplier[multiplier_idx++] = curr_char;
        } else if (curr_char == ',') {
          first_number = false;
          multiplier_idx = 0;
        } else {
          return i;
        }
      }
      }
    } else {
      if (curr_char >= '0' && curr_char <= '9') {
        second_multiplier[multiplier_idx++] = curr_char;
      } else if (curr_char == ')') {
        break;
      } else {
        return i;
      }
    }
  }

  const long first = strtol(first_multiplier, NULL, 10);
  const long second = strtol(second_multiplier, NULL, 10);

  printf("Parsed values: %ld * %ld\n", first, second);
  *result += first * second;

  return 0;
}
