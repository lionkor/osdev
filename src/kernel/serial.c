#include "serial.h"
#include "ports.h"

i32 init_serial() {
    port_byte_out(PORT + 1, 0x00); // disable interrupts
    port_byte_out(PORT + 3, 0x80); // enable dlab (baud rate divisor)
    port_byte_out(PORT + 0, 0x03); // low byte of divisor
    port_byte_out(PORT + 1, 0x00); // high byte "
    port_byte_out(PORT + 3, 0x03); // 8 bit,s no parity, one stop bit
    port_byte_out(PORT + 2, 0xc7); // FIFO, clear, 14 byte threshold
    port_byte_out(PORT + 4, 0x0b); // IRQs enabled, RTS, DSR set
    port_byte_out(PORT + 4, 0x1e); // loopback mode + test
    // test serial chip
    port_byte_out(PORT + 0, 0xae);
    if (port_byte_in(PORT) != 0xae) {
        return 1;
    }
    port_byte_out(PORT + 4, 0x0f);
    return 0;
}
