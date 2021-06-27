#include "binops.h"

const char hexmap[] = "0123456789abcdef####"; // #'s to detect overflow

void u8_to_hex(u8 x, char* buf) {
    buf[1] = hexmap[(x & 0xf0) >> 4];
    buf[0] = hexmap[x & 0x0f];
}

void u16_to_hex(u16 x, char* buf) {
    for (u8fast i = 0; i < 4; ++i) {
        buf[4 - 1 - i] = hexmap[x & 0xf];
        x >>= 4;
    }
}

void u32_to_hex(u32 x, char* buf) {
    for (u8fast i = 0; i < 8; ++i) {
        buf[8 - 1 - i] = hexmap[x & 0xf];
        x >>= 4;
    }
}

void u32_to_dec(u32 x, char* buf) {
    u32 multiplier = 1;
    u32 i = 0;
    while (true) {
        buf[0] = '0' + (x & 0xf) * multiplier;
        x >>= 4;
        multiplier *= 16;
        ++i;
        if (x == 0) {
            break;
        }
    }
}
