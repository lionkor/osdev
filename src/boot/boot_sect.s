[org 0x7c00]
jmp start ; start

%include "print_hex.s"

start:
    mov ax, S_BOOTING_OS
    call print_line 
    
    jmp loop_forever

loop_forever:
    jmp $


S_BOOTING_OS:
    db 'Booting lkOS', 0

S_GOODYBE:
    db 'Goodbye', 0

S_CRLF:
    db 0x0a, 0x0d, 0

; padding and magic
times 510 - ($ - $$) db 0
dw 0xaa55
