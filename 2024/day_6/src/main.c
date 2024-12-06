#include <main.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>

int main(void) {
  FILE* file = fopen("data/input_test.txt", "r");
  const uint16_t file_size = 100;
  const uint16_t line_len = 10;  // including newline
  char buffer[file_size] = {'\0'};

  fread(buffer, sizeof(char), file_size, file);
  printf("%s", buffer);
}
