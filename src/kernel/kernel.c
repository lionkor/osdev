#include "kprint.h"

#include <ktypes.h>
#include <binops.h>

void kernel_main(void) {
    terminal_initialize();
    kplog("welcome to lkOS");
    kpwarning("kernel is heavy WIP");
    kperror("not an error, just testing!");
    kprint_hex_16(0xdead);
    kprint("\n");
    kprint_hex_32(0xdada1010);
    kprint("\n");
    kprint_hex_8(0x69);
    kprint("\n");
    char buf[20];
    u32_to_dec(12345, buf);
    kprint(buf);
    kprint("\n");

    kprintf("Hello, World! %x and here's a percent: %%!\n", 0xdeadbeef);
}
