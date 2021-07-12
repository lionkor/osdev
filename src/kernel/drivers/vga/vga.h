#pragma once

#include <ktypes.h>

// these defines exist to make sure we never
// read or write from/to a port that is totally wrong
#define DRV_VGA_PORT_3c0 0x3c0
#define DRV_VGA_PORT_3c2 0x3c2
#define DRV_VGA_PORT_3c4 0x3c4
#define DRV_VGA_PORT_3c6 0x3c6
#define DRV_VGA_PORT_3c7 0x3c7
#define DRV_VGA_PORT_3c8 0x3c8
#define DRV_VGA_PORT_3c9 0x3c9
#define DRV_VGA_PORT_3cc 0x3cc
#define DRV_VGA_PORT_3ce 0x3ce
#define DRV_VGA_PORT_3d4 0x3d4

void drv_vga_set_graphics_write_mode(void);
void drv_vga_set_graphics_read_mode(void);
