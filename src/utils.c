#include "utils.h"
#include <string.h>

bool is_bit_at_position_set(uint16_t value, uint16_t position)
{
    return (value >> (position - 1)) & 1;
}

bool prefix(const char *pre, const char *str)
{
    return strncmp(pre, str, strlen(pre)) == 0;
}

uint16_t swap16(uint16_t x)
{
    return (x << 8) | (x >> 8);
}

uint16_t sign_extend(uint16_t x, int bit_count)
{
    if ((x >> (bit_count - 1)) & 1) {
        x |= (0xFFFF << bit_count);
    }
    return x;
}
