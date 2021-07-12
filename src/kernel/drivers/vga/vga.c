#include "vga.h"
#include "kernel/drivers/driver_utils.h"

#define DRV_VGA_PORT_GRAPHICS_MODE DRV_VGA_PORT_3ce

void drv_vga_set_graphics_write_mode() {
    drv_write_as_u8(DRV_VGA_PORT_GRAPHICS_MODE, 5);
    drv_write_as_u8(drv_offset_addr_8(DRV_VGA_PORT_GRAPHICS_MODE, 1), BIT_0);
}

void drv_vga_set_graphics_read_mode() {
    drv_write_as_u8(DRV_VGA_PORT_GRAPHICS_MODE, 5);
    drv_write_as_u8(drv_offset_addr_8(DRV_VGA_PORT_GRAPHICS_MODE, 1), BIT_3);
}
