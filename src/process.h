#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "cpu.h"

#define MEM_ROM_BANK_0        0x0000
#define MEM_ROM_BANK_SWITCH   0x4000
#define MEM_ROM_VIDEO         0x8000
#define MEM_RAM_BANK_SWITCH   0xA000
#define MEM_RAM_INTERNAL_1    0xC000
#define MEM_RAM_INTERNAL_ECHO 0xE000
#define MEM_SPRITE_ATTR       0xFE00
#define MEM_MISC_EMPTY_1      0xFEA0
#define MEM_IO_PORTS          0xFF00
#define MEM_MISC_EMPTY_2      0xFF4C
#define MEM_RAM_INTERNAL_2    0xFF4C
#define MEM_EI_REG            0xFFFF

#define MEM_MAP_SIZE          0xFFFF
#define DEFAULT_MAX_ITERATIONS 1000000

struct Process {
    struct Z80CPU *cpu;
    uint8_t *mem;
    size_t memsize;
    uint16_t entry;
    int iterations;
    int max_iterations;
};

struct Process *newprocess(void);
void initprocess(struct Process *p, struct Z80CPU *cpu, uint8_t *mem);
void run(struct Process *p);
void memorydump(struct Process *p);
void dump(struct Process *p);
void loadmemory(struct Process *p, FILE *romfile);
int step(struct Process *p);
int stepn(struct Process *p, int n);


#endif
