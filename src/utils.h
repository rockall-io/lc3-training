#include <stdint.h>
#include <stdbool.h>

bool is_bit_at_position_set(uint16_t value, uint16_t position);
bool prefix(const char *pre, const char *str);
uint16_t swap16(uint16_t x);
uint16_t sign_extend(uint16_t x, int bit_count);