#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "cpu.h"
#include "process.h"
#include "fib.h"
#include "video.h"

int main(int argc, char *argv[]) {
    int opt;
    int max_iterations = 0;
    uint16_t entry = 0x100;
    if (argc < 2)
        goto usage_error;
    while ((opt = getopt(argc, argv, "vsi:e:")) != -1) {
        switch (opt) {
            case 'v': 
                verbose = true; 
                break;
            case 'i':
                max_iterations = atoi(optarg);
                break;
            case 'e':
                entry = strtol(optarg, NULL, 16);
                break;
            default:
                goto usage_error;
        }
    }
    char *romfilename = argv[optind];
    struct Process *p = newprocess();
    if (max_iterations)
        p->max_iterations = max_iterations;
    if (entry)
        p->entry = entry;
    if (verbose)
        dump(p);
    FILE *romfp = fopen(romfilename, "r");
    loadmemory(p, romfp);
    run(p);
    return 0;

usage_error:
        fprintf(stderr, "Usage ./tse <romfile>\n");
        exit(1);
}

void tse_memcpy(uint8_t *target, uint8_t *source, size_t len ) {
    for (size_t i = 0; i < len; i++) {
        target[i] = source[i];
    }
}

void main_wasm(void) {
    volatile uint8_t *foo = malloc(4);
    foo[2] = 0x12;

    struct Z80CPU cpu;
    struct Z80CPU_REG r;
    uint8_t mem[MEM_MAP_SIZE];
    struct Process process;

    initcpu(&cpu, &r);
    initprocess(&process, &cpu, mem);
    process.max_iterations = 50;

    tse_memcpy(process.mem, assembly_FIB_rom, assembly_FIB_rom_len); // len is getting corrupted somehow.

    run(&process);
}
