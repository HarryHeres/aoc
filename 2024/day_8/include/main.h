#ifndef _MAIN_
#define _MAIN_

#include <stdint.h>
#include "array_list.h"

uint32_t find_antinodes(char* map);

void check_for_antennas(const char* map, const char frequency, const uint32_t start_x, const uint32_t start_y,
                        ArrayList* antinodes);

void print_map(char* map, const uint32_t rows, const uint32_t cols);
#endif
