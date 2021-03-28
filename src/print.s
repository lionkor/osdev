
; print(ax) - prints null-terminated string in ax
print:
    pusha           ; push all registers
    mov bx, ax      ; move argument into bx
    mov ah, 0x0e    ; int 10/ah = 0eh -> scrolling teletype BIOS routine
print_start:
    mov al, [bx]    ; load character from address in bx
    cmp al, 0x0     ; if al == 0
    je print_end    ; then we're done. we assume null termination
    int 0x10        ; interrupt
    add bx, 1       ; move to the next char
    jmp print_start ; go to the start
print_end:
    popa            ; pop all registers
    ret             ; return from routine

; print_line(ax) - prints null-terminated string in ax, then prints CRLF
print_line:
    call print      ; print like we usually would
    pusha           ; push all registers
    mov ah, 0x0e    ; int 10/ah = 0eh -> scrolling teletype BIOS routine
    mov al, 0x0A    ; move LF into al
    int 0x10        ; ... and print it
    mov al, 0x0D    ; move CR into al
    int 0x10        ; ... and print it
    popa            ; pop all registers again
    ret             ; return 
