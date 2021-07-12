#pragma once

#include "stdarg.h"
#include "string.h"

int vsprintf(char* buf, const char* fmt, va_list args);
int sprintf(char* buf, const char* fmt, ...);
