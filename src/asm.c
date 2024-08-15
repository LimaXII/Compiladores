/* ======= GRUPO J ======= */
/* Luccas da Silva Lima 00324683 */
/* Matheus Almeida da Silva 00316326 */

#include "asm.h"
#include <string.h>

int n_registers = 0;
int gen_temp() {
    return n_registers++;
}

int gen_label() {
    static int label_count = 0;
    return label_count++;
}

void gen_code(AsmCodeList** head, Opcode opcode, int t1, int t2, int t3, int t4) {
    AsmCodeList* new_node = (AsmCodeList*)malloc(sizeof(AsmCodeList));
    new_node->asm_code.opcode = opcode;
    new_node->asm_code.t1 = t1;
    new_node->asm_code.t2 = t2;
    new_node->asm_code.t3 = t3;
    new_node->asm_code.t4 = t4;
    new_node->next = NULL;

    // Se a lista está vazia, o novo nó se torna o início
    if (*head == NULL) {
        *head = new_node;
    } else {
        // Encontre o último nó da lista
        AsmCodeList* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        // Adiciona o novo nó ao final da lista
        current->next = new_node;
    }
}

AsmCodeList* concatenate_code(AsmCodeList* head1, AsmCodeList* head2) {
    AsmCodeList* new_head = NULL;
    AsmCodeList* current = NULL;
    AsmCodeList* temp = NULL;

    for (temp = head1; temp != NULL; temp = temp->next) {
        AsmCodeList* new_node = (AsmCodeList*)malloc(sizeof(AsmCodeList));
        new_node->asm_code = temp->asm_code;
        new_node->next = NULL;

        if (new_head == NULL) {
            new_head = new_node;
        } else {
            current->next = new_node;
        }
        current = new_node;
    }

    for (temp = head2; temp != NULL; temp = temp->next) {
        AsmCodeList* new_node = (AsmCodeList*)malloc(sizeof(AsmCodeList));
        new_node->asm_code = temp->asm_code;
        new_node->next = NULL;

        if (new_head == NULL) {
            new_head = new_node;
        } else {
            current->next = new_node;
        }
        current = new_node;
    }

    return new_head;
}

