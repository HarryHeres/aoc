#ifndef _MAIN_
#define _MAIN_

#include <stdint.h>
#include <stdio.h>

uint64_t process_stones(FILE* file, const uint16_t iters);

uint64_t process_stone(const uint64_t stone_id, const uint16_t remaining_iters);

#endif
