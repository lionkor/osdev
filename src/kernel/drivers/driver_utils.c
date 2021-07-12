#include "driver_utils.h"
#include <kernel/kprint.h>
#include <stdio.h>
#include <string.h>

void drv_write_as_u8(uptr address, u8 value) {
    *(u8*)(address) = value;
}

void drv_write_as_u16(uptr address, u16 value) {
    *(u16*)(address) = value;
}

void drv_write_as_u32(uptr address, u32 value) {
    *(u16*)(address) = value;
}

void drv_printf(const char* driver_name, const char* fmt, ...) {
    char namebuf[64];
    sprintf(namebuf, "[drv/%s] ", driver_name);
    kprint_c(namebuf, VGA_COLOR_LIGHT_GREY);
    va_list args;
    va_start(args, fmt);
    char buf[KERNEL_PRINTF_MAXLEN];
    vsprintf(buf, fmt, args);
    va_end(args);
    kprint(buf);
    kprint_flush();
}

void drv_printf_error(const char* driver_name, const char* fmt, ...) {
    char namebuf[64];
    sprintf(namebuf, "[drv/%s] ", driver_name);
    kprint_c(namebuf, VGA_COLOR_LIGHT_GREY);
    kprint_c("error", VGA_COLOR_LIGHT_RED);
    kprint_c(": ", VGA_COLOR_LIGHT_GREY);
    va_list args;
    va_start(args, fmt);
    char buf[KERNEL_PRINTF_MAXLEN];
    vsprintf(buf, fmt, args);
    va_end(args);
    kprint(buf);
    kprint_flush();
}

void drv_printf_warning(const char* driver_name, const char* fmt, ...) {
    char namebuf[64];
    sprintf(namebuf, "[drv/%s] ", driver_name);
    kprint_c(namebuf, VGA_COLOR_LIGHT_GREY);
    kprint_c("warning", VGA_COLOR_LIGHT_BLUE);
    kprint_c(": ", VGA_COLOR_LIGHT_GREY);
    va_list args;
    va_start(args, fmt);
    char buf[KERNEL_PRINTF_MAXLEN];
    vsprintf(buf, fmt, args);
    va_end(args);
    kprint(buf);
    kprint_flush();
}

uptr drv_offset_addr_8(uptr ptr, u8 offset) {
    u8* cast_ptr = (u8*)(ptr);
    cast_ptr += offset;
    return (uptr)(cast_ptr);
}

uptr drv_offset_addr_16(uptr ptr, u16 offset) {
    u16* cast_ptr = (u16*)(ptr);
    cast_ptr += offset;
    return (uptr)(cast_ptr);
}

uptr drv_offset_addr_32(uptr ptr, u32 offset) {
    u32* cast_ptr = (u32*)(ptr);
    cast_ptr += offset;
    return (uptr)(cast_ptr);
}
