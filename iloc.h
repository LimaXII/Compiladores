#ifndef ILOC_H
#define ILOC_H

#include <stdio.h>
#include <stdlib.h>

typedef struct IlocCode
{
    char* opcode;
    int label;
    int t_op1;
    int t_op2;
    int t_result;
}IlocCode;

typedef struct IlocCodeList
{
    IlocCode iloc_code;
    struct IlocCodeList* next;
}IlocCodeList;
 

int gen_temp();
int gen_label();
void gen_code(IlocCodeList** head, char* opcode, int arg1, int arg2, int result, int label);
void concatenate_code(IlocCodeList** head1, IlocCodeList* head2);
void print_iloc_code_list(IlocCodeList* head);

#endif