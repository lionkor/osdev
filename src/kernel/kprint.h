#pragma once

#include "terminal.h"

#define KERNEL_PRINTF_MAXLEN 1024

void kprint_init(void);
// alias for terminal_writestring
void kprint(const char* data);
void kprintf(const char* fmt, ...);
void kprint_flush(void);

void kprint_c(const char* data, enum vga_color color);
// the following append \n
void kperror(const char* data);
void kpferror(const char* fmt, ...);
void kpwarning(const char* data);
void kpfwarning(const char* fmt, ...);
void kplog(const char* data);
void kprint_hex_8(u8 data);
void kprint_hex_16(u16 data);
void kprint_hex_32(u32 data);

void kprint_bin_8(u8 data);
void kprint_bin_16(u16 data);
void kprint_bin_32(u32 data);
