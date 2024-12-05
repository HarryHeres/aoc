#ifndef _MAIN_
#define _MAIN_
#include <sys/types.h>

static const char XMAS[] = "XMAS";
static const char SAMX[] = "SAMX";

uint find_xmas(const char* buffer, const uint buffer_size, const uint line_len);

uint find_mas(const char* buffer, const uint buffer_size, const uint line_len);

#endif
