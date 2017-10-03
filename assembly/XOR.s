.org 0

    ld a,1
    ld b,1
    xor b
    ;; a is 0

    ld b,0
    xor b
    ;; a is 0

    ld b,1
    xor b
    ;; a is 1

    ld b,0
    xor b
    ;; a is 1

    halt
