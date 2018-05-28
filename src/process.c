#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "process.h"
#include "cpu.h"

bool verbose = false;


/*----                  Setup functions                      ---*/
/*--------------------------------------------------------------*/

struct Process *newprocess(size_t memsize) {
    struct Process *p = malloc(sizeof(struct Process));
    p->cpu = newcpu();
    p->mem = malloc(memsize*sizeof(uint8_t));
    p->cpu->mem = p->mem;
    p->memsize = memsize;
    p->max_iterations = DEFAULT_MAX_ITERATIONS;
    p->iterations = 0;

    return p;
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


/*----                  Debug functions                      ---*/
/*--------------------------------------------------------------*/

void memorydump(struct Process *p) {
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
    printf("---------\n");
    printf("Registers\n");
    registerdump(p->cpu);
    printf("Memory\n");
    memorydump(p);
}

/*----                      Execution                        ---*/
/*--------------------------------------------------------------*/

void run(struct Process *p) {
    while (step(p) != -1)
        if (verbose)
            dump(p);
}

int stepn(struct Process *p, int n) {
    int i, rc;
    for (i = 0; i < n; i++) {
        if ((rc = step(p)) != 0)
            return rc;
    }
    return 0;
}


int step(struct Process *p) {
    if (p->iterations++ >= p->max_iterations)
        return -1;
    execute(p->cpu);
}