void print_asm_code_list(AsmCodeList* head) {
    AsmCodeList* current = head;
    while (current) {
        switch (current->asm_code.opcode) {
            case OP_NOP:
                printf("\tnop\n");
                break;
            case OP_ADD:
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t1, "%rip", "%eax");
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t2, "%rip", "%edx");
                printf("\taddl    %s, %s \n", "%edx", "%eax");
                printf("\tmovl    %s, _temp_r_%d(%s) \n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_SUB:
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t1, "%rip", "%eax");
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t2, "%rip", "%edx");
                printf("\tsubl    %s, %s \n", "%edx", "%eax");
                printf("\tmovl    %s, _temp_r_%d(%s) \n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_MULT:
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t1, "%rip", "%eax");
                printf("\timull   _temp_r_%d(%s), %s \n", current->asm_code.t2, "%rip", "%eax");
                printf("\tmovl    %s, _temp_r_%d(%s) \n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_DIV:
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t1, "%rip", "%eax");
                printf("\tcdq \n");
                printf("\tidivl   _temp_r_%d(%s)\n", current->asm_code.t2, "%rip");
                printf("\tmovl    %s, _temp_r_%d(%s) \n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_NEG:
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t1, "%rip", "%eax");
                printf("\tnegl    %s \n", "%eax");
                printf("\tmovl    %s, _temp_r_%d(%s) \n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_NEG_LOG:
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t1, "%rip", "%eax");
                printf("\ttest    %s, %s\n", "%eax", "%eax");
                printf("\tmovl    $0, %s\n", "%eax");
                printf("\tsete    %s\n", "%al");
                printf("\tmovl    %s, _temp_r_%d(%s)\n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_AND:
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t1, "%rip", "%eax");
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t2, "%rip", "%edx");
                printf("\ttest    %s, %s\n", "%eax", "%edx");
                printf("\tmovl    $0, %s\n", "%eax");
                printf("\tsetne    %s\n", "%al");
                printf("\tmovl    %s, _temp_r_%d(%s)\n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_OR:
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t1, "%rip", "%eax");
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t2, "%rip", "%edx");
                printf("\tor      %s, %s\n", "%eax", "%edx");
                printf("\tmovl    $0, %s\n", "%eax");
                printf("\tsetne    %s\n", "%al");
                printf("\tmovl    %s, _temp_r_%d(%s)\n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_CMP_EQ:
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t1, "%rip", "%eax");
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t2, "%rip", "%edx");
                printf("\tcmp     %s, %s\n", "%edx", "%eax");
                printf("\tmovl    $0, %s\n", "%eax");
                printf("\tsete    %s\n", "%al");
                printf("\tmovl    %s, _temp_r_%d(%s)\n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_CMP_NE:
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t1, "%rip", "%eax");
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t2, "%rip", "%edx");
                printf("\tcmp     %s, %s\n", "%edx", "%eax");
                printf("\tmovl    $0, %s\n", "%eax");
                printf("\tsetne   %s\n", "%al");
                printf("\tmovl    %s, _temp_r_%d(%s)\n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_CMP_GT:
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t1, "%rip", "%eax");
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t2, "%rip", "%edx");
                printf("\tcmp      %s, %s\n", "%edx", "%eax");
                printf("\tmovl    $0, %s\n", "%eax");
                printf("\tsetg    %s\n", "%al");
                printf("\tmovl    %s, _temp_r_%d(%s)\n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_CMP_LT:
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t1, "%rip", "%eax");
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t2, "%rip", "%edx");
                printf("\tcmp      %s, %s\n", "%edx", "%eax");
                printf("\tmovl    $0, %s\n", "%eax");
                printf("\tsetl    %s\n", "%al");
                printf("\tmovl    %s, _temp_r_%d(%s)\n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_CMP_GE:
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t1, "%rip", "%eax");
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t2, "%rip", "%edx");
                printf("\tcmp      %s, %s\n", "%edx", "%eax");
                printf("\tmovl    $0, %s\n", "%eax");
                printf("\tsetge    %s\n", "%al");
                printf("\tmovl    %s, _temp_r_%d(%s)\n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_CMP_LE:
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t1, "%rip", "%eax");
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t2, "%rip", "%edx");
                printf("\tcmp      %s, %s\n", "%edx", "%eax");
                printf("\tmovl    $0, %s\n", "%eax");
                printf("\tsetle    %s\n", "%al");
                printf("\tmovl    %s, _temp_r_%d(%s)\n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_CBR:
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t1, "%rip", "%eax");
                printf("\ttest    %s, %s\n", "%eax", "%eax"); // eax AND eax
                printf("\tjnz  l%d\n", current->asm_code.t3);
                printf("\tjz  l%d\n", current->asm_code.t4);
                break;
            case OP_JUMPI:
                printf("\tjmp l%d\n", current->asm_code.t1);
                break;
            case OP_LOADI:
                printf("\tmovl $%d, _temp_r_%d(%s)\n", current->asm_code.t1, current->asm_code.t3, "%rip");
                break;
            case OP_LOADAI_GLOBAL:
                printf("\tmovl global%d(%s), %s\n"      , current->asm_code.t1/4   , "%rip"            , "%edx");
                printf("\tmovl %s, _temp_r_%d(%s)\n"    , "%edx"            , current->asm_code.t3    , "%rip");
                break;
            case OP_LOADAI_LOCAL:
                printf("\tmovl -%d(%s), %s\n"           , current->asm_code.t1     , "%rbp"            , "%edx");
                printf("\tmovl %s, _temp_r_%d(%s)\n"    , "%edx"            , current->asm_code.t3    , "%rip");
                break;
            case OP_STOREAI_GLOBAL:
                printf("\tmovl _temp_r_%d(%s), %s\n"    , current->asm_code.t1     , "%rip"            , "%edx");
                printf("\tmovl %s, global%d(%s)\n"      , "%edx"            , current->asm_code.t3 / 4, "%rip");
                break;
            case OP_STOREAI_LOCAL:
                printf("\tmovl _temp_r_%d(%s), %s\n"    , current->asm_code.t1     , "%rip"            , "%edx");
                printf("\tmovl %s, -%d(%s)\n"            , "%edx"            , current->asm_code.t3   , "%rbp");
                break;
            case OP_LABEL:
                printf("l%d: \n", current->asm_code.t1);
                break;
            case OP_RETURN:
                printf("\tmovl _temp_r_%d(%s), %s\n", current->asm_code.t1, "%rip", "%eax");
                printf("\tpopq %s\n", "%rbp");
                printf("\tret\n");
                break;
            default:
                printf("Instrução desconhecida.\n");
                break;
        }
        current = current->next;
    }
}

void free_asm_code_list(AsmCodeList* head) {
    AsmCodeList* current = head;
    AsmCodeList* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

void gen_label_code(AsmCodeList** head, int label_num) {
    AsmCodeList* new_node = (AsmCodeList*)malloc(sizeof(AsmCodeList));
    new_node->asm_code.opcode = OP_LABEL;
    new_node->asm_code.t1 = label_num;
    new_node->asm_code.t2 = -1;
    new_node->asm_code.t3 = -1;
    new_node->asm_code.t4 = -1;
    new_node->next = NULL;

    // Se a lista está vazia, o novo nó se torna o início
    if (*head == NULL) {
        *head = new_node;
    } else {
        // Encontre o último nó da lista
        AsmCodeList* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        // Adiciona o novo nó ao final da lista
        current->next = new_node;
    }
}

void generateAsm(AsmCodeList *head)
{
    Table* globalTable = globalTableStack->table;
    // Define variáveis globais e os registradores usados pelo ILOC
    int bucket_idx;
    TableNode* entry;
    int i = 0;
    printf("# --------------------\n# SEGMENTO DE DADOS\n# --------------------\n");
    printf(".data\n");
    printf("# ->Variáveis globais\n");
    for (bucket_idx=0; bucket_idx < globalTable->bucket_count; bucket_idx++)
    {
        entry = globalTable->buckets[bucket_idx].nodes;
        while (entry != NULL){
            if(entry->entry.nature == NATURE_IDENTIFIER){
                printf("global%d:\t.long\t0\n", i);
                i++;
            }
            entry = entry->next;
        }
    }
    printf("# ->Registradores ASM\n");
    for(int i = 0; i < n_registers; i++){
        printf("_temp_r_%d:\t.long\t0\n", i);
    }

    printf("# --------------------\n# SEGMENTO DE CÓDIGO\n# --------------------\n");

    // Adiciona info da main
    printf("\t.text\n\t.globl\tmain\n\t.type\tmain, @function\nmain:\n");
    printf("\tpushq	%s\n", "%rbp");
    printf("\tmovq %s, %s\n", "%rsp","%rbp");

    print_asm_code_list(head);
}
