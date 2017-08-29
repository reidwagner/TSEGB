#ifndef Z80TSE_CPU_H
#define Z80TSE_CPU_H

#include <stdint.h>
#include <stddef.h>

struct Z80CPU {
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t h;
    uint8_t l;
    uint8_t ap;
    uint8_t bp;
    uint8_t cp;
    uint8_t dp;
    uint8_t ep;
    uint8_t hp;
    uint8_t lp;
    uint16_t ix;
    uint16_t iy;
    uint16_t sp; 
    uint16_t pc; 
    uint8_t i; 
    uint8_t r;
    uint8_t stat;
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
