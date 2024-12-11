#ifndef _MAIN_
#define _MAIN_

#include <stdint.h>
#include <stdio.h>
#include "array_list.h"
#include "linked_list.h"

uint64_t part_one(FILE* file);

void apply_rules(LinkedList* stones);

uint64_t part_two(FILE* file);

void process_stone(ArrayList** dict, const uint64_t value, const uint32_t iters);

#endif
