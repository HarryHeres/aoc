#ifndef _MAIN_
#define _MAIN_

#include <stdbool.h>
#include <stdint.h>

uint32_t traverse_map(char* map, const uint32_t rows, const uint32_t columns, const uint32_t start_x,
                      const uint32_t start_y);

uint32_t find_obstruction_places(char* map, const uint32_t rows, const uint32_t columns, const uint32_t start_x,
                                 const uint32_t start_y);

bool contains_cycle(char* map, const uint32_t rows, const uint32_t columns, const uint32_t start_x,
                    const uint32_t start_y);

#endif
