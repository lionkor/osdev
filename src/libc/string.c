#include "string.h"
#include "stdarg.h"

#include <binops.h>

size_t strlen(const char* str) {
    size_t i = 0;
    for (; str[i]; ++i)
        ;
    return i;
}

void* memcpy(void* dstptr, const void* srcptr, size_t n) {
    u8* dst = dstptr;
    const u8* src = srcptr;
    for (size_t i = 0; i < n; ++i) {
        dst[i] = src[i];
    }
    return dst;
}

void* memmove(void* dstptr, const void* srcptr, size_t size) {
    unsigned char* dst = (unsigned char*)dstptr;
    const unsigned char* src = (const unsigned char*)srcptr;
    if (dst < src) {
        for (size_t i = 0; i < size; i++)
            dst[i] = src[i];
    } else {
        for (size_t i = size; i != 0; i--)
            dst[i - 1] = src[i - 1];
    }
    return dstptr;
}

void* memset(void* dst, int c, size_t n) {
    u8* buf = (u8*)dst;
    for (size_t i = 0; i < n; ++i) {
        buf[i] = (u8)c;
    }
    return buf;
}

int memcmp(const void* aptr, const void* bptr, size_t size) {
    const unsigned char* a = (const unsigned char*)aptr;
    const unsigned char* b = (const unsigned char*)bptr;
    for (size_t i = 0; i < size; i++) {
        if (a[i] < b[i])
            return -1;
        else if (b[i] < a[i])
            return 1;
    }
    return 0;
}

