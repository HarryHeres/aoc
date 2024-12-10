#ifndef _MAIN_
#define _MAIN_

#include <stdint.h>
#include <trail.h>

uint32_t find_trails(TrailPoint* map, const uint32_t start_idx);

void reset_map(TrailPoint* map);

#endif
