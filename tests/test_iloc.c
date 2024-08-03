#include "../iloc.h"
#include "../ast_tree.h"
#include "../table.h"
#include "../valor_lexico.h"

TableStack* globalTableStack = NULL;

int main() {
    Node* node1 = create_node_valor_lexico(createValor_lexico("add", OTHER, 1), TYPE_INT);
    Node* node2 = create_node_valor_lexico(createValor_lexico("sub", OTHER, 1), TYPE_INT);
    Node* node3 = create_node_valor_lexico(createValor_lexico("mult", OTHER, 1), TYPE_INT);
    Node* node4 = create_node_valor_lexico(createValor_lexico("div", OTHER, 1), TYPE_INT);

    // Adicionando código ILOC a cada nó usando gen_code
    gen_code(&(node1->iloc_code_list), OP_ADD, 1, 2, 3, 0);
    gen_code(&(node2->iloc_code_list), OP_SUB, 4, 5, 6, 0);
    gen_code(&(node3->iloc_code_list), OP_MULT, 7, 8, 9, 0);
    gen_code(&(node4->iloc_code_list), OP_DIV, 10, 11, 12, 0);

    // Concatenando código ILOC dos nós
    Node* root = create_node_valor_lexico(createValor_lexico("root", OTHER, 1), TYPE_PLACEHOLDER);
    root->iloc_code_list = concatenate_code(node1->iloc_code_list, node2->iloc_code_list);
    root->iloc_code_list = concatenate_code(root->iloc_code_list, node3->iloc_code_list);
    root->iloc_code_list = concatenate_code(root->iloc_code_list, node4->iloc_code_list);

    // Imprimindo o código ILOC gerado
    printf("Generated ILOC Code for root node:\n");
    print_iloc_code_list(root->iloc_code_list);

    // Limpando a memória
    free_tree(node1);
    free_tree(node2);
    free_tree(node3);
    free_tree(node4);
    free_tree(root);

    return 0;
}
