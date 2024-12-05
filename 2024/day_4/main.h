#ifndef _MAIN_
#define _MAIN_
#include <stdbool.h>
#include <sys/types.h>

const uint find_xmas(const char* buffer, const uint buffer_size, const uint line_len);

const uint find_ahead(const char* buffer, const uint start_idx);

const uint find_reverse(const char* buffer, const uint start_idx);

const uint find_above(const char* buffer, const uint start_idx, const uint line_len);

const uint find_above_left(const char* buffer, const uint start_idx, const uint line_len);

const uint find_above_right(const char* buffer, const uint start_idx, const uint line_len);

const uint find_below(const char* buffer, const uint start_idx, const uint line_len);

const uint find_below_left(const char* buffer, const uint start_idx, const uint line_len);

const uint find_below_right(const char* buffer, const uint start_idx, const uint line_len);

#endif
