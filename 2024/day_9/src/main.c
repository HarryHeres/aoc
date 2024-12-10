#include <array_list.h>
#include <main.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

const uint32_t ROWS = 0;
const uint32_t COLS = 0;

const uint32_t LINE_LEN = 19999;

int main(void) {
  FILE* file = fopen("data/input.txt", "r");

  char line[LINE_LEN + 1];
  memset(line, '\0', sizeof(line));

  fgets(line, sizeof(line), file);

  ArrayList* result[LINE_LEN];
  memset(result, 0, sizeof(result));

  uint32_t id = 0;
  uint32_t curr_id_count = 0;
  for (uint32_t i = 0; i < sizeof(result) / sizeof(ArrayList*); ++i) {
    curr_id_count = line[i] - '0';
    result[i] = array_list_init(curr_id_count);

    if (i % 2 == 0) {
      for (uint32_t j = 0; j < curr_id_count; ++j) {
        array_list_add(result[i], i / 2);
      }
    }

    for (uint32_t j = 0; j < result[i]->capacity; ++j) {
      id = array_list_get(result[i], j);
      if (i > 0 && id < 1) {
        printf("%c", '.');
      } else {
        printf("%d", id);
      }
    }
  }
  printf("\n");

  curr_id_count = 0;
  uint32_t curr_id = 0;
  for (int32_t i = LINE_LEN - 1; i >= 0; i -= 2) {
    curr_id = i / 2;
    curr_id_count = line[i] - '0';

    int32_t free_idx = find_free_space(result, curr_id_count, i);
    if (free_idx < 1) {
      continue;
    }

    for (uint32_t j = 0; j < curr_id_count; ++j) {
      array_list_add(result[free_idx], curr_id);
    }

    array_list_clear(result[i]);
  }

  uint64_t checksum = 0;
  uint32_t position = 0;
  for (uint32_t i = 0; i < LINE_LEN - 1; ++i) {
    for (uint32_t j = 0; j < result[i]->capacity; ++j) {
      id = array_list_get(result[i], j);
      if (i > 0 && id < 1) {
        printf("%c", '.');
      } else {
        printf("%d", id);
        checksum += id * position;
      }
      ++position;
    }
  }
  printf("\n");
  printf("Checksum: %ld\n", checksum);
}

int32_t find_free_space(ArrayList** result, const uint32_t block_size, const uint32_t stop_index) {
  for (uint32_t i = 1; i < stop_index; i += 2) {
    if (result[i]->capacity - result[i]->count >= block_size) {
      return i;
    }
  }

  return -1;
}

// Part one
/* int main(void) { */
/*   FILE* file = fopen("data/input.txt", "r"); */

/*   char line[LINE_LEN + 2]; */
/*   memset(line, '\0', sizeof(line)); */

/*   fgets(line, sizeof(line), file); */

/*   uint64_t number_count = 0; */
/*   for (uint32_t i = 0; i < LINE_LEN; i += 2) { */
/*     number_count += line[i] - '0'; */
/*   } */

/*   ArrayList* result = array_list_init(number_count); */

/*   bool is_free_space = false; */
/*   uint32_t line_left_idx = 0; */
/*   uint32_t line_right_idx = LINE_LEN - 1; */
/*   uint32_t count_to_write = 0; */
/*   uint32_t curr_count = 0; */
/*   uint32_t curr_id = 0; */

/*   uint32_t write_buffer[number_count]; */
/*   memset(write_buffer, '\0', sizeof(write_buffer)); */

/*   uint32_t write_help_buffer[number_count]; */
/*   memset(write_buffer, '\0', sizeof(write_help_buffer)); */

/*   uint32_t write_buffer_idx = number_count - 1; */
/*   uint32_t write_help_buffer_idx = 0; */
/*   while (true) { */
/*     if (result->count == result->capacity) { */
/*       break; */
/*     } */

/*     count_to_write = line[line_left_idx] - '0'; */

/*     if (is_free_space == false) { */
/*       curr_id = line_left_idx / 2; */
/*       for (uint32_t _ = 0; _ < count_to_write; ++_) { */
/*         write_buffer[write_buffer_idx] = curr_id; */
/*         --write_buffer_idx; */
/*       } */
/*     } else if (number_count - 1 - write_buffer_idx < count_to_write) { */
/*       int32_t count_to_write_copy = count_to_write; */
/*       while (count_to_write_copy > 0) { */
/*         curr_count = line[line_right_idx] - '0'; */
/*         curr_id = line_right_idx / 2; */
/*         for (uint32_t _ = 0; _ < curr_count; ++_) { */
/*           write_help_buffer[write_help_buffer_idx] = curr_id; */
/*           ++write_help_buffer_idx; */
/*         } */

/*         line_right_idx -= 2; */
/*         count_to_write_copy -= curr_count; */
/*       } */

/*       for (uint32_t i = 0; i < write_help_buffer_idx; ++i) { */
/*         write_buffer[write_buffer_idx] = write_help_buffer[write_help_buffer_idx - i - 1]; */
/*         --write_buffer_idx; */
/*       } */
/*       write_help_buffer_idx = 0; */
/*     } */

/*     write_block(result, write_buffer, &write_buffer_idx, count_to_write); */
/*     is_free_space = !is_free_space; */
/*     ++line_left_idx; */
/*   } */
/*   print_result_disk(result); */

/*   uint64_t checksum = 0; */
/*   for (uint32_t i = 0; i < result->count; ++i) { */
/*     checksum += array_list_get(result, i) * i; */
/*   } */

/*   printf("Checksum: %ld\n", checksum); */
/* } */

/* void write_block(ArrayList* result, const uint32_t* write_buffer, uint32_t* write_buffer_idx, const uint32_t count) { */
/*   for (uint32_t _ = 0; _ < count; ++_) { */
/*     array_list_add(result, write_buffer[(*write_buffer_idx) + 1]); */
/*     ++(*write_buffer_idx); */
/*   } */
/* } */

/* void append_to_string(char* string, char* to_append, const uint32_t len, const uint32_t count) { */
/*   for (uint32_t i = 0; i < count; ++i) { */
/*     for (uint32_t j = 0; j < len; ++j) { */
/*       string[i * len + j] = to_append[j]; */
/*     } */
/*   } */
/* } */

/* void print_result_disk(const ArrayList* disk) { */
/*   printf("Result: "); */
/*   for (uint32_t i = 0; i < disk->count; ++i) { */
/*     printf("%d,", array_list_get(disk, i)); */
/*   } */
/*   printf("\n"); */
/* } */
