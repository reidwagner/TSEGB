.org 0

    ld b, 7
    ld a, 1
    ld c, 0
loop:
    ld d, a
    add a, c
    ld c, d
    djnz loop

    halt
