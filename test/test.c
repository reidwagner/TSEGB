#include <stdio.h>
#include <stdlib.h>
#include "../src/cpu.h"
#include "../src/process.h"
#include "unity/unity.h"

struct Process *create_process(char *binary_file_path) {
    struct Process *p = newprocess(DEFAULT_MAX_MEMSIZE);
    FILE *binary_fp = fopen(binary_file_path, "r");
    if (binary_fp == NULL) {
        perror("Problem loading binary file");
        exit(1);
    }
    loadmemory(p, binary_fp);
    return p;
}

struct Process *run_process(char *binary_file_path) {
    struct Process *p = create_process(binary_file_path);
    run(p);
    return p;
}

void test_ld() {
    struct Process *p = run_process("assembly/LD.bin");
    TEST_ASSERT_EQUAL_INT(1, p->cpu->a);
    TEST_ASSERT_EQUAL_INT(2, p->cpu->b);
    TEST_ASSERT_EQUAL_INT(3, p->cpu->c);
    TEST_ASSERT_EQUAL_INT(4, p->cpu->d);
    TEST_ASSERT_EQUAL_INT(5, p->cpu->e);
    TEST_ASSERT_EQUAL_INT(6, p->cpu->h);
    TEST_ASSERT_EQUAL_INT(7, p->cpu->l);
    free(p);
}

void test_add() {
    struct Process *p = run_process("assembly/ADD.bin");
    TEST_ASSERT_EQUAL_INT(28, p->cpu->a);
    free(p);
}

void test_and() {
    struct Process *p = create_process("assembly/AND.bin");
    int i,j;

    /*
      1 & 1 -> 1
    */
    for (i = 0; i < 3; i++)
        step(p);
    TEST_ASSERT_EQUAL_INT(1, p->cpu->a);

    /*
      1 & 0 -> 0
      0 & 1 -> 0
      0 & 0 -> 0
    */
    for (j = 0; j < 3; j++) {
        for (i = 0; i < 2; i++)
            step(p);
        TEST_ASSERT_EQUAL_INT(0, p->cpu->a);
    }

    free(p);
}

void test_or() {
    struct Process *p = create_process("assembly/OR.bin");
    int i,j;

    /*
      0 | 0 -> 0
    */
    for (i = 0; i < 3; i++)
        step(p);
    TEST_ASSERT_EQUAL_INT(0, p->cpu->a);

    /*
      0 | 1 -> 1
      1 | 0 -> 1
      1 | 1 -> 1
    */
    for (j = 0; j < 3; j++) {
        for (i = 0; i < 2; i++)
            step(p);
        TEST_ASSERT_EQUAL_INT(1, p->cpu->a);
    }

    free(p);
}

void test_xor() {
    struct Process *p = create_process("assembly/XOR.bin");
    int i,j;

    /*
      1 ^ 1 -> 0
    */
    for (i = 0; i < 3; i++)
        step(p);
    TEST_ASSERT_EQUAL_INT(0, p->cpu->a);

    /*
      0 | 0 -> 0
    */
    for (i = 0; i < 2; i++)
        step(p);
    TEST_ASSERT_EQUAL_INT(0, p->cpu->a);

    /*
      0 | 1 -> 1
    */
    for (i = 0; i < 2; i++)
        step(p);
    TEST_ASSERT_EQUAL_INT(1, p->cpu->a);

    /*
      1 | 0 -> 1
    */
    for (i = 0; i < 2; i++)
        step(p);
    TEST_ASSERT_EQUAL_INT(1, p->cpu->a);

    free(p);
}

int main(void) {
    UnityBegin("test/test.c");

    RUN_TEST(test_ld);
    RUN_TEST(test_add);
    RUN_TEST(test_and);
    RUN_TEST(test_or);
    RUN_TEST(test_xor);

    UnityEnd();
    return 0;
}

