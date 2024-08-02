#include "iloc.h"

int gen_temp() {
    static int temp_count = 0;
    return temp_count++;
}

int gen_label() {
    static int label_count = 0;
    return label_count++;
}

void gen_code(IlocCodeList** head, char* opcode, int arg1, int arg2, int result, int label) {
    IlocCodeList* new_node = (IlocCodeList*)malloc(sizeof(IlocCodeList));
    new_node->iloc_code.opcode = opcode;
    new_node->iloc_code.t_op1 = arg1;
    new_node->iloc_code.t_op2 = arg2;
    new_node->iloc_code.t_result = result;
    new_node->iloc_code.label = label;
    new_node->next = *head;
    *head = new_node;
}

void concatenate_code(IlocCodeList** head1, IlocCodeList* head2) {
    if (!head1 || !head2) return;
    
    IlocCodeList* current = *head1;
    if (!current) {
        *head1 = head2;
        return;
    }
    while (current->next) {
        current = current->next;
    }
    current->next = head2;
}

void print_iloc_code_list(IlocCodeList* head) {
    IlocCodeList* current = head;
    while (current) {
        if (current->iloc_code.label != -1) {
            printf("L%d: ", current->iloc_code.label);
        }
        printf("%s r%d, r%d => r%d\n",
               current->iloc_code.opcode,
               current->iloc_code.t_op1,
               current->iloc_code.t_op2,
               current->iloc_code.t_result);
        current = current->next;
    }
}
