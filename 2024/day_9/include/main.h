#ifndef _MAIN_
#define _MAIN_

#include <array_list.h>
#include <stdint.h>

void write_block(ArrayList* result, const uint32_t* write_buffer, uint32_t* write_buffer_idx, const uint32_t count);

void print_result_disk(const ArrayList* disk);

#endif
