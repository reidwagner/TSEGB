#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "cpu.h"
#include "process.h"

static int rom_size_max = 1000;

bool verbose = false;

void run(struct Process *p) {
    while (step(p) != -1)
        if (verbose)
            dump(p);
}

int main(int argc, char *argv[]) {
    int opt;
    if (argc < 2)
        goto usage_error;
    while ((opt = getopt(argc, argv, "v")) != -1) {
        switch (opt) {
            case 'v': 
                verbose = true; 
                break;
            default:
                goto usage_error;
        }
    }
    char *romfilename = argv[optind];
    struct Process *p = newprocess(rom_size_max);
    if (verbose)
        dump(p);
    FILE *romfp = fopen(romfilename, "r");
    loadmemory(p, romfp);
    if (verbose)
        dump(p);
    run(p);
    return 0;

usage_error:
        fprintf(stderr, "Usage ./tse <romfile>\n");
        exit(1);
}
