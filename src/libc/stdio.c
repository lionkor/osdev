#include "stdio.h"
#include "binops.h"
#include "ktypes.h"

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

int sprintf(char* buf, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int ret = vsprintf(buf, fmt, args);
    va_end(args);
    return ret;
}
