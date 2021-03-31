#pragma once

#include "../types.h"

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f
#define RED_ON_WHITE 0xf4
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

void clear_screen();
// specify negative values for col, row to auto-calculate them
void kprint_at(char* msg, i32 col, i32 row);
// equivalent to kprint_at(msg, -1, -1)
void kprint(char* msg);
