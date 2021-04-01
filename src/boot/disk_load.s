; void disk_load(n_sectors DH, dest SD:BX, drive DL)
; load DH sectors
disk_load:
    push dx             ; save this for later error checking
    mov ah, 0x02        ; set up BIOS read
    mov al, dh          ; dh is how many sectors to read
    mov ch, 0x00        ; drive: cylinder 0
    mov dh, 0x00        ; drive: head 0
    mov cl, 0x02        ; drive: start from 2nd sector (1st sector is boot sector)
    int 0x13            ; interrupt into BIOS to read

    jc _disk_load_disk_error ; CF is set by 0x13 BIOS routine on error

    pop dx              ; restore original drive + n_sectors arguments
    ; now verify we read as much as expected
    cmp dh, al          ; AL is sectors read
    jne _disk_load_disk_error_n ; error if read != to_read
    ret

_disk_load_disk_error:
    mov ax, S_DISK_ERROR
    call print_line
    ret

_disk_load_disk_error_n:
    mov ax, S_DISK_ERROR_N
    call print_line
    ret

S_DISK_ERROR db "error: disk read failed", 0
S_DISK_ERROR_N db "error: disk read failed (read != to_read)", 0
