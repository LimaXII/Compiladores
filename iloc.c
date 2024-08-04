/* ======= GRUPO J ======= */
/* Luccas da Silva Lima 00324683 */
/* Matheus Almeida da Silva 00316326 */

#include "iloc.h"
#include <string.h>

int gen_temp() {
    static int temp_count = 0;
    return temp_count++;
}

int gen_label() {
    static int label_count = 0;
    return label_count++;
}

void gen_code(IlocCodeList** head, Opcode opcode, int t1, int t2, int t3, int t4) {
    IlocCodeList* new_node = (IlocCodeList*)malloc(sizeof(IlocCodeList));
    new_node->iloc_code.opcode = opcode;
    new_node->iloc_code.t1 = t1;
    new_node->iloc_code.t2 = t2;
    new_node->iloc_code.t3 = t3;
    new_node->iloc_code.t4 = t4;
    new_node->next = NULL;

    // Se a lista está vazia, o novo nó se torna o início
    if (*head == NULL) {
        *head = new_node;
    } else {
        // Encontre o último nó da lista
        IlocCodeList* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        // Adiciona o novo nó ao final da lista
        current->next = new_node;
    }
}

IlocCodeList* concatenate_code(IlocCodeList* head1, IlocCodeList* head2) {
    IlocCodeList* new_head = NULL;
    IlocCodeList* current = NULL;
    IlocCodeList* temp = NULL;

    for (temp = head1; temp != NULL; temp = temp->next) {
        IlocCodeList* new_node = (IlocCodeList*)malloc(sizeof(IlocCodeList));
        new_node->iloc_code = temp->iloc_code;
        new_node->next = NULL;

        if (new_head == NULL) {
            new_head = new_node;
        } else {
            current->next = new_node;
        }
        current = new_node;
    }

    for (temp = head2; temp != NULL; temp = temp->next) {
        IlocCodeList* new_node = (IlocCodeList*)malloc(sizeof(IlocCodeList));
        new_node->iloc_code = temp->iloc_code;
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

void print_iloc_code_list(IlocCodeList* head) {
    IlocCodeList* current = head;
    while (current) {
        switch (current->iloc_code.opcode) {
            case OP_NOP:
                printf("nop\n");
                break;
            case OP_ADD:
                printf("add r%d, r%d => r%d\n", current->iloc_code.t1, current->iloc_code.t2, current->iloc_code.t3);
                break;
            case OP_SUB:
                printf("sub r%d, r%d => r%d\n", current->iloc_code.t1, current->iloc_code.t2, current->iloc_code.t3);
                break;
            case OP_MULT:
                printf("mult r%d, r%d => r%d\n", current->iloc_code.t1, current->iloc_code.t2, current->iloc_code.t3);
                break;
            case OP_DIV:
                printf("div r%d, r%d => r%d\n", current->iloc_code.t1, current->iloc_code.t2, current->iloc_code.t3);
                break;
            case OP_NEG:
                printf("rsubI r%d, 0 => r%d\n", current->iloc_code.t1, current->iloc_code.t3);
                break;
            case OP_NEG_LOG:
                printf("xorI r%d, -1 => r%d\n", current->iloc_code.t1, current->iloc_code.t3);
                break;
            case OP_AND:
                printf("and r%d, r%d => r%d\n", current->iloc_code.t1, current->iloc_code.t2, current->iloc_code.t3);
                break;
            case OP_OR:
                printf("or r%d, r%d => r%d\n", current->iloc_code.t1, current->iloc_code.t2, current->iloc_code.t3);
                break;
            case OP_CMP_EQ:
                printf("cmp_EQ r%d, r%d -> r%d\n", current->iloc_code.t1, current->iloc_code.t2, current->iloc_code.t3);
                break;
            case OP_CMP_NE:
                printf("cmp_NE r%d, r%d -> r%d\n", current->iloc_code.t1, current->iloc_code.t2, current->iloc_code.t3);
                break;
            case OP_CMP_GT:
                printf("cmp_GT r%d, r%d -> r%d\n", current->iloc_code.t1, current->iloc_code.t2, current->iloc_code.t3);
                break;
            case OP_CMP_LT:
                printf("cmp_LT r%d, r%d -> r%d\n", current->iloc_code.t1, current->iloc_code.t2, current->iloc_code.t3);
                break;
            case OP_CMP_GE:
                printf("cmp_GE r%d, r%d -> r%d\n", current->iloc_code.t1, current->iloc_code.t2, current->iloc_code.t3);
                break;
            case OP_CMP_LE:
                printf("cmp_LE r%d, r%d -> r%d\n", current->iloc_code.t1, current->iloc_code.t2, current->iloc_code.t3);
                break;
            case OP_CBR:
                printf("cbr r%d -> l%d, l%d\n", current->iloc_code.t1, current->iloc_code.t3, current->iloc_code.t4);
                break;
            case OP_JUMPI:
                printf("jumpI -> l%d\n", current->iloc_code.t1);
                break;
            case OP_LOADI:
                printf("loadI %d => r%d\n", current->iloc_code.t1, current->iloc_code.t3);
                break;
            case OP_LOADAI_GLOBAL:
                printf("loadAI rbss, %d => r%d\n", current->iloc_code.t1, current->iloc_code.t3);
                break;
            case OP_LOADAI_LOCAL:
                printf("loadAI rfp, %d => r%d\n", current->iloc_code.t1, current->iloc_code.t3);
                break;
            case OP_STOREAI_GLOBAL:
                printf("storeAI r%d => rbss, %d\n", current->iloc_code.t1, current->iloc_code.t3);
                break;
            case OP_STOREAI_LOCAL:
                printf("storeAI r%d => rfp, %d\n", current->iloc_code.t1, current->iloc_code.t3);
                break;
            case OP_LABEL:
                printf("L%d:", current->iloc_code.t1);
                break;
            default:
                printf("Instrução desconhecida.\n");
                break;
        }
        current = current->next;
    }
}

void free_iloc_code_list(IlocCodeList* head) {
    IlocCodeList* current = head;
    IlocCodeList* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

void gen_label_code(IlocCodeList** head, int label_num) {
    IlocCodeList* new_node = (IlocCodeList*)malloc(sizeof(IlocCodeList));
    new_node->iloc_code.opcode = OP_LABEL;
    new_node->iloc_code.t1 = label_num;
    new_node->iloc_code.t2 = -1;
    new_node->iloc_code.t3 = -1;
    new_node->iloc_code.t4 = -1;
    new_node->next = *head;
    *head = new_node;
}
