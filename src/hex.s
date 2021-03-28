[org 0x7c00]
jmp start ; start


start:
    mov ax, S_BOOTING_OS
    call print_line 
    
    ; print a hex string
    mov ax, 0xabcd
    call print_hex

    ; crlf
    mov ax, S_CRLF
    call print
    
    ; print a hex string
    mov ax, 0x0123
    call print_hex

    ; crlf
    mov ax, S_CRLF
    call print

    ; print a hex string
    mov ax, 0xff00
    call print_hex

    ; crlf
    mov ax, S_CRLF
    call print

    mov ax, S_GOODYBE
    call print_line

    jmp loop_forever

loop_forever:
    jmp $

%include "print_hex.asm"


S_BOOTING_OS:
    db 'Booting OS', 0

S_GOODYBE:
    db 'Goodbye', 0

S_CRLF:
    db 0x0a, 0x0d, 0

; padding a magic
times 510 - ($ - $$) db 0
dw 0xaa55
