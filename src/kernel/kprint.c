#include "kprint.h"

#include <string.h>

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
            for (size_t i = cur; i < cur + (W - current_x); ++i) {
                buffer[i] = ' ';
                colors[i] = color;
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
