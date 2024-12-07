#include <array_list.h>
#include <math.h>
#include <sequence.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Sequence* sequence_init(const uint32_t capacity, const uint64_t calibration_value) {
  Sequence* rv = (Sequence*)malloc(sizeof(Sequence));

  rv->calibration_value = calibration_value;
  rv->values = array_list_init(capacity);
  rv->operators = (char*)malloc(capacity - 1);

  memset(rv->operators, '\0', capacity - 1);

  return rv;
}

void sequence_add_value(Sequence* this, const uint32_t value) {
  array_list_add(this->values, value);
}
// Part one
/* bool sequence_is_valid(Sequence* this) { */
/*   for (uint32_t i = 0; i < pow(2, this->values->count - 1); ++i) { */
/*     apply_operator_mask(this, i); */
/*     if (sequence_test_equation(this)) { */
/*       return true; */
/*     } */
/*   } */

/*   return false; */
/* } */

/* void apply_operator_mask(Sequence* this, uint32_t mask) { */
/*   for (uint32_t i = 0; i < this->values->count - 1; ++i) { */
/*     if ((1 << i & mask) == 1 << i) { */
/*       this->operators[i] = '*'; */
/*     } else { */
/*       this->operators[i] = '+'; */
/*     } */
/*   } */
/* } */

bool sequence_is_valid(Sequence* this) {

  for (uint32_t i = 0; i < pow(3, this->values->count - 1); ++i) {
    apply_operator_mask(this, i);
    if (sequence_test_equation(this)) {
      return true;
    }
  }
  return false;
}

void apply_operator_mask(Sequence* this, uint32_t mask) {
  memset(this->operators, 0, this->values->count - 1);
  for (uint32_t _ = 0; _ < mask; ++_) {
    if (this->operators[0] < 2) {
      ++this->operators[0];
    } else {
      uint32_t next_idx = 0;
      while (this->operators[next_idx] > 1) {
        ++next_idx;
      }
      ++this->operators[next_idx];
      memset(this->operators, 0, next_idx);
    }
  }
}

bool sequence_test_equation(Sequence* this) {
  uint64_t result = array_list_get(this->values, 0);
  char buffer[100];
  memset(buffer, 0, sizeof(buffer));
  for (uint32_t i = 1; i < this->values->count; ++i) {
    switch (this->operators[i - 1]) {
      case 0: {
        result += array_list_get(this->values, i);
        break;
      }
      case 1: {
        result *= array_list_get(this->values, i);
        break;
      }
      case 2: {
        sprintf(buffer, "%ld%d", result, array_list_get(this->values, i));
        result = strtol(buffer, NULL, 10);
        break;
      }
    }
  }

  return result == this->calibration_value;
}

void sequence_clear(Sequence* this, const uint64_t new_calibration_value) {
  array_list_clear(this->values);

  memset(this->operators, '\0', this->values->capacity - 1);
  this->calibration_value = new_calibration_value;
}

void sequence_free(Sequence* this) {
  array_list_free(this->values);
  free(this->operators);
  free(this);
}
