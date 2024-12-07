#ifndef _SEQUENCE_
#define _SEQUENCE_
#include <array_list.h>
#include <stdint.h>

typedef struct Sequence {
  uint64_t calibration_value;
  ArrayList* values;
  char* operators;
} Sequence;

Sequence* sequence_init(const uint32_t capacity, const uint64_t calibration_value);

void sequence_add_value(Sequence* this, const uint32_t value);

bool sequence_is_valid(Sequence* this);

void apply_operator_mask(Sequence* this, uint32_t mask);

bool sequence_test_equation(Sequence* this);

void sequence_clear(Sequence* this, const uint64_t new_calibration_value);

void sequence_free(Sequence* this);

#endif
