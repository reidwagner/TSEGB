#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "process.h"
#include "cpu.h"

bool verbose = false;

struct Process *newprocess(size_t memsize) {
    struct Process *p = malloc(sizeof(struct Process));
    p->cpu = newcpu();
    p->mem = malloc(memsize*sizeof(uint8_t));
    p->memsize = memsize;
    p->max_iterations = DEFAULT_MAX_ITERATIONS;
    p->iterations = 0;

    p->r_table[R_B] = &p->cpu->b;
    p->r_table[R_C] = &p->cpu->c;
    p->r_table[R_D] = &p->cpu->d;
    p->r_table[R_E] = &p->cpu->e;
    p->r_table[R_H] = &p->cpu->h;
    p->r_table[R_L] = &p->cpu->l;
    p->r_table[R_HL] = NULL; // Best way to handle? Nothing goes here.
    p->r_table[R_A] = &p->cpu->a;

    p->cc_table[CC_Z] = &check_condition_z;
    p->cc_table[CC_NZ] = &check_condition_nz;

    p->alu_table[ALU_ADD] = &add_n;
    p->alu_table[ALU_ADC] = &adc_n;
    p->alu_table[ALU_SUB] = &sub_n;
    p->alu_table[ALU_SBC] = &sbc_n;
    p->alu_table[ALU_AND] = &and_n;
    p->alu_table[ALU_XOR] = &xor_n;
    p->alu_table[ALU_OR] = &or_n;
    p->alu_table[ALU_CP] = &cp_n;

    return p;
}

void run(struct Process *p) {
    while (step(p) != -1)
        if (verbose)
            dump(p);
}


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
/* Think about making these inlines or macros. */
uint8_t currb(struct Process *p) {
    return p->mem[p->cpu->pc];
}

uint8_t nextb(struct Process *p) {
    return p->mem[p->cpu->pc++];
}

uint16_t nexttwob(struct Process *p) {
    uint8_t lo = nextb(p);
    uint8_t hi = nextb(p);
    return (hi << 8) + lo;
}

void report_unknown(struct Process *p) {
    fprintf(stderr, "Unknown opcode: %02x\n", currb(p));
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

int stepn(struct Process *p, int n) {
    int i, rc;
    for (i = 0; i < n; i++) {
        if ((rc = step(p)) != 0)
            return rc;
    }
    return 0;
}

/* Also contains some assorted other ops, like NOP */
void relative_jump(struct Process *p, uint8_t op_y) {
    switch (op_y) {
    case 0:
        break;
    default:
        report_unknown(p);
    }
}

void byte_load_immediate(struct Process *p, uint8_t op_y) {
    if (op_y == 6)
        *((p->cpu->h << 8) + p->cpu->l + p->mem) = nextb(p);
    else
        *(p->r_table[op_y]) = nextb(p);
}

void alu_r_operation(struct Process *p, uint8_t op_y, uint8_t op_z) {
    p->alu_table[op_y](p->cpu, *(p->r_table[op_z]));
}

void conditional_jump(struct Process *p, uint8_t op_y) {
    uint8_t cc = p->cc_table[op_y](p->cpu);
    if (cc)
        p->cpu->pc = nexttwob(p);
}

/* Needs better name */
void misc_operation(struct Process *p, uint8_t op_y) {
    switch (op_y) {
    case 0:
        p->cpu->pc = nexttwob(p);
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        report_unknown(p);
    }
} 

int step(struct Process *p) {

    if (p->iterations++ >= p->max_iterations)
        return -1;

    uint8_t op = nextb(p);
    struct Z80CPU *cpu = p->cpu;

    uint8_t op_x = op >> 6;
    uint8_t op_y = (op >> 3) % 8;
    uint8_t op_z = op % 8;
    uint8_t op_p = op_y >> 1;
    uint8_t op_q = op_y % 2;

    if (verbose)
        printf("Opcode: %02x x: %d y: %d z: %d p %d q %d\n", op, op_x, op_y, op_z, op_p, op_q);

    switch (op_x) {
        case 0:
            switch (op_z) {
                case 0:
                    relative_jump(p, op_y);
                    break;
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                    byte_load_immediate(p, op_y);
                    break;
                case 7:
                default:
                    report_unknown(p);
            }
            break;
        case 1:
            if (op_z == 6 && op_y == 6) {
                if (verbose)
                    printf("HALT\n");
                return -1;
            } else {
                ; //8-bit loading
            }
        case 2:
            alu_r_operation(p, op_y, op_z);
            break;
        case 3:
            switch (op_z) {
                case 0:
                case 1:
                case 2:
                    conditional_jump(p, op_y);
                    break;
                case 3:
                    misc_operation(p, op_y);
                    break;
                case 4:
                case 5:
                case 6:
                case 7:
                default:
                    report_unknown(p);
            }
            break;
        default:
            report_unknown(p);
    }
    set_zero_flag(cpu);
    return 0;
