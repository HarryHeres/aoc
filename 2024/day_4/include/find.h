#ifndef _FIND_
#define _FIND_
#include <stdbool.h>
#include <sys/types.h>

uint find_ahead(const char* buffer, const uint start_idx);

uint find_reverse(const char* buffer, const uint start_idx);

uint find_above(const char* buffer, const uint start_idx, const uint line_len);

uint find_above_left(const char* buffer, const uint start_idx, const uint line_len);

uint find_above_right(const char* buffer, const uint start_idx, const uint line_len);

uint find_below(const char* buffer, const uint start_idx, const uint line_len);

uint find_below_left(const char* buffer, const uint start_idx, const uint line_len);

uint find_below_right(const char* buffer, const uint start_idx, const uint line_len);

#endif
