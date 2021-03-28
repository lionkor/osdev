[bits 32]

VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

; void print_pm(char* msg EDX)
print_pm:
    pusha
    mov edx, VIDEO_MEMORY

_print_pm_loop:
    mov al, [ebx]
    mov ah, WHITE_ON_BLACK

    cmp al, 0           ; *msg == 0
    je _print_pm_done

    mov [edx], ax

    add ebx, 1          ; ++msg
    add edx, 2          ; advance in video memory

    jmp _print_pm_loop

_print_pm_done:
    popa
    ret

print_line_pm:
    call print_pm
    mov edx, S_NEWLINE
    call print_pm
    ret

S_NEWLINE db "\n\r", 0
