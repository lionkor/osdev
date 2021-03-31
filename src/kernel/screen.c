#include "screen.h"
#include "ports.h"

int get_cursor_offset();
void set_cursor_offset(i32 offset);
i32 print_char(char c, i32 col, i32 row, char attr);
i32 get_offset(i32 col, i32 row);
i32 get_offset_row(i32 offset);
i32 get_offset_col(i32 offset);

void kprint_at(char* msg, i32 col, i32 row) {
    i32 offset = 0;
    if (col >= 0 && row >= 0) {
        offset = get_offset(col, row);
    } else {
        offset = get_cursor_offset();
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }

    int i = 0;
    while (msg[i] != 0) {
        offset = print_char(msg[i++], col, row, WHITE_ON_BLACK);
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
}

void kprint(char* msg) {
    kprint_at(msg, -1, -1);
}

i32 print_char(char c, i32 col, i32 row, char attr) {
    u8* vm = (u8*)VIDEO_ADDRESS;
    if (!attr) {
        attr = WHITE_ON_BLACK;
    }
    // print red E on error
    if (col >= MAX_COLS || row >= MAX_ROWS) {
        vm[2 * (MAX_COLS) * (MAX_ROWS)-2] = 'E';
        vm[2 * (MAX_COLS) * (MAX_ROWS)-1] = RED_ON_WHITE;
        return get_offset(col, row);
    }
    i32 offset = 0;
    if (col >= 0 && row >= 0) {
        offset = get_offset(col, row);
    } else {
        offset = get_cursor_offset();
    }

    if (c == '\n') {
        row = get_offset_row(offset);
        offset = get_offset(0, row + 1);
    } else {
        vm[offset] = c;
        vm[offset + 1] = attr;
        offset += 2;
    }
    set_cursor_offset(offset);
    return offset;
}

i32 get_cursor_offset() {
    i32 offset = 0;
    port_byte_out(REG_SCREEN_CTRL, 0x0f); // low byte
    offset |= port_byte_in(REG_SCREEN_DATA);
    port_byte_out(REG_SCREEN_CTRL, 0x0e); // high byte
    offset |= ((u16)port_byte_in(REG_SCREEN_DATA)) << 8;
    return offset;
}

void set_cursor_offset(i32 offset) {
    // TODO: offset/=2 ??
    port_byte_out(REG_SCREEN_CTRL, 0x0f);
    port_byte_out(REG_SCREEN_DATA, (u8)(offset & 0xff));
    port_byte_out(REG_SCREEN_CTRL, 0x0e);
    port_byte_out(REG_SCREEN_DATA, (u8)((offset >> 8) & 0xff));
}

void clear_screen() {
    i32 screen_size = MAX_COLS * MAX_ROWS;
    u8* vm = (u8*)VIDEO_ADDRESS;
    for (i32 i = 0; i < screen_size; ++i) {
        vm[i * 2] = ' ';
        vm[i * 2 + 1] = WHITE_ON_BLACK;
    }
    set_cursor_offset(get_offset(0, 0));
}

i32 get_offset(i32 col, i32 row) {
    return 2 * (row * MAX_COLS + col);
}

i32 get_offset_row(i32 offset) {
    return offset / (2 * MAX_COLS);
}

i32 get_offset_col(i32 offset) {
    return (offset - (get_offset_row(offset) * 2 * MAX_COLS)) / 2;
}
