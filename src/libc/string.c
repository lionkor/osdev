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

int vsprintf(char* buf, const char* fmt, va_list args) {
    if (!buf) {
        return -1;
    }
    size_t fmtlen = strlen(fmt);
    // use va_arg to get the next arg
    size_t k = 0;
    for (size_t i = 0; i < fmtlen; ++i) {
        char c = fmt[i];
        switch (c) {
        case '%': {
            ++i;
            if (i >= fmtlen) {
                break;
            }
            c = fmt[i];
            switch (c) {
            case '%': { // %% - literal percent sign
                buf[k++] = '%';
                break;
            }
            case 'x': { // %x - 32 bit unsigned hex
                const char* b = "0x00000000";
                memcpy(&buf[k], b, 10);
                k += 2; // for 0x
                u32_to_hex(va_arg(args, uint32_t), &buf[k]);
                k += 8; // for the 8 0's
                break;
            }
            case 's': { // %s - null terminated string
                const char* str = va_arg(args, const char*);
                if (str == NULL) {
                    str = "(null)";
                }
                size_t len = strlen(str);
                memcpy(&buf[k], str, len);
                k += len;
                break;
            }
            default: {
                // unknown format specifier
            }
            }

            break;
        }
        default: {
            buf[k++] = c;
            break;
        }
        }
    }
    buf[k] = 0;
    return k - 1; // return count excluding final null byte
}
