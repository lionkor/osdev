[org 0x7c00]
mov [BOOT_DRIVE], dl        ; copy boot drive from DL, this was set by BIOS
jmp start ; start

%include "print_hex.s"
%include "disk_load.s"

start:
    mov ax, S_BOOTING_OS
    call print_line 

    mov ax, S_SETTING_UP_STACK
    call print

    mov bp, 0x8000              ; setup stack far away
    mov sp, bp
    
    mov ax, S_OK
    call print_line

    mov ax, S_READING_FROM_DISK
    call print

    mov bx, 0x9000              ; load into 0x0000:0x9000 (ES:BX)
    mov dh, 5                   ; 5 sectors
    mov dl, [BOOT_DRIVE]        ; from the boot disk
    call disk_load

    mov ax, S_OK
    call print_line

    jmp $

S_BOOTING_OS db 'booting lkOS v1.0', 0
S_SETTING_UP_STACK db 'setting up stack... ', 0
S_READING_FROM_DISK db 'reading initial data from disk... ', 0
S_OK db "ok!", 0

; global variables

BOOT_DRIVE db 0

; padding and magic
times 510 - ($ - $$) db 0
dw 0xaa55

; some verifyable data
times 256 dw 0xdada
times 256 dw 0xface
