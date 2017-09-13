#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "cpu.h"

#define R_B 0
#define R_C 1
#define R_D 2
#define R_E 3
#define R_H 4
#define R_L 5
#define R_HL 6
#define R_A 7

#define ALU_ADD 0
#define ALU_ACD 1
#define ALU_SUB 2
#define ALU_SBC 3
#define ALU_AND 4
#define ALU_XOR 5
#define ALU_OR 6
#define ALU_CP 7

struct Process {
    struct Z80CPU *cpu;
    uint8_t *mem;
    size_t memsize;
    uint8_t *r_table[8];
    void (*alu_table[8]) (struct Z80CPU*, uint8_t);
};

struct Process *newprocess(size_t memsize);
void memorydump(struct Process *p);
void dump(struct Process *p);
void loadmemory(struct Process *p, FILE *romfile);
int step(struct Process *p);
void add_A_n(struct Z80CPU *cpu, uint8_t n);

extern bool verbose;

#endif
