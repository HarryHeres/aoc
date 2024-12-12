#include <main.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const char INPUT_FILENAME[] = "data/input.txt";
const uint32_t ROWS = 10;
const uint32_t COLS = 10;

int main(void) {
  FILE* file = fopen(INPUT_FILENAME, "r");
  if (access(INPUT_FILENAME, F_OK) != 0) {
    printf("File %s not found. Exiting...\n", INPUT_FILENAME);
    return EXIT_FAILURE;
  }

  fseek(file, 0, SEEK_END);
  if (ftell(file) == 0) {
    fclose(file);
    printf("File %s is empty. Exiting...\n", INPUT_FILENAME);
    return EXIT_FAILURE;
  }

  fseek(file, 0, SEEK_SET);
  printf("Part one: %lu\n", part_one(file));

  fseek(file, 0, SEEK_SET);
  printf("Part two: %lu\n", part_two(file));

  return EXIT_SUCCESS;
}

uint64_t part_one(FILE* file) {
  return 0;
}

uint64_t part_two(FILE* file) {
  return 0;
}
