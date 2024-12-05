#ifndef _MAIN_
#define _MAIN_

#include <array_list.h>
#include <stdint.h>
#include "map.h"

uint16_t* parse_rule(char* line);

ArrayList* parse_page_sequence(char* line);

uint16_t count_occurences_in_front(const Map* rules, const ArrayList* sequence, const uint16_t number);

#endif
