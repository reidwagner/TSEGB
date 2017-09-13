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

struct Process {
    struct Z80CPU *cpu;
    uint8_t *mem;
    size_t memsize;
    uint8_t *r_table[8];
};

struct Process *newprocess(size_t memsize);
void memorydump(struct Process *p);
void dump(struct Process *p);
void loadmemory(struct Process *p, FILE *romfile);
int step(struct Process *p);

extern bool verbose;

#endif
