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
}
