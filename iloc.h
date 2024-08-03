#ifndef ILOC_H
#define ILOC_H

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    OP_NOP,
    OP_ADD,
    OP_SUB,
    OP_MULT,
    OP_DIV,
    OP_NEG,
    OP_NEG_LOG,
    OP_AND,
    OP_OR,
    OP_CMP_EQ,
    OP_CMP_NE,
    OP_CMP_GT,
    OP_CMP_LT,
    OP_CMP_GE,
    OP_CMP_LE,
    OP_CBR,
    OP_JUMPI,
    OP_LOADI,
    OP_LOADAI_GLOBAL,
    OP_LOADAI_LOCAL,
    OP_STOREAI_GLOBAL,
    OP_STOREAI_LOCAL
} Opcode;

typedef struct IlocCode {
    Opcode opcode;
    int t1;
    int t2;
    int t3;
    int t4;
} IlocCode;

typedef struct IlocCodeList {
    IlocCode iloc_code;
    struct IlocCodeList* next;
} IlocCodeList;

int gen_temp();
int gen_label();
void gen_code(IlocCodeList** head, Opcode opcode, int t1, int t2, int t3, int t4);
IlocCodeList* concatenate_code(IlocCodeList* head1, IlocCodeList* head2);
void print_iloc_code_list(IlocCodeList* head);
void free_iloc_code_list(IlocCodeList* head);

#endif
