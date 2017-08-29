#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "cpu.h"

struct Process *newprocess(size_t memsize) {
    struct Process *p = malloc(sizeof(struct Process));
    p->cpu = newcpu();
    p->mem = malloc(memsize*sizeof(uint8_t));
    p->memsize = memsize;
    return p;
}

void memorydump(struct Process *p) {
    printf("Memory dump:\n");

    size_t i;
    size_t last_nonzero_index = 0;
    for (i = 0; i < p->memsize; i++)
        if (p->mem[i])
            last_nonzero_index = i;
    if (last_nonzero_index < p->memsize)
        last_nonzero_index++;  //print one zero after the last non-zero if we can
    for (i = 0; i <= last_nonzero_index; i++)
        printf("%02x ", p->mem[i]);

    printf("...\n");
}

void dump(struct Process *p) {
    registerdump(p->cpu);
    memorydump(p);
}

uint8_t nextb(struct Process *p) {
    return p->mem[p->cpu->pc++];
}

uint16_t nexttwob(struct Process *p) {
    uint8_t lo = nextb(p);
    uint8_t hi = nextb(p);
    return (hi << 8) + lo;
}

void loadmemory(struct Process *p, FILE *romfp) {
    fseek(romfp, 0, SEEK_END);
    if (p->memsize < ftell(romfp)) {
        fprintf(stderr, "ROM size larger than available memory.");
        exit(1);
    }
    rewind(romfp);          

    fread(p->mem, sizeof(uint8_t), p->memsize, romfp);
}

int step(struct Process *p) {
    uint8_t op = nextb(p);
    struct Z80CPU *cpu = p->cpu;
    switch (op) {
        case NOP:
            break;
        case LD_A_n:
            cpu->a = nextb(p);
            break;
        case LD_B_n:
            cpu->b = nextb(p);
            break;
        case ADD_A_B:
            cpu->a += cpu->b;
            break;
        case LD_nloc_A:
            p->mem[(size_t) nexttwob(p)] = cpu->a;
            break;
        case HALT:
            printf("HALT\n");
            return -1;
        default:
            printf("Undefined code\n");
    }
    return 0;
}
