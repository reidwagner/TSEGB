#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "cpu.h"
#include "process.h"
#include "fib.h"

extern void printPixel(int x, int y);

int squarer(int num) {
    return num * num;
}

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
    struct Process *p = newprocess(MEM_MAP_SIZE + 1);
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

int main_wasm(int arg) {
    volatile uint8_t *foo = malloc(4);
    foo[2] = 0x12;

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            printPixel(i,j);
        }
    }

    return (int)foo[2];
}
