#include "screen.h"
#include "serial.h"

void main() {
    if (!init_serial()) {
        // do nothing
    }
    clear_screen();
    kprint("hello, world!");
    while (1) {
    }
}
