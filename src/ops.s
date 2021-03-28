; common operations

; shift_arbitrary(out ax : what, const bx : amount)
; shifts ax by bx
shift_arbitrary:
    push cx
    xor cx, cx
shift_arbitrary_for_start:
    shr ax, 1
    add cx, 1
    cmp cx, bx
    je shift_arbitrary_for_start
    pop cx
    ret
