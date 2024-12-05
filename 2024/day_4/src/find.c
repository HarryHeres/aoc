#include <find.h>
#include <main.h>
#include <string.h>

uint find_ahead(const char* buffer, const uint start_idx) {
  return memcmp(&buffer[start_idx], XMAS, sizeof(XMAS) - 1) == 0 ? 1 : 0;
}

uint find_reverse(const char* buffer, const uint start_idx) {
  return memcmp(&buffer[start_idx - sizeof(SAMX) + 2], SAMX, sizeof(SAMX) - 1) == 0 ? 1 : 0;
}

uint find_above(const char* buffer, const uint start_idx, const uint line_len) {
  char tmp[sizeof(XMAS)] = {'\0'};

  for (uint i = 0; i < sizeof(tmp) - 1; ++i) {
    tmp[i] = buffer[start_idx - (i * line_len)];
  }

  return memcmp(&tmp, XMAS, sizeof(tmp)) == 0 ? 1 : 0;
}

uint find_above_left(const char* buffer, const uint start_idx, const uint line_len) {
  char tmp[sizeof(XMAS)] = {'\0'};

  for (uint i = 0; i < sizeof(tmp) - 1; ++i) {
    tmp[i] = buffer[start_idx - (i * line_len) - i];
  }

  return memcmp(&tmp, XMAS, sizeof(tmp)) == 0 ? 1 : 0;
}

uint find_above_right(const char* buffer, const uint start_idx, const uint line_len) {
  char tmp[sizeof(XMAS)] = {'\0'};

  for (uint i = 0; i < sizeof(tmp) - 1; ++i) {
    tmp[i] = buffer[start_idx - (i * line_len) + i];
  }

  return memcmp(&tmp, XMAS, sizeof(tmp)) == 0 ? 1 : 0;
}

uint find_below(const char* buffer, const uint start_idx, const uint line_len) {
  char tmp[sizeof(XMAS)] = {'\0'};
  for (uint i = 0; i < sizeof(tmp) - 1; ++i) {
    tmp[i] = buffer[start_idx + (i * line_len)];
  }

  return memcmp(&tmp, XMAS, sizeof(tmp)) == 0 ? 1 : 0;
}

uint find_below_left(const char* buffer, const uint start_idx, const uint line_len) {
  char tmp[sizeof(XMAS)] = {'\0'};
  for (uint i = 0; i < sizeof(tmp) - 1; ++i) {
    tmp[i] = buffer[start_idx + (i * line_len) - i];
  }

  return memcmp(&tmp, XMAS, sizeof(tmp)) == 0 ? 1 : 0;
}

uint find_below_right(const char* buffer, const uint start_idx, const uint line_len) {
  char tmp[sizeof(XMAS)] = {'\0'};
  for (uint i = 0; i < sizeof(tmp) - 1; ++i) {
    tmp[i] = buffer[start_idx + (i * line_len) + i];
  }

  return memcmp(&tmp, XMAS, sizeof(tmp)) == 0 ? 1 : 0;
}
