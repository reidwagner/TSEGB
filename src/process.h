#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "cpu.h"

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

struct Process {
    struct Z80CPU *cpu;
    uint8_t *mem;
    size_t memsize;
    uint8_t *r_table[8];
    uint8_t (*cc_table[8]) (struct Z80CPU*);
    void (*alu_table[8]) (struct Z80CPU*, uint8_t);
};

struct Process *newprocess(size_t memsize);
void memorydump(struct Process *p);
void dump(struct Process *p);
void loadmemory(struct Process *p, FILE *romfile);
int step(struct Process *p);

extern bool verbose;

#endif
