#ifndef UTILITY_H_
#define UTILITY_H_

#include "math.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

bool is_power_of_two (uint32_t const val);
bool is_parity_odd (uint32_t const inVal);
uint8_t count_set_bits (uint32_t const inVal32bit);
uint64_t swap_bits (uint64_t in_val);
  
#ifdef __cplusplus
}
#endif

#endif /* UTILITY_H_ */
