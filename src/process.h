#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "cpu.h"

struct Process {
    struct Z80CPU *cpu;
    uint8_t *mem;
    size_t memsize;
};

struct Process *newprocess(size_t memsize);
void memorydump(struct Process *p);
void dump(struct Process *p);
void loadmemory(struct Process *p, FILE *romfile);
int step(struct Process *p);

#endif
