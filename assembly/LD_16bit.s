.org 0

    ld bc,1
    ld de,2
    ld hl,3
    ld sp,4

    add hl,bc
    add hl,de
    add hl,hl
    add hl,sp
    ;; hl is 16

    halt
