#include "kprint.h"

#include <string.h>
#include <binops.h>

#define print_kernel() kprint_internal("[kernel] ", VGA_COLOR_LIGHT_GREY)

#define W 80
#define H 25

static char buffer[W * H];
static u8 colors[W * H];

static size_t current_x = 0;
static size_t current_y = 0;

static inline void kprint_flush(void) {
    for (size_t x = 0; x < W; ++x) {
        for (size_t y = 0; y < H; ++y) {
            terminal_putentryat(buffer[x + y * W], colors[x + y * W], x, y);
        }
    }
}

// just write in the last line and then call this
static inline void scroll() {
    for (size_t i = 0; i < H - 1; ++i) {
        for (size_t k = 0; k < W; ++k) {
            buffer[k + i * W] = buffer[k + (i + 1) * W];
            colors[k + i * W] = colors[k + (i + 1) * W];
        }
    }
}

void kprint_internal(const char* data, u8 color) {
    for (size_t i = 0; data[i]; ++i) {
        if (data[i] == '\n') {
            // clear the rest of the line
            size_t cur = current_x + W * current_y;
            for (size_t k = cur; k < cur + (W - current_x); ++k) {
                buffer[k] = ' ';
                colors[k] = color;
            }
            current_x = 0;
            current_y += 1;
            if (current_y >= H) {
                scroll();
                current_y = H - 1;
            }
        } else {
            buffer[current_x + W * current_y] = data[i];
            colors[current_x + W * current_y] = color;

            if (++current_x >= W) {
                current_x = 0;
                current_y += 1;
                if (current_y >= H) {
                    scroll();
                    current_y = H - 1;
                }
            }
        }
    }
}

void kprint(const char* data) {
    kprint_c(data, VGA_COLOR_LIGHT_GREY);
    kprint_flush();
}

void kprint_c(const char* data, enum vga_color color) {
    kprint_internal(data, color);
    kprint_flush();
}

void kperror(const char* data) {
    print_kernel();
    kprint_internal("error", VGA_COLOR_LIGHT_RED);
    kprint_internal(": ", VGA_COLOR_LIGHT_GREY);
    kprint_internal(data, VGA_COLOR_LIGHT_GREY);
    kprint_internal("\n", VGA_COLOR_LIGHT_GREY);
    kprint_flush();
}

void kpwarning(const char* data) {
    print_kernel();
    kprint_internal("warning", VGA_COLOR_LIGHT_BLUE);
    kprint_internal(": ", VGA_COLOR_LIGHT_GREY);
    kprint_internal(data, VGA_COLOR_LIGHT_GREY);
    kprint_internal("\n", VGA_COLOR_LIGHT_GREY);
    kprint_flush();
}

void kplog(const char* data) {
    print_kernel();
    kprint_internal(data, VGA_COLOR_LIGHT_GREY);
    kprint_internal("\n", VGA_COLOR_LIGHT_GREY);
    kprint_flush();
}

void kprint_init() {
    for (size_t i = 0; i < sizeof(buffer); ++i) {
        buffer[i] = ' ';
        colors[i] = VGA_COLOR_LIGHT_GREY;
    }
    kprint_flush();
}

static const char hex_map[] = "0123456789abcdef";

void kprint_hex_8(u8 data) {
    // 0x00
    char buf[] = "0x00";
    u8_to_hex(data, buf + 2);
    kprint_internal(buf, VGA_COLOR_LIGHT_GREEN);
    kprint_flush();
}

void kprint_hex_16(u16 data) {
    // 0x00'00
    char buf[] = "0x0000";
    u16_to_hex(data, buf + 2);
    kprint_internal(buf, VGA_COLOR_LIGHT_GREEN);
    kprint_flush();
}

void kprint_hex_32(u32 data) {
    // 0x00'00'00'00
    char buf[] = "0x00000000";
    u32_to_hex(data, buf + 2);
    kprint_internal(buf, VGA_COLOR_LIGHT_GREEN);
    kprint_flush();
}

void kprint_bin_8(u8 data) {
    char buf[] = "0b00000000";
    for (size_t i = 0; i < 8; ++i) {
        bool bit = data % 2;
        data /= 2;
        buf[sizeof(buf) - 2 - i] = '0' + bit;
    }
    buf[sizeof(buf) - 1] = 0;
    kprint_internal(buf, VGA_COLOR_LIGHT_GREEN);
    kprint_flush();
}

void kprint_bin_16(u16 data) {
    char buf[] = "0b0000000000000000";
    for (size_t i = 0; i < 16; ++i) {
        bool bit = data % 2;
        data /= 2;
        buf[sizeof(buf) - 2 - i] = '0' + bit;
    }
    buf[sizeof(buf) - 1] = 0;
    kprint_internal(buf, VGA_COLOR_LIGHT_GREEN);
    kprint_flush();
}

void kprint_bin_32(u32 data) {
    char buf[] = "0b00000000000000000000000000000000";
    for (size_t i = 0; i < 32; ++i) {
        bool bit = data % 2;
        data /= 2;
        buf[sizeof(buf) - 2 - i] = '0' + bit;
    }
    buf[sizeof(buf) - 1] = 0;
    kprint_internal(buf, VGA_COLOR_LIGHT_GREEN);
    kprint_flush();
}
