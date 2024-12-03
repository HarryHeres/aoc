#ifndef _MAIN_
#define _MAIN_
#include <stdbool.h>
#include <sys/types.h>

const uint check_for_match_do(const uint buffer_size, const char buffer[],
                              const uint start_idx, bool *active);

const uint check_for_match_mul(const uint buffer_size, const char buffer[],
                               const uint start_idx, long long *result);

#endif
