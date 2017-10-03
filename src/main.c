#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "cpu.h"
#include "process.h"

int main(int argc, char *argv[]) {
    int opt;
    int max_iterations = 0;
    if (argc < 2)
        goto usage_error;
    while ((opt = getopt(argc, argv, "vi:")) != -1) {
        switch (opt) {
            case 'v': 
                verbose = true; 
                break;
            case 'i':
                max_iterations = atoi(optarg);
                break;
            default:
                goto usage_error;
        }
    }
    char *romfilename = argv[optind];
    struct Process *p = newprocess(DEFAULT_MAX_MEMSIZE);
    if (max_iterations)
        p->max_iterations = max_iterations;
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
