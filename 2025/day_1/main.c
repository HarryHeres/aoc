#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int part_one(FILE *input_file) {
  char buff[6] = {0};
  int curr = 50;
  int rv = 0;

  while (fgets(buff, sizeof(buff), input_file)) {
    int next = atoi(&buff[1]);

    if (buff[0] == 'L') {
      next = -next;
    }

    curr = (curr + next) % 100;
    // printf("Curr: %d\n", curr);

    if (curr == 0) {
      ++rv;
    }
  }

  return rv;
}

int part_two(FILE *input_file) {
  char buff[6] = {0};
  int prev = 0;
  int curr = 50;
  int rv = 0;

  while (fgets(buff, sizeof(buff), input_file)) {
    int next = atoi(&buff[1]);

    rv += next / 100;
    next %= 100;

    if (buff[0] == 'L') {
      next = -next;
    }

    prev = curr;
    curr = curr + next;

    if (curr != 0 && prev != 0 && (prev ^ curr) < 0) {
      ++rv;
    }

    if (abs(curr) > 100) {
      ++rv;
    }

    curr %= 100;
    if (curr == 0) {
      ++rv;
    }
  }

  return rv;
}

int main() {
  // FILE *input_file = fopen("data/test.txt", "r");
  FILE *input_file = fopen("data/input.txt", "r");

  printf("Part 1: %d\n", part_one(input_file));

  fseek(input_file, 0, 0);

  printf("Part 2: %d\n", part_two(input_file));
  return 0;
}
