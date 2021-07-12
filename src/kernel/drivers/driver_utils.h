#pragma once

#include <ktypes.h>

#define BIT_0 (1u << 0u)
#define BIT_1 (1u << 1u)
#define BIT_2 (1u << 2u)
#define BIT_3 (1u << 3u)
#define BIT_4 (1u << 4u)
#define BIT_5 (1u << 5u)
#define BIT_6 (1u << 6u)
#define BIT_7 (1u << 7u)

#define BIT_8 ((u16)(1u << 8u))
#define BIT_9 ((u16)(1u << 9u))
#define BIT_10 ((u16)(1u << 10u))
#define BIT_11 ((u16)(1u << 11u))
#define BIT_12 ((u16)(1u << 12u))
#define BIT_13 ((u16)(1u << 13u))
#define BIT_14 ((u16)(1u << 14u))
#define BIT_15 ((u16)(1u << 15u))

#define BIT_16 ((u32)(1u << 16u))
#define BIT_17 ((u32)(1u << 17u))
#define BIT_18 ((u32)(1u << 18u))
#define BIT_19 ((u32)(1u << 19u))
#define BIT_20 ((u32)(1u << 20u))
#define BIT_21 ((u32)(1u << 21u))
#define BIT_22 ((u32)(1u << 22u))
#define BIT_23 ((u32)(1u << 23u))
#define BIT_24 ((u32)(1u << 24u))
#define BIT_25 ((u32)(1u << 25u))
#define BIT_26 ((u32)(1u << 26u))
#define BIT_27 ((u32)(1u << 27u))
#define BIT_28 ((u32)(1u << 28u))
#define BIT_29 ((u32)(1u << 29u))
#define BIT_30 ((u32)(1u << 30u))
#define BIT_31 ((u32)(1u << 31u))

void drv_write_as_u8(uptr address, u8 value);
void drv_write_as_u16(uptr address, u16 value);
void drv_write_as_u32(uptr address, u32 value);

inline uptr drv_offset_addr_8(uptr ptr, u8 offset);
inline uptr drv_offset_addr_16(uptr val, u16 offset);
inline uptr drv_offset_addr_32(uptr val, u32 offset);

void drv_printf(const char* driver_name, const char* fmt, ...);
void drv_printf_error(const char* driver_name, const char* fmt, ...);
void drv_printf_warning(const char* driver_name, const char* fmt, ...);
