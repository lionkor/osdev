#pragma once

#include "terminal.h"


void kprint_init(void);
// alias for terminal_writestring
void kprint(const char* data);
void kprint_c(const char* data, enum vga_color color);
// the following append \n
void kperror(const char* data);
void kpwarning(const char* data);
void kplog(const char* data);
