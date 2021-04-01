#include "screen.h"

void kernel_main(void) {
    terminal_initialize();
    terminal_writestring("What's up!");
    while (true) {
    }
}
