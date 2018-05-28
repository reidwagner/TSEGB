#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "cpu.h"

struct Process {
    struct Z80CPU *cpu;
    uint8_t *mem;
    size_t memsize;
    int iterations;
    int max_iterations;
};

struct Process *newprocess(size_t memsize);
void run(struct Process *p);
void memorydump(struct Process *p);
void dump(struct Process *p);
void loadmemory(struct Process *p, FILE *romfile);
int step(struct Process *p);
int stepn(struct Process *p, int n);

#define DEFAULT_MAX_MEMSIZE 1000
#define DEFAULT_MAX_ITERATIONS 10000

#endif
