[bits 32]

section .text
_start:
    extern kernel_main
    call kernel_main
    cli
hang: hlt
jmp hang

