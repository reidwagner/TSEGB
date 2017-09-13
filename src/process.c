#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "process.h"
#include "cpu.h"

struct Process *newprocess(size_t memsize) {
    struct Process *p = malloc(sizeof(struct Process));
    p->cpu = newcpu();
    p->mem = malloc(memsize*sizeof(uint8_t));
    p->memsize = memsize;

    p->r_table[R_B] = &p->cpu->b;
    p->r_table[R_C] = &p->cpu->c;
    p->r_table[R_D] = &p->cpu->d;
    p->r_table[R_E] = &p->cpu->e;
    p->r_table[R_H] = &p->cpu->h;
    p->r_table[R_L] = &p->cpu->l;
    p->r_table[R_HL] = &p->cpu->hl; // Not correct yet
    p->r_table[R_A] = &p->cpu->a;

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

uint8_t nextb(struct Process *p) {
    return p->mem[p->cpu->pc++];
}

uint16_t nexttwob(struct Process *p) {
    uint8_t lo = nextb(p);
    uint8_t hi = nextb(p);
    return (hi << 8) + lo;
}

uint8_t carry(struct Z80CPU *cpu) {
    return cpu->f & 1;
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

void add_n(struct Z80CPU *cpu, uint8_t n) {
    cpu->a += n;
}

void adc_n(struct Z80CPU *cpu, uint8_t n) {
    cpu->a += (n + carry(cpu));
}

void sub_n(struct Z80CPU *cpu, uint8_t n) {
    ; //TODO
}

void sbc_n(struct Z80CPU *cpu, uint8_t n) {
    ; //TODO
}

void and_n(struct Z80CPU *cpu, uint8_t n) {
    cpu->a &= n;
}

void xor_n(struct Z80CPU *cpu, uint8_t n) {
    cpu->a ^= n;
}

void or_n(struct Z80CPU *cpu, uint8_t n) {
    cpu->a |= n;
}

void cp_n(struct Z80CPU *cpu, uint8_t n) {
    ; //TODO
}

int step(struct Process *p) {
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
                    switch (op_y) {
                        default:
                        goto unknown_op;
                    }
                    break;
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                    *(p->r_table[op_y]) = nextb(p);
                    break;
                case 7:
                default:
                    goto unknown_op;
            }
            break;
        case 1:
            if (op_z == 6 && op_y == 6) {
                if (verbose)
                    printf("HALT\n");
                return -1;
            } else {
                ;
            }
        case 2:
            p->alu_table[op_y](p->cpu, *(p->r_table[op_z]));
            break;
        case 3:
            switch (op_z) {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                default:
                    goto unknown_op;
            }
            break;
        default:
            goto unknown_op;
    }
    return 0;
unknown_op:
    fprintf(stderr, "Unknown opcode: %02x\n", op);
    return 0;
}
