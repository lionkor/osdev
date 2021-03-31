[org 0x7c00]
KERNEL_OFFSET equ 0x1000

    mov [BOOT_DRIVE], dl

    mov bp, 0x9000              ; setup stack far away
    mov sp, bp

    mov ax, S_BOOTING_OS
    call print_line

    mov ax, S_SWITCHING_TO_PM
    call print_line

    call load_kernel

    call switch_to_pm ; noreturn
    jmp $

; global variables

BOOT_DRIVE db 0

%include "disk_load.s"
%include "print.s"
%include "switch_to_pm.s"
%include "print_pm.s"

[bits 16]
load_kernel:
    mov ax, S_LOAD_KERNEL
    call print
                            ; load from disk:
    mov bx, KERNEL_OFFSET   ; to kernel_offset
    mov dh, 15              ; 15 sectors (boot sector is skipped by routine)
    mov dl, [BOOT_DRIVE]    ; from this drive
    call disk_load

    mov ax, S_OK
    call print_line

    ret

[bits 32]

BEGIN_PM: ; called once we're in protected mode!
    mov edx, S_OK
    call print_line_pm

    call KERNEL_OFFSET


S_BOOTING_OS db 'lkOS v1.0', 0
S_SETTING_UP_STACK db 'setting up stack... ', 0
S_SWITCHING_TO_PM db 'switching to 32-bit protected mode... ', 0
S_LOAD_KERNEL db 'loading kernel... ', 0
S_OK db "ok!", 0

; padding and magic
times 510 - ($ - $$) db 0
dw 0xaa55

times 1024 dw 0xface
