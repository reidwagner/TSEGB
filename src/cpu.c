#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"

#define print_reg_col(label, reg) printf("%-5s %6d\n", label, reg);

void registerdump(struct Z80CPU *cpu) {
    printf("%-3s %-3s %-3s %-3s %-3s %-3s %-3s %-3s %-3s",
            "a", "b", "c", "d", "e", "h", "l", "i", "r");
    printf("\n");
    printf("%-3d %-3d %-3d %-3d %-3d %-3d %-3d %-3d %-3d",
            cpu->a, cpu->b, cpu->c, cpu->d, cpu->e, cpu->h, cpu->l, cpu->i, cpu->r);
    printf("\n");
    printf("%-3s %-3s %-3s %-3s %-3s %-3s %-3s %-3s %-3s %-3s %-3s %-3s",
            "ap", "bp", "cp", "dp", "ep", "hp", "lp", "ix", "iy", "sp", "pc", "stat");
    printf("\n");
    printf("%-3d %-3d %-3d %-3d %-3d %-3d %-3d %-3d %-3d %-3d %-3d %-3d",
            cpu->ap, cpu->bp, cpu->cp, cpu->dp, cpu->ep, cpu->hp, cpu->lp, cpu->ix, cpu->iy, cpu->sp, cpu->pc, cpu->stat);
    printf("\n");
}

struct Z80CPU *newcpu() {
    struct Z80CPU *cpu = malloc(sizeof(struct Z80CPU));
    cpu->a = 0;
    cpu->b = 0;
    cpu->c = 0;
    cpu->d = 0;
    cpu->e = 0;
    cpu->h = 0;
    cpu->l = 0;
    cpu->ap = 0;
    cpu->bp = 0;
    cpu->cp = 0;
    cpu->dp = 0;
    cpu->ep = 0;
    cpu->hp = 0;
    cpu->lp = 0;
    cpu->ix = 0;
    cpu->iy = 0;
    cpu->sp = 0; 
    cpu->pc = 0; 
    cpu->i = 0; 
    cpu->r = 0;
    cpu->stat = 0;
    return cpu;
}
