#include <main.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

const uint32_t ROWS = 0;
const uint32_t COLS = 0;

int main(void) {
  FILE* file = fopen("data/input_test.txt", "r");

  printf("Part one: %lld\n", part_one(file));
  printf("Part two: %lld\n", part_two(file));

  return EXIT_SUCCESS;
}

uint64_t part_one(FILE* file) {
  return 0;
}

uint64_t part_two(FILE* file) {
  return 0;
}
