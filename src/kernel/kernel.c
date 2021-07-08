#include "kprint.h"

#include <binops.h>
#include <ktypes.h>

#include "!

void kernel_main(void) {
    terminal_initialize();
    kplog("welcome to lkOS");
    kpwarning("kernel is heavy WIP");
    kperror("not an error, just testing!");
    kprintf("Hello, %s! %x and here's a percent: %%!\n", "Lion", 0xdeadbeef);
    kpferror("Well, %s, this is kinda awkward! I got: %s, %s!\n", "lion", NULL, "uwu");
}
