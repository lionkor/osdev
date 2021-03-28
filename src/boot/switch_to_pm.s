; switch to protected mode

%include "gdt.s"

switch_to_pm:
    cli                         ; clear & disable interrupts for now
    lgdt [gdt_descriptor]
    mov eax, cr0                ; start switching by setting first bit of control register CR0
    or eax, 0x1
    mov cr0, eax

    jmp CODE_SEG:init_pm

[bits 32]
; initailize stack and registers once in protected mode
init_pm:
    ; old segments are meaningless, so we point our segment registers
    ; so we point our segment registers to the data selector from the GDT
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x9'00'00      ; set stack to top of free space
    mov esp, ebp

    call BEGIN_PM ; protected mode, here we go!
