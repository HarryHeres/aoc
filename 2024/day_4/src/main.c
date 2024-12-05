#include <find.h>
#include <main.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

int main(void) {
  FILE* file = fopen("data/input.txt", "r");
  const uint file_size = 19740;
  const uint line_len = 141;  // including newline
  char buffer[file_size] = {'\0'};

  fread(buffer, sizeof(char), file_size, file);
  printf("%s", buffer);

  // Part one
  /* printf("Result: %d", find_xmas(buffer, file_size, line_len)); */

  // Part two
  printf("Result: %d", find_mas(buffer, file_size, line_len));
}

uint find_mas(const char* buffer, const uint buffer_size, const uint line_len) {
  long result = 0;

  for (uint i = line_len; i < buffer_size - line_len; ++i) {
    if (i % line_len < 1 || i % line_len > line_len - 2) {
      continue;
    }

    const char curr_char = buffer[i];
    if (curr_char != 'A') {
      continue;
    }

    // Left diagonal
    if ((buffer[i - line_len - 1] == 'M' && buffer[i + line_len + 1] == 'S') ||
        (buffer[i - line_len - 1] == 'S' && buffer[i + line_len + 1] == 'M')) {

      // Right diagonal
      if ((buffer[i - line_len + 1] == 'M' && buffer[i + line_len - 1] == 'S') ||
          (buffer[i - line_len + 1] == 'S' && buffer[i + line_len - 1] == 'M')) {
        result += 1;
      }
    }
  }

  return result;
}

uint find_xmas(const char* buffer, const uint buffer_size, const uint line_len) {
  long result = 0;
  uint found = 0;

  for (uint i = 0; i < buffer_size; ++i) {
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

    if (i >= (sizeof(XMAS) - 2) * line_len) {
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

    if (i < buffer_size - ((sizeof(XMAS) - 2) * line_len)) {
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
