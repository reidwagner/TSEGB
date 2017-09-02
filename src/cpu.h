#ifndef Z80TSE_CPU_H
#define Z80TSE_CPU_H

#include <stdint.h>
#include <stddef.h>
#define REG_U(hi, lo, full) \
    union { \
        struct { \
            uint8_t hi; \
            uint8_t lo; \
        }; \
        uint16_t full; \
    };

struct Z80CPU {
    REG_U(a, f, af)
    REG_U(b, c, bc)
    REG_U(d, e, de )
    REG_U(h, l, hl )
    REG_U(a_p, f_p, af_p)
    REG_U(b_p, c_p, bc_p)
    REG_U(d_p, e_p, de_p)
    REG_U(h_p, l_p, hl_p)
    uint16_t ix;
    uint16_t iy;
    uint16_t sp; 
    uint16_t pc; 
    uint8_t i; 
    uint8_t r;
};

enum CODES {
    NOP = 0x00,
    LD_A_n = 0x3e,
    LD_B_n = 0x06,
    ADD_A_B = 0x80,
    LD_nloc_A = 0x32,
    HALT = 0x76
};

void registerdump(struct Z80CPU *cpu);

struct Z80CPU *newcpu();

#endif
