#include "main.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

const char XMAS[] = "XMAS";
const char SAMX[] = "SAMX";

int main() {
  FILE* file = fopen("input.txt", "r");
  const uint file_size = 19740;
  const uint line_len = 141;  // including newline
  char buffer[file_size] = {'\0'};

  fread(buffer, sizeof(char), file_size, file);
  printf("Result: %d", find_xmas(buffer, file_size, line_len));
}

const uint find_xmas(const char* buffer, const uint buffer_size, const uint line_len) {
  long result = 0;
  uint found = 0;

  for (int i = 0; i < buffer_size; ++i) {
    const char curr_char = buffer[i];
    if (curr_char != 'X') {
      continue;
    }

    if (i < buffer_size - sizeof(XMAS) + 1) {
      found = find_ahead(buffer, i);
      if (found == 1) {
        printf("Found ahead at index %d\n", i);
      }
      result += found;
    }

    if (i >= sizeof(XMAS) - 2) {
      found = find_reverse(buffer, i);
      if (found == 1) {
        printf("Found reversed at index %d\n", i);
      }
      result += found;
    }

    if (i >= 3 * line_len) {
      found = find_above(buffer, i, line_len);
      if (found == 1) {
        printf("Found above at index %d\n", i);
      }
      result += found;

      if (i % line_len >= sizeof(XMAS) - 2) {
        found = find_above_left(buffer, i, line_len);
        if (found == 1) {
          printf("Found above-left at index %d\n", i);
        }
        result += found;
      }

      if (i % line_len < line_len - sizeof(XMAS) + 2) {
        found = find_above_right(buffer, i, line_len);
        if (found == 1) {
          printf("Found above-right at index %d\n", i);
        }
        result += found;
      }
    }

    if (i < buffer_size - 3 * line_len) {
      found = find_below(buffer, i, line_len);
      if (found == 1) {
        printf("Found below at index %d\n", i);
      }
      result += found;

      if (i % line_len >= sizeof(XMAS) - 2) {
        found = find_below_left(buffer, i, line_len);
        if (found == 1) {
          printf("Found below-left at index %d\n", i);
        }
        result += found;
      }

      if (i % line_len < line_len - sizeof(XMAS) + 2) {
        found = find_below_right(buffer, i, line_len);
        if (found == 1) {
          printf("Found below-right at index %d\n", i);
        }
        result += found;
      }
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

  for (uint i = 0; i < sizeof(tmp) - 1; ++i) {
    tmp[i] = buffer[start_idx - (i * line_len)];
  }

  return memcmp(&tmp, XMAS, sizeof(tmp)) == 0 ? 1 : 0;
}

const uint find_above_left(const char* buffer, const uint start_idx, const uint line_len) {
  char tmp[sizeof(XMAS)] = {'\0'};

  for (uint i = 0; i < sizeof(tmp) - 1; ++i) {
    tmp[i] = buffer[start_idx - (i * line_len) - i];
  }

  return memcmp(&tmp, XMAS, sizeof(tmp)) == 0 ? 1 : 0;
}

const uint find_above_right(const char* buffer, const uint start_idx, const uint line_len) {
  char tmp[sizeof(XMAS)] = {'\0'};

  for (uint i = 0; i < sizeof(tmp) - 1; ++i) {
    tmp[i] = buffer[start_idx - (i * line_len) + i];
  }

  return memcmp(&tmp, XMAS, sizeof(tmp)) == 0 ? 1 : 0;
}

const uint find_below(const char* buffer, const uint start_idx, const uint line_len) {
  char tmp[sizeof(XMAS)] = {'\0'};
  for (uint i = 0; i < sizeof(tmp) - 1; ++i) {
    tmp[i] = buffer[start_idx + (i * line_len)];
  }

  return memcmp(&tmp, XMAS, sizeof(tmp)) == 0 ? 1 : 0;
}

const uint find_below_left(const char* buffer, const uint start_idx, const uint line_len) {
  char tmp[sizeof(XMAS)] = {'\0'};
  for (uint i = 0; i < sizeof(tmp) - 1; ++i) {
    tmp[i] = buffer[start_idx + (i * line_len) - i];
  }

  return memcmp(&tmp, XMAS, sizeof(tmp)) == 0 ? 1 : 0;
}

const uint find_below_right(const char* buffer, const uint start_idx, const uint line_len) {
  char tmp[sizeof(XMAS)] = {'\0'};
  for (uint i = 0; i < sizeof(tmp) - 1; ++i) {
    tmp[i] = buffer[start_idx + (i * line_len) + i];
  }

  return memcmp(&tmp, XMAS, sizeof(tmp)) == 0 ? 1 : 0;
}
