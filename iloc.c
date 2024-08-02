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

void gen_code(IlocCodeList** head, char* opcode, int t1, int t2, int t3, int t4) {
    IlocCodeList* new_node = (IlocCodeList*)malloc(sizeof(IlocCodeList));
    new_node->iloc_code.opcode = strdup(opcode);
    new_node->iloc_code.t1 = t1;
    new_node->iloc_code.t2 = t2;
    new_node->iloc_code.t3 = t3;
    new_node->iloc_code.t4 = t4;
    new_node->next = *head;
    *head = new_node;
}

IlocCodeList* concatenate_code(IlocCodeList* head1, IlocCodeList* head2) {
    IlocCodeList* new_head = NULL;
    IlocCodeList* current = NULL;
    IlocCodeList* temp = NULL;

    // Adiciona os elementos da primeira lista
    for (temp = head1; temp != NULL; temp = temp->next) {
        IlocCodeList* new_node = (IlocCodeList*)malloc(sizeof(IlocCodeList));
        new_node->iloc_code.opcode = strdup(temp->iloc_code.opcode);
        new_node->iloc_code.t1 = temp->iloc_code.t1;
        new_node->iloc_code.t2 = temp->iloc_code.t2;
        new_node->iloc_code.t3 = temp->iloc_code.t3;
        new_node->iloc_code.t4 = temp->iloc_code.t4;
        new_node->next = NULL;

        if (new_head == NULL) {
            new_head = new_node;
        } else {
            current->next = new_node;
        }
        current = new_node;
    }

    // Adiciona os elementos da segunda lista
    for (temp = head2; temp != NULL; temp = temp->next) {
        IlocCodeList* new_node = (IlocCodeList*)malloc(sizeof(IlocCodeList));
        new_node->iloc_code.opcode = strdup(temp->iloc_code.opcode);
        new_node->iloc_code.t1 = temp->iloc_code.t1;
        new_node->iloc_code.t2 = temp->iloc_code.t2;
        new_node->iloc_code.t3 = temp->iloc_code.t3;
        new_node->iloc_code.t4 = temp->iloc_code.t4;
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
        if (strcmp(current->iloc_code.opcode, OP_NOP) == 0) {
            printf("nop\n");
        } else if (strcmp(current->iloc_code.opcode, OP_ADD) == 0) {
            printf("add r%d, r%d => r%d\n", current->iloc_code.t1, current->iloc_code.t2, current->iloc_code.t3);
        } else if (strcmp(current->iloc_code.opcode, OP_SUB) == 0) {
            printf("sub r%d, r%d => r%d\n", current->iloc_code.t1, current->iloc_code.t2, current->iloc_code.t3);
        } else if (strcmp(current->iloc_code.opcode, OP_MULT) == 0) {
            printf("mult r%d, r%d => r%d\n", current->iloc_code.t1, current->iloc_code.t2, current->iloc_code.t3);
        } else if (strcmp(current->iloc_code.opcode, OP_DIV) == 0) {
            printf("div r%d, r%d => r%d\n", current->iloc_code.t1, current->iloc_code.t2, current->iloc_code.t3);
        } else if (strcmp(current->iloc_code.opcode, OP_NEG) == 0) {
            printf("rsubI r%d, 0 => r%d\n", current->iloc_code.t1, current->iloc_code.t3);
        } else if (strcmp(current->iloc_code.opcode, OP_NEG_LOG) == 0) {
            printf("xorI r%d, -1 => r%d\n", current->iloc_code.t1, current->iloc_code.t3);
        } else if (strcmp(current->iloc_code.opcode, OP_AND) == 0) {
            printf("and r%d, r%d => r%d\n", current->iloc_code.t1, current->iloc_code.t2, current->iloc_code.t3);
        } else if (strcmp(current->iloc_code.opcode, OP_OR) == 0) {
            printf("or r%d, r%d => r%d\n", current->iloc_code.t1, current->iloc_code.t2, current->iloc_code.t3);
        } else if (strcmp(current->iloc_code.opcode, OP_CMP_EQ) == 0) {
            printf("cmp_EQ r%d, r%d -> r%d\n", current->iloc_code.t1, current->iloc_code.t2, current->iloc_code.t3);
        } else if (strcmp(current->iloc_code.opcode, OP_CMP_NE) == 0) {
            printf("cmp_NE r%d, r%d -> r%d\n", current->iloc_code.t1, current->iloc_code.t2, current->iloc_code.t3);
        } else if (strcmp(current->iloc_code.opcode, OP_CMP_GT) == 0) {
            printf("cmp_GT r%d, r%d -> r%d\n", current->iloc_code.t1, current->iloc_code.t2, current->iloc_code.t3);
        } else if (strcmp(current->iloc_code.opcode, OP_CMP_LT) == 0) {
            printf("cmp_LT r%d, r%d -> r%d\n", current->iloc_code.t1, current->iloc_code.t2, current->iloc_code.t3);
        } else if (strcmp(current->iloc_code.opcode, OP_CMP_GE) == 0) {
            printf("cmp_GE r%d, r%d -> r%d\n", current->iloc_code.t1, current->iloc_code.t2, current->iloc_code.t3);
        } else if (strcmp(current->iloc_code.opcode, OP_CMP_LE) == 0) {
            printf("cmp_LE r%d, r%d -> r%d\n", current->iloc_code.t1, current->iloc_code.t2, current->iloc_code.t3);
        } else if (strcmp(current->iloc_code.opcode, OP_CBR) == 0) {
            printf("cbr r%d -> l%d, l%d\n", current->iloc_code.t1, current->iloc_code.t3, current->iloc_code.t4);
        } else if (strcmp(current->iloc_code.opcode, OP_JUMPI) == 0) {
            printf("jumpI -> l%d\n", current->iloc_code.t1);
        } else if (strcmp(current->iloc_code.opcode, OP_LOADI) == 0) {
            printf("loadI %d => r%d\n", current->iloc_code.t1, current->iloc_code.t3);
        } else if (strcmp(current->iloc_code.opcode, OP_LOADAI_GLOBAL) == 0) {
            printf("loadAI rbss, %d => r%d\n", current->iloc_code.t1, current->iloc_code.t3);
        } else if (strcmp(current->iloc_code.opcode, OP_LOADAI_LOCAL) == 0) {
            printf("loadAI rfp, %d => r%d\n", current->iloc_code.t1, current->iloc_code.t3);
        } else if (strcmp(current->iloc_code.opcode, OP_STOREAI_GLOBAL) == 0) {
            printf("storeAI r%d => rbss, %d\n", current->iloc_code.t1, current->iloc_code.t3);
        } else if (strcmp(current->iloc_code.opcode, OP_STOREAI_LOCAL) == 0) {
            printf("storeAI r%d => rfp, %d\n", current->iloc_code.t1, current->iloc_code.t3);
        } else {
            printf("Instrução desconhecida.\n");
        }
        current = current->next;
    }
}

void free_iloc_code_list(IlocCodeList* head) {
    IlocCodeList* current = head;
    IlocCodeList* next;

    while (current != NULL) {
        next = current->next;
        free(current->iloc_code.opcode); // Liberar a string alocada para opcode
        free(current);
