#ifndef ILOC_H
#define ILOC_H

#include <stdio.h>
#include <stdlib.h>

#define OP_NOP "nop"
#define OP_ADD "add"
#define OP_SUB "sub"
#define OP_MULT "mult"
#define OP_DIV "div"
#define OP_NEG "neg"
#define OP_NEG_LOG "neg_log"
#define OP_AND "and"
#define OP_OR "or"
#define OP_CMP_EQ "cmp_EQ"
#define OP_CMP_NE "cmp_NE"
#define OP_CMP_GT "cmp_GT"
#define OP_CMP_LT "cmp_LT"
#define OP_CMP_GE "cmp_GE"
#define OP_CMP_LE "cmp_LE"
#define OP_CBR "cbr"
#define OP_JUMPI "jumpI"
#define OP_LOADI "loadI"
#define OP_LOADAI_GLOBAL "loadAI_global"
#define OP_LOADAI_LOCAL "loadAI_local"
#define OP_STOREAI_GLOBAL "storeAI_global"
#define OP_STOREAI_LOCAL "storeAI_local"

typedef struct IlocCode
{
    char* opcode;
    int t1; // Primeiro temporário ou argumento
    int t2; // Segundo temporário ou argumento (opcional)
    int t3; // Primeiro temporário de saída
    int t4; // Segundo temporário de saída (opcional, para operações de branching)
} IlocCode;

typedef struct IlocCodeList
{
    IlocCode iloc_code;
    struct IlocCodeList* next;
} IlocCodeList;

int gen_temp();
int gen_label();
void gen_code(IlocCodeList** head, char* opcode, int t1, int t2, int t3, int t4);
IlocCodeList* concatenate_code(IlocCodeList* head1, IlocCodeList* head2);
void free_iloc_code_list(IlocCodeList* head);
void print_iloc_code_list(IlocCodeList* head);

#endif // ILOC_H
