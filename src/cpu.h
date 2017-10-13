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

#define REG_U_BITFIELD(hi, lo, full) \
    union { \
        struct { \
            uint8_t hi; \
            union { \
                struct { \
                    uint8_t lo ## _C : 1; \
                    uint8_t lo ## _N : 1; \
                    uint8_t lo ## _PV : 1; \
                    uint8_t lo ## _F3 : 1; \
                    uint8_t lo ## _H : 1; \
                    uint8_t lo ## _F5 : 1; \
                    uint8_t lo ## _Z : 1; \
                    uint8_t lo ## _S : 1; \
                } ; \
                uint8_t lo; \
            }; \
        }; \
        uint16_t full; \
    };

struct Z80CPU {
    REG_U_BITFIELD(a, f, af)
    REG_U(b, c, bc)
    REG_U(d, e, de )
    REG_U(h, l, hl )
    REG_U_BITFIELD(a_p, f_p, af_p)
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

void registerdump(struct Z80CPU *cpu);

struct Z80CPU *newcpu();

void add_n(struct Z80CPU *cpu, uint8_t a);
void adc_n(struct Z80CPU *cpu, uint8_t a);
void sub_n(struct Z80CPU *cpu, uint8_t a);
void sbc_n(struct Z80CPU *cpu, uint8_t a);
void and_n(struct Z80CPU *cpu, uint8_t a);
void xor_n(struct Z80CPU *cpu, uint8_t a);
void or_n(struct Z80CPU *cpu, uint8_t a);
void cp_n(struct Z80CPU *cpu, uint8_t a);
void set_zero_flag(struct Z80CPU *cpu);
uint8_t check_condition_z(struct Z80CPU *cpu);
uint8_t check_condition_nz(struct Z80CPU *cpu);

#endif
