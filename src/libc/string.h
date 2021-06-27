#include <ktypes.h>

#include <stdarg.h>

size_t strlen(const char* str);
int vsprintf(char* buf, const char* fmt, va_list args);
void* memcpy(void* __restrict dst, const void* __restrict src, size_t n);
void* memmove(void* dst, const void* src, size_t n);
void* memset(void* dst, int c, size_t n);
int memcmp(const void* a, const void* b, size_t n);
