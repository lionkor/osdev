#include "kprint.h"

#include <ktypes.h>

void kernel_main(void) {
    terminal_initialize();
    kplog("welcome to lkOS");
    kpwarning("kernel is heavy WIP");
    kperror("not an error, just testing!");
    kprint_hex_8(0x12);
    kprint("\n");
    kprint_hex_8(0x21);
    kprint("\n");
    kprint_hex_32(0xdada1010);
    kprint("\n");
    for (size_t i = 0; i < 5000; ++i) {
    }
}
