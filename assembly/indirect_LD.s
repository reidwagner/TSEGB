.org 0

    ld a,0xa
    ld l,0xb
    ld c,0x50
    ld e,0x60

    ld (bc),a
    ld (de),a
    ld (0x70),a
    ld (0x80),hl

    ld a,0
    ld a,(bc)
    ld a,0
    ld a,(de)
    ld a,0
    ld a,(0x70)
    ld l,0
    ld hl,(0x80)

    halt

.org 0x100
