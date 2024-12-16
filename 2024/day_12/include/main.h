#ifndef _MAIN_
#define _MAIN_

#include <point.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

uint64_t part_one(FILE* file);

uint32_t process_region(Point** map, uint32_t start_idx);

uint64_t part_two(FILE* file);

#endif
