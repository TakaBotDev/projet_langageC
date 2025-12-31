#include "tests.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


//je me suis aidé de l'IA pour générer le fichier tests.c


struct __test_section {
    const char* name;
};

struct __test_case {
    struct __test_section* section;
    jmp_buf env;
    const char* name;
    int id;
    test_result result;
};

jmp_buf* get_env(struct __test_case* testcase) {
    return &testcase->env;
}

struct __test_section* init_section(const char* name) {
    struct __test_section* sec = malloc(sizeof(struct __test_section));
    sec->name = name;
    printf("\n--- Section %s ---\n", name);
    return sec;
}

void cleanup_section(struct __test_section* section) {
    free(section);
}

struct __test_case* init_test(struct __test_section* section, const char* file, int line, int id, const char* name) {
    struct __test_case* t = malloc(sizeof(struct __test_case));
    t->section = section;
    t->name = name;
    t->id = id;
    t->result = UNKNOWN;
    return t;
}

void fail(struct __test_case* testcase, const char* file, int line, const char* cause) {
    printf("FAILED [%s:%d] %s\n", file, line, cause);
    longjmp(*(get_env(testcase)), FAILURE);
}

void failf(struct __test_case* testcase, const char* file, int line, const char* format, ...) {
    va_list args;
    va_start(args, format);
    printf("FAILED [%s:%d] ", file, line);
    vprintf(format, args);
    printf("\n");
    va_end(args);
    longjmp(*(get_env(testcase)), FAILURE);
}

void record(struct __test_case* testcase, test_result result) {
    testcase->result = result;
    if (result == SUCCESS) {
        printf("Test %s passed\n", testcase->name);
    } else if (result == FAILURE) {
        printf("Test %s failed\n", testcase->name);
    }
    free(testcase);
}

void set_timeout(struct __test_case* testcase, const char* file, int line, time_t sec, suseconds_t usec) {
    (void)testcase; (void)file; (void)line; (void)sec; (void)usec;
    // Pas implémenté dans ce stub minimal
}

void report(FILE* out, struct __test_section* section) {
    fprintf(out, "--- Report section %s ---\n", section->name);
}

void report_csv_head(FILE* out) { (void)out; }
void report_csv(FILE* out, struct __test_section* section) { (void)out; (void)section; }
void report_analysis_head(FILE* out) { (void)out; }
void report_analysis(FILE* out, struct __test_section* section) { (void)out; (void)section; }

void initialize_tests() {
    printf("Initializing test framework...\n");
}

