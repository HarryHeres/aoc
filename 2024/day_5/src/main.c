#include <main.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array_list.h"
#include "map.h"

int main(void) {
  FILE* file = fopen("data/input.txt", "r");
  const uint16_t line_len = 100;  // including newline
  char line_buffer[line_len] = {'\0'};

  const Map* rules = map_create(100);
  if (rules == NULL) {
    printf("Unable to allocate memory for rules map");
    return EXIT_FAILURE;
  }

  while (fgets(line_buffer, line_len, file)) {
    if (memcmp(line_buffer, "\n", 1) == 0) {
      break;
    }

    // Parse rules
    const uint16_t* parsed = parse_rule(line_buffer);
    if (parsed == NULL) {
      printf("Invalid rule format: %s", line_buffer);
      return EXIT_FAILURE;
    }

    printf("Parsed %d, %d\n", parsed[0], parsed[1]);

    map_put(rules, parsed[0], parsed[1]);

    free(parsed);
  }

  uint32_t result = 0;
  uint16_t sequence_number = 1;
  while (fgets(line_buffer, line_len, file)) {
    bool is_ok = true;
    ArrayList* sequence = parse_page_sequence(line_buffer);
    if (sequence == NULL) {
      printf("Invalid sequence format: %s", line_buffer);
      return EXIT_FAILURE;
    }

    for (int16_t i = sequence->count - 1; i >= 0; --i) {
      if (is_ok == false) {
        break;
      }

      for (int16_t j = i; j >= 0; --j) {
        if (map_contains(rules, array_list_get(sequence, i), array_list_get(sequence, j)) == true) {
          is_ok = false;
          break;
        }
      }
    }

    // Part one
    /* if (is_ok == true) { */
    /*   printf("Sequence %d is OK\n", sequence_number++); */
    /*   const uint16_t middle = array_list_get(sequence, sequence->count / 2); */
    /*   printf("Middle value: %d\n", middle); */
    /*   result += middle; */
    /* } else { */
    /*   printf("Sequence %d is NOT OK\n", sequence_number++); */
    /* } */

    // Part two
    if (is_ok == false) {
      printf("Sequence %d is NOT OK\n", sequence_number++);

      // Find first occurence that has n/2 numbers in front of it based on the rulse
      uint16_t middle = 0;
      uint16_t curr_number = 0;
      for (int16_t i = sequence->count; i >= 0; --i) {
        curr_number = array_list_get(sequence, i);
        if (count_occurences_in_front(rules, sequence, curr_number) == sequence->count / 2) {
          middle = curr_number;
          break;
        }
      }

      printf("New middle value: %d\n", middle);
      result += middle;
    }
  }

  printf("Result: %d", result);

  map_free(rules);
}

uint16_t* parse_rule(char* line) {
  uint16_t* rv = (uint16_t*)malloc(2 * sizeof(uint16_t));
  if (rv == NULL) {
    printf("Unable to allocate memory for rule\n");
    return NULL;
  }

  char* buffer = strtok(line, "|");  // Only 2-digit numbers
  if (buffer == NULL) {
    printf("No delimiter '|' found in %s\n", line);
  }

  rv[0] = (uint16_t)strtoul(buffer, NULL, 10);

  buffer = strtok(NULL, "|");
  if (buffer == NULL) {
    free(rv);
    return NULL;
  }

  rv[1] = strtoul(buffer, NULL, 10);

  return rv;
}

ArrayList* parse_page_sequence(char* line) {
  ArrayList* list = array_list_create(100);
  if (list == NULL) {
    printf("Unable to allocate memory for array list\n");
    return NULL;
  }

  char* buffer = strtok(line, ",");

  if (buffer == NULL) {
    array_list_free(list);
    return NULL;
  }

  printf("Parsed sequence numbers: ");
  while (buffer != NULL) {
    const uint16_t parsed = (uint16_t)strtol(buffer, NULL, 10);
    printf("%d, ", parsed);

    array_list_add(list, parsed);
    buffer = strtok(NULL, ",");
  }

  printf("\n");

  return list;
}

uint16_t count_occurences_in_front(const Map* rules, const ArrayList* sequence, const uint16_t number) {
  uint16_t occurences = 0;
  uint16_t curr_number = 0;
  for (uint16_t i = 0; i < sequence->count; ++i) {
    curr_number = array_list_get(sequence, i);
    if (curr_number == number) {
      continue;
    }

    if (map_contains(rules, number, curr_number) == true) {
      occurences++;
    }
  }
  return occurences;
}
