#include <main.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

const uint32_t ROWS = 0;
const uint32_t COLS = 0;

const uint32_t LINE_LEN = 5;

int main(void) {
  FILE* file = fopen("data/input_test.txt", "r");

  char line[LINE_LEN + 2];
  memset(line, '\0', sizeof(line));

  fgets(line, sizeof(line), file);

  uint64_t result_len = 0;
  for (uint32_t i = 0; i < LINE_LEN; ++i) {
    result_len += line[i] - '0';
  }

  char result[result_len];
  memset(result, '.', sizeof(result));
  uint32_t result_idx = 0;

  uint32_t line_idx = 0;
  uint32_t count = 0;

  char write_buffer[result_len];
  memset(write_buffer, '\0', sizeof(write_buffer));

  char curr_id[(uint32_t)ceil(LINE_LEN / 2.0)];
  uint32_t write_buffer_curr_idx = sizeof(write_buffer) - 1;
  uint32_t to_write_count = 0;
  uint32_t free_space_size = 0;
  bool is_free_space = false;

  for (uint64_t i = 0; i < LINE_LEN; ++i) {
    count = line[line_idx] - '0';

    if (is_free_space == false) {
      sprintf(curr_id, "%d", line_idx);
      to_write_count = count * strlen(curr_id);
    } else {
      sprintf(curr_id, "%d", line_idx / 2);
      free_space_size = line[LINE_LEN - line_idx] - '0';
      to_write_count = free_space_size;
    }

    write_buffer_curr_idx -= count * strlen(curr_id);
    append_to_string(&write_buffer[write_buffer_curr_idx], curr_id, strlen(curr_id), count);

    for (uint32_t _ = 0; _ < to_write_count; ++_) {
      result[result_idx] = write_buffer[write_buffer_curr_idx];
      ++write_buffer_curr_idx;
      ++result_idx;
    }

    line_idx = LINE_LEN - 1 - line_idx + (is_free_space ? 1 : 0);
    is_free_space = line_idx % 2 == 0;
    memset(curr_id, '\0', sizeof(curr_id));
  }

  print_result_disk(result);
}

void append_to_string(char* string, char* to_append, const uint32_t len, const uint32_t count) {
  for (uint32_t i = 0; i < count; ++i) {
    for (uint32_t j = 0; j < len; ++j) {
      string[i * len + j] = to_append[j];
    }
  }
}

void print_result_disk(const char* disk) {
  uint32_t idx = 0;
  printf("Result: ");
  while (disk[idx] != '\0') {
    printf("%c", disk[idx]);
    ++idx;
  }
  printf("\n");
}
