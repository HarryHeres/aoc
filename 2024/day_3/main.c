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
  bool active = true;
  for (int i = 0; i < file_size; ++i) {

    if (buffer[i] == 'o' && buffer[i - 1] == 'd') {
      const uint skip = check_for_match_do(file_size, buffer, i, &active);
      if (skip > 0) {
        printf("\nSkipping do %d...\n", skip);
        i += skip;
      }
    } else if (buffer[i] == 'm' && active) {
      const uint skip = check_for_match_mul(file_size, buffer, i, &rv);
      if (skip > 0) {
        printf("\nSkipping mul %d...\n", skip);
        i += skip;
      }
    } else {
      continue;
    }
  }

  printf("Result: %lld\n", rv);
}

const uint check_for_match_do(const uint buffer_size, const char buffer[],
                              const uint start_idx, bool *active) {
  const char case_dont[] = {'n', '\'', 't', '(', ')'};

  // Checking do
  if (buffer[start_idx + 1] == '(' && buffer[start_idx + 2] == ')') {
    *active = true;
    return 0;
  }

  // Checking don't
  for (int i = 0; i < sizeof(case_dont); ++i) {
    if (buffer[start_idx + i + 1] != case_dont[i]) {
      return i;
    }
  }

  *active = false;
  return 0;
}

// Part one
const uint check_for_match_mul(const uint buffer_size, const char buffer[],
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
