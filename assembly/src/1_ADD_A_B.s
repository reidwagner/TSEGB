;;Loads 123 and 61 into A and B
;;Adds A and B, storing in A
;;Writes A to memory location 0xA

.org 0

	ld a,123
    ld b,61
    add a,b
    ld (10),a
    halt