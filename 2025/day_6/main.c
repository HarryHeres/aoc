#include "src/headers/array_list.h"
#include <_stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  ArrayList *numbers;
  ArrayList *operators;
  size_t number_line_count;
} Homework;

uint64_t part_two(FILE *input, Homework *homework) {
  if (input == NULL || homework == NULL) {
    return 0;
  }

  char *lines[homework->number_line_count];
  char *line;
  size_t allocated = 0;
  for (int i = 0; i < homework->number_line_count; ++i) {
    line = NULL;
    getline(&line, &allocated, input);
    lines[i] = line;
  }

  char *operators = NULL;
  getline(&operators, &allocated, input);

  char curr_op = '\0';
  uint64_t curr_res = 0;
  uint64_t rv = 0;
  char curr_val[20];
  bool is_blank_col;
  for (int col = 0; col < strlen(lines[0]) - 1; ++col) {
    is_blank_col = true;
    memset(curr_val, 0, sizeof(curr_val));

    if (operators[col] != ' ') {
      curr_op = operators[col];

      switch (curr_op) {
      case '+':
        curr_res = 0;
        break;
      case '*':
        curr_res = 1;
        break;
      default:
        printf("Unknown operation: %c\n", curr_op);
        return 0;
      }
    }

    for (int i = 0; i < homework->number_line_count; ++i) {
      is_blank_col &= lines[i][col] == ' ';
      sprintf(curr_val, "%s%c", curr_val, lines[i][col]);
    }

    if (is_blank_col && operators[col] == ' ') {
      rv += curr_res;
    } else {
      switch (curr_op) {
      case '+':
        curr_res += strtol(curr_val, NULL, 10);
        break;
      case '*':
        curr_res *= strtol(curr_val, NULL, 10);
        break;
      default:
        printf("Unknown operation: %c", curr_op);
        return 0;
      }
    }
  }

  rv += curr_res;

  for (int i = 0; i < homework->number_line_count; ++i) {
    free(lines[i]);
  }

  free(operators);
  return rv;
}

uint64_t part_one(Homework *homework) {
  if (homework == NULL) {
    return 0;
  }

  uint64_t results[homework->operators->size];

  char *curr_op;
  for (size_t i = 0; i < homework->operators->size; ++i) {
    curr_op = (char *)array_list_get(homework->operators, i);
    switch (*curr_op) {
    case '+':
      results[i] = 0;
      break;
    case '*':
      results[i] = 1;
      break;
    default:
      printf("Unknown operation: %c", *curr_op);
      return 0;
    }
  }

  uint64_t *curr;
  size_t op_idx = 0;
  for (size_t i = 0; i < homework->numbers->size; ++i) {
    curr = array_list_get(homework->numbers, i);
    op_idx = i % homework->operators->size;
    curr_op = (char *)array_list_get(homework->operators, op_idx);
    switch (*curr_op) {
    case '+':
      results[op_idx] += *curr;
      break;
    case '*':
      results[op_idx] *= *curr;
      break;
    default:
      printf("Unknown operation: %c", *curr_op);
      return 0;
    }
  }

  uint64_t rv = 0;
  for (size_t i = 0; i < homework->operators->size; ++i) {
    rv += results[i];
  }

  return rv;
}

Homework *parse_input(FILE *input) {
  if (input == NULL) {
    return NULL;
  }

  char *line = NULL;
  size_t allocated = 0;
  ssize_t read = getline(&line, &allocated, input);

  fseek(input, 0, SEEK_END);
  ssize_t line_count = ftell(input) / read;
  fseek(input, read, 0);

  ArrayList *numbers = array_list_create(100000);

  char *token = strtok(line, " ");
  uint32_t *val;

  while (strcmp(token, "\n") != 0) {
    val = malloc(sizeof(uint32_t));
    if (val == NULL) {
      return NULL;
    }

    *val = strtol(token, NULL, 10);
    array_list_add(numbers, val);
    token = strtok(NULL, " ");
  }

  free(line);

  for (size_t i = 1; i < line_count - 1; ++i) {
    line = NULL;
    getline(&line, &allocated, input);

    token = strtok(line, " ");
    while (token != NULL && strcmp(token, "\n") != 0) {
      val = malloc(sizeof(uint32_t));
      if (val == NULL) {
        return NULL;
      }

      *val = strtol(token, NULL, 10);
      array_list_add(numbers, val);
      token = strtok(NULL, " ");
    }

    free(line);
  }

  ArrayList *operators = array_list_create(numbers->size);
  line = NULL;
  getline(&line, &allocated, input);
  token = strtok(line, " ");

  char *op;
  while (token != NULL && strcmp(token, "\n") != 0) {
    op = malloc(sizeof(char));
    *op = *token;
    array_list_add(operators, op);
    token = strtok(NULL, " ");
  }

  free(line);

  Homework *rv = malloc(sizeof(Homework));
  if (rv == NULL) {
    array_list_free(numbers);
    array_list_free(operators);
    return NULL;
  }

  rv->numbers = numbers;
  rv->operators = operators;
  rv->number_line_count = line_count - 1;
  return rv;
}

int main() {
  // FILE *input = fopen("data/test.txt", "r");
  FILE *input = fopen("data/input.txt", "r");
  if (input == NULL) {
    return EXIT_FAILURE;
  }

  Homework *homework = parse_input(input);
  if (homework == NULL) {
    return EXIT_FAILURE;
  }

  printf("Part one: %llu\n", part_one(homework));
  fseek(input, 0, 0);
  printf("Part two: %llu\n", part_two(input, homework));

  array_list_free(homework->numbers);
  array_list_free(homework->operators);
  free(homework);
  fclose(input);

  return EXIT_SUCCESS;
}
