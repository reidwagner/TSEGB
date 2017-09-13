.org 0

    ld a,1
    ld b,1
    and b
    ;; a is 1

    ld b,0
    and b
    ;; a is 0

    ld b,1
    and b
    ;; a is 0

    ld b,0
    and b
    ;; a is 0

    halt
