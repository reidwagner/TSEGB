#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"

#define print_reg_col(label, reg) printf("%-5s %6d\n", label, reg);

void registerdump(struct Z80CPU *cpu) {
    printf("%-5s %6s\n", "reg", "value");
    print_reg_col("a", cpu->a);
    print_reg_col("b", cpu->b);
    print_reg_col("c", cpu->c);
    print_reg_col("d", cpu->d);
    print_reg_col("e", cpu->e);
    print_reg_col("h", cpu->h);
    print_reg_col("l", cpu->l);
    print_reg_col("ap", cpu->ap);
    print_reg_col("bp", cpu->bp);
    print_reg_col("cp", cpu->cp);
    print_reg_col("dp", cpu->dp);
    print_reg_col("ep", cpu->ep);
    print_reg_col("hp", cpu->hp);
    print_reg_col("lp", cpu->lp);
    print_reg_col("ix", cpu->ix);
    print_reg_col("iy", cpu->iy);
    print_reg_col("sp", cpu->sp);
    print_reg_col("pc", cpu->pc);
    print_reg_col("i", cpu->i);
    print_reg_col("r", cpu->r);
    print_reg_col("stat", cpu->stat);
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
