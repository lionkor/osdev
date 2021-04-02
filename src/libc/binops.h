#pragma once

#include <ktypes.h>

// buf needs to be of size sizeof(u8)
void u8_to_hex(u8 x, char* buf);
// buf needs to be of size sizeof(u16)
void u16_to_hex(u16 x, char* buf);
// buf needs to be of size sizeof(u32)
void u32_to_hex(u32 x, char* buf);
