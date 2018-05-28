#ifndef Z80TSE_CPU_H
#define Z80TSE_CPU_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

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

enum {
    R_B,
    R_C,
    R_D,
    R_E,
    R_H,
    R_L,
    R_HL,
    R_A
};

enum {
    RP_BC,
    RP_DE,
    RP_HL,
    RP_SP
};

enum {
    RP2_BC,
    RP2_DE,
    RP2_HL,
    RP2_AF
};

enum {
    ALU_ADD,
    ALU_ADC,
    ALU_SUB,
    ALU_SBC,
    ALU_AND,
    ALU_XOR,
    ALU_OR,
    ALU_CP
};

enum {
    CC_NZ,
    CC_Z,
    CC_NC,
    CC_C,
    CC_PO,
    CC_PE,
    CC_P,
    CC_M
};

struct Z80CPU_REG {
    REG_U_BITFIELD(a, f, af)
    REG_U(c, b, bc)
    REG_U(e, d, de )
    REG_U(l, h, hl )
    REG_U_BITFIELD(a_p, f_p, af_p)
    REG_U(c_p, b_p, bc_p)
    REG_U(e_p, d_p, de_p)
    REG_U(l_p, h_p, hl_p)
    uint16_t ix;
    uint16_t iy;
    uint16_t sp;
    uint16_t pc;
    uint8_t i;
    uint8_t r;
};

struct Z80CPU {
    struct Z80CPU_REG *r;
    uint8_t *mem;
    uint8_t *r_table[8];
    uint16_t *rp_table[8];
    uint16_t *rp2_table[8];
    uint8_t (*cc_table[8]) (struct Z80CPU*);
    void (*alu_table[8]) (struct Z80CPU*, uint8_t);
};

void registerdump(struct Z80CPU *cpu);

struct Z80CPU *newcpu();

int execute(struct Z80CPU *cpu);

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

extern bool verbose;

#endif
