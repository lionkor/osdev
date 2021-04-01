#include "terminal.h"
#include "ports.h"
#include <ktypes.h>

static inline u8 vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

static inline u16 vga_entry(u8 uc, u8 color) {
    return (u16)uc | (u16)color << 8;
}

size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
u8 terminal_color;
u16* terminal_buffer;

void terminal_initialize(void) {
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    terminal_buffer = (u16*)0xB8000;
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

void terminal_setcolor(u8 color) {
    terminal_color = color;
}

void terminal_putentryat(char c, u8 color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) {
    terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
    if (++terminal_column == VGA_WIDTH) {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT)
            terminal_row = 0;
    }
}

void terminal_write(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (data[i] == '\n') {
            ++terminal_row;
            terminal_column = 0;
        } else {
            terminal_putchar(data[i]);
        }
    }
}

void terminal_writestring(const char* data) {
    terminal_write(data, strlen(data));
}

void kprint(const char* data) {
    terminal_writestring(data);
}

void kprint_c(const char* data, enum vga_color color) {
    // push old color
    enum vga_color old_color = terminal_color;
    terminal_setcolor(color);
    terminal_writestring(data);
    terminal_setcolor(old_color);
}

#define print_kernel() kprint("[kernel] ")

void kperror(const char* data) {
    print_kernel();
    kprint_c("error", VGA_COLOR_LIGHT_RED);
    kprint(": ");
    kprint(data);
    kprint("\n");
}

void kpwarning(const char* data) {
    print_kernel();
    kprint_c("warning", VGA_COLOR_LIGHT_BLUE);
    kprint(": ");
    kprint(data);
    kprint("\n");
}

void kplog(const char* data) {
    print_kernel();
    kprint(data);
    kprint("\n");
}
