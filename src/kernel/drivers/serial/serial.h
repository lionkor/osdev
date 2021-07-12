#pragma once

#include "kernel/drivers/driver_utils.h"
#include <ktypes.h>

// mostly adopted from
// https://wiki.osdev.org/Serial_Ports

i32 drv_serial_init(void);
char drv_serial_read(void);
void drv_serial_write(char a);
