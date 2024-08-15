/* ======= GRUPO J ======= */
/* Luccas da Silva Lima 00324683 */
/* Matheus Almeida da Silva 00316326 */

#ifndef ASM_H
#define ASM_H

#include <stdio.h>
#include <stdlib.h>
#include "table.h"

extern int n_registers;

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
    OP_STOREAI_LOCAL,
    OP_LABEL,
    OP_RETURN
} Opcode;

typedef struct AsmCode {
    Opcode opcode;
    int t1; // temporario de entrada 1
    int t2; // temporario de entrada 2
    int t3; // temporario de saida 1
    int t4; // temporario de saida 2
} AsmCode;

typedef struct AsmCodeList {
    AsmCode asm_code;
    struct AsmCodeList* next;
} AsmCodeList;

int gen_temp();
int gen_label();
void gen_code(AsmCodeList** head, Opcode opcode, int t1, int t2, int t3, int t4);
AsmCodeList* concatenate_code(AsmCodeList* head1, AsmCodeList* head2);
void print_asm_code_list(AsmCodeList* head);
void free_asm_code_list(AsmCodeList* head);
void gen_label_code(AsmCodeList** head, int label_num);
void generateAsm(AsmCodeList* head);
#endif
