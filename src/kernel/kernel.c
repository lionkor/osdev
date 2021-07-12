#include "kprint.h"

#include <binops.h>
#include <ktypes.h>

#include <kernel/drivers/driver_utils.h>
#include <kernel/drivers/serial/serial.h>

void kernel_main(void) {
    drv_serial_init(); // should always be first

    terminal_initialize();
    kplog("welcome to lkOS");
    kpwarning("kernel is heavy WIP");
    kperror("not an error, just testing!");
    kprintf("Hello, %s! %x and here's a percent: %%!\n", "Lion", 0xdeadbeef);
    drv_printf_error("vga", "some shit: %s", "uwu owo!!!\n");
    kpferror("Well, %s, this is kinda awkward! I got: %s, %s!\n", "lion", NULL, "uwu");
    kprintf("Writing to serial!\n");
    kprintf_serial("Hello, Serial!\n");
}
