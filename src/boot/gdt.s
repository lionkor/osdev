; GDT
gdt_start:
gdt_null:               ; mandatory null descriptor
    dd 0x0              ; dd -> 4 bytes
    dd 0x0 
gdt_code:               ; code segment descriptor
    ; base = 0x0, limit = 0xf'ff'ff
    ; 1st flags: 1001b
    ;       present:        1
    ;       priviledge:     00
    ;       desc type:      1
    ; type flags: 1010b
    ;       code:           1
    ;       conforming:     0
    ;       readable:       1 <- TODO is this not "writable"?
    ;       accessed:       0
    ; 2nd flags: 1100b
    ;       granularity:    1
    ;       32-bit:         1
    ;       64-bit segment: 0
    ;       AVL:            0
    dw 0xffff       ; limit 0-15
    dw 0x0          ; base 0-15
    db 0x0          ; base 16-23
    db 10011010b    ; 1st flags, type flags
    db 11001111b    ; 2nd flags, limit 16-19
    db 0x0          ; base 24-31
gdt_data:               ; data segment descriptor
    dw 0xffff       ; limit 0-15
    dw 0x0          ; base 0-15
    db 0x0          ; base 16-23
    db 10010010b    ; 1st flags, type flags
    db 11001111b    ; 2nd flags, limit 16-19
    db 0x0          ; base 24-31
gdt_end:                ; end label so we can calulate the size

gdt_descriptor:
    dw gdt_end - gdt_start - 1  ; size of GDT, less than one (TODO: Why?)
    dd gdt_start                ; start address

; Define some handy constants for the GDT segment descriptor offsets , which
; are what segment registers must contain when in protected mode. For example ,
; when we set DS = 0 x10 in PM , the CPU knows that we mean it to use the
; segment described at offset 0 x10 ( i.e. 16 bytes ) in our GDT , which in our
; case is the DATA segment (0 x0 -> NULL ; 0 x08 -> CODE ; 0 x10 -> DATA )
; (from os-dev.pdf)
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start 
