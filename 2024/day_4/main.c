#include "main.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

const char XMAS[] = "XMAS";
const char SAMX[] = "SAMX";

int main() {
  FILE* file = fopen("input_test.txt", "r");
  const uint file_size = 20000;
  char buffer[file_size];

  fread(buffer, 1, file_size, file);
  printf("Result: %d", find_xmas(buffer, file_size, 10));
}

const uint find_xmas(const char* buffer, const uint buffer_size, const uint line_len) {
  uint result = 0;

  for (uint i = 0; i < buffer_size; ++i) {
    const char curr_char = buffer[i];
    if (curr_char != 'X') {
      continue;
    }

    if (i < buffer_size - sizeof(XMAS) - 1) {
      result += find_ahead(buffer, i);
    }
    if (i > sizeof(XMAS)) {
      result += find_reverse(buffer, i);
    }

    if (i > 4 * line_len) {
      result += find_above(buffer, i, line_len);
    }

    if (i < buffer_size - 4 * line_len) {
      result += find_below(buffer, i, line_len);
    }
  }

  return result;
}

const uint find_ahead(const char* buffer, const uint start_idx) {
  return memcmp(&buffer[start_idx], XMAS, sizeof(XMAS) - 1) == 0 ? 1 : 0;
}

const uint find_reverse(const char* buffer, const uint start_idx) {
  return memcmp(&buffer[start_idx - sizeof(SAMX) + 2], SAMX, sizeof(SAMX) - 1) == 0 ? 1 : 0;
}

const uint find_above(const char* buffer, const uint start_idx, const uint line_len) {
  char tmp[sizeof(XMAS)] = {'\0'};
  for (uint i = 0; i < sizeof(XMAS) - 1; ++i) {
    tmp[i] = buffer[start_idx - i * line_len];
  }
  return memcmp(&tmp, XMAS, sizeof(XMAS) - 1) == 0 ? 1 : 0;
}

const uint find_below(const char* buffer, const uint start_idx, const uint line_len) {
  char tmp[sizeof(XMAS)] = {'\0'};
  for (uint i = 0; i < sizeof(XMAS) - 1; ++i) {
    tmp[i] = buffer[start_idx + i * line_len];
  }
  return memcmp(&tmp, XMAS, sizeof(XMAS) - 1) == 0 ? 1 : 0;
}
