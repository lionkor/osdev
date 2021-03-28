
print_hex:
    pusha
    ; we first handle the bits & 0xf000
    mov cx, ax
    shr cx, 4 * 3
    and cx, 0x000f
    ; cx is now the offset into S_HEX_CHARMAP
    ; we now get that char from the charmap into DX
    mov bx, cx
    ; bx is offset into charmap
    mov dx, [S_HEX_CHARMAP + bx - 1] ; dx now points to charmap[bx - 1]
    ; now we store that char in cx
    mov cx, dx
    ; we set HEX_OUT[2] to this char
    ; so we load it first
    mov bx, S_HEX_OUT
    ; go to the 2nd index store our found char there
    mov [bx + 2], ch
    ; store bx
    push bx

    ; now we repeat this for the & 0x0f00 nibble
    mov cx, ax
    shr cx, 4 * 2
    and cx, 0x000f
    mov bx, cx
    mov dx, [S_HEX_CHARMAP + bx - 1] ; dx now points to charmap[bx]
    mov cx, dx
    ; pop bx from earlier
    pop bx
    ; go to the 3rd index this time and set it to the char we want
    mov [bx + 3], ch
    ; store bx
    push bx
    
    ; now we repeat this for the & 0x00f0 nibble
    mov cx, ax
    shr cx, 4 * 1
    and cx, 0x000f
    mov bx, cx
    mov dx, [S_HEX_CHARMAP + bx - 1] ; dx now points to charmap[bx]
    mov cx, dx
    ; pop bx from earlier
    pop bx
    ; go to the 4th index this time and set it to the char we want
    mov [bx + 4], ch
    ; store bx
    push bx
    
    ; now we repeat this once more for the & 0x00f0 nibble
    mov cx, ax
    ; no shift right here
    ; shr 4 * 0
    and cx, 0x000f
    mov bx, cx
    mov dx, [S_HEX_CHARMAP + bx - 1] ; dx now points to charmap[bx]
    mov cx, dx
    ; pop bx from earlier
    pop bx
    ; go to the 5th index this time and set it to the char we want
    mov [bx + 5], ch
    ; we also dont push bx, since we're done :)

    mov ax, bx
    call print
    popa
    ret

%include "print.asm"

S_HEX_OUT:
    db '0x0000', 0

S_HEX_CHARMAP:
    db '0123456789abcdef', 0
