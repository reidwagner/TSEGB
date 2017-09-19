#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"

#define print_reg_col(label, reg) printf("%-5s %6d\n", label, reg);

void registerdump(struct Z80CPU *cpu) {
    printf("%-3s %-3s %-3s %-3s %-3s %-3s %-3s %-3s %-3s %-3s",
            "a", "f", "b", "c", "d", "e", "h", "l", "i", "r");
    printf("\n");
    printf("%-3d %-3d %-3d %-3d %-3d %-3d %-3d %-3d %-3d %-3d",
            cpu->a, cpu->f, cpu->b, cpu->c, cpu->d, cpu->e, cpu->h, cpu->l, cpu->i, cpu->r);
    printf("\n");
    printf("%-3s %-3s %-3s %-3s %-3s %-3s %-3s %-3s %-3s %-3s %-3s",
            "ap", "bp", "cp", "dp", "ep", "hp", "lp", "ix", "iy", "sp", "pc");
    printf("\n");
    printf("%-3d %-3d %-3d %-3d %-3d %-3d %-3d %-3d %-3d %-3d %-3d",
            cpu->a_p, cpu->b_p, cpu->c_p, cpu->d_p, cpu->e_p, cpu->h_p, cpu->l_p, cpu->ix, cpu->iy, cpu->sp, cpu->pc);
    printf("\n");
    printf("%-3s %-3s %-3s %-3s %-3s %-3s %-3s %-3s",
            "S", "Z", "F5", "H", "F3", "PV", "N", "C");
    printf("\n");
    printf("%-3d %-3d %-3d %-3d %-3d %-3d %-3d %-3d",
            cpu->f_S, cpu->f_Z, cpu->f_F5, cpu->f_H, cpu->f_F3, cpu->f_PV, cpu->f_N, cpu->f_C);
    printf("\n");
}

struct Z80CPU *newcpu() {
    struct Z80CPU *cpu = malloc(sizeof(struct Z80CPU));
    cpu->a = 0;
    cpu->f = 0;
    cpu->b = 0;
    cpu->c = 0;
    cpu->d = 0;
    cpu->e = 0;
    cpu->h = 0;
    cpu->l = 0;
    cpu->a_p = 0;
    cpu->b_p = 0;
    cpu->c_p = 0;
    cpu->d_p = 0;
    cpu->e_p = 0;
    cpu->h_p = 0;
    cpu->l_p = 0;
    cpu->ix = 0;
    cpu->iy = 0;
    cpu->sp = 0; 
    cpu->pc = 0; 
    cpu->i = 0; 
    cpu->r = 0;

    cpu->f_Z = 1;

    return cpu;
}
