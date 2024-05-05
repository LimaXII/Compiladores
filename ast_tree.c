/* ======= GRUPO J ======= */
/* Luccas da Silva Lima 00324683 */
/* Matheus Almeida da Silva 00316326 */

#include <stdio.h>
#include <stdlib.h>
#include "ast_tree.h"

// Função para criar um novo nodo.
Node* create_node(Valor_lexico valor_lexico) {
    // Aloca memória do tamanho de um nodo.
    Node* new_node = (Node*)malloc(sizeof(Node));       
    if (new_node == NULL) {
        fprintf(stderr, "Erro ao alocar memória para um novo nó.\n");
        exit(1);
    }
    // Atribui os valores do nodo. Depois retorna o novo nodo criado.
    new_node->valor_lexico = valor_lexico;      
    new_node->children = NULL;
    new_node->daddy = NULL;
    new_node->child_count = 0;
    return new_node;
}

Node* create_node_to_function(Valor_lexico valor_lexico) {
    Node* node = createNode(valor_lexico);

    char* start = "call ";
    char* newtoken_val = malloc(strlen(start) + strlen(node->valor_lexico.token_val) + 1);

    strcpy(newtoken_val, start);
    strcat(newtoken_val, node->valor_lexico.token_val);

    free(node->valor_lexico.token_val);
    node->valor_lexico.token_val = newtoken_val;

    return node;
}

// Função para adicionar um nodo a um nó.
void add_child(Node* parent, Node* child) {
    parent->child_count++;         // Incrementa o número de filhos.
    parent->children = (Node**)realloc(parent->children, parent->child_count * sizeof(Node*));
    if (parent->children == NULL) {
        fprintf(stderr, "Erro ao realocar memória para adicionar um novo filho.\n");
        exit(1);
    }
    parent->children[parent->child_count - 1] = child;
    child->daddy = parent;
}

// Função para percorrer e imprimir a árvore, recursivamente.
// Imprime no formato: 0x8235900 [token_val="minha_funcao"];
void print_tree_token_vals(Node* node) {
    if (node == NULL) return;
    printf("%p [token_val=\"%s\"];\n", node, node->valor_lexico.token_val);
    for (int i = 0; i < node->child_count; i++) {
        print_tree_token_vals(node->children[i]);
    }
}

// Função para percorrer e imprimir a árvore, recursivamente.
// Imprime no formato: 0x8235900, 0x82358e8.
void print_tree_hierarchy(Node* node) {
    if (node == NULL) return;
    for (int i = 0; i < node->child_count; i++) {
        printf("%p, %p\n", node, node->children[i]);
        print_tree_hierarchy(node->children[i]);
    }
}

// Função para liberar a memória da árvore
void free_tree(Node* node) {
    if (node == NULL) return;
    for (int i = 0; i < node->child_count; i++) {
        free_tree(node->children[i]);
    }
    free(node->children);
    free(node);
}

// Função para exportar a árvore.
void exporta(Node* node) {
    if (node == NULL) return;

    // Caso a árvore não seja vazia. Imprime a arvore nos dois formatos solicitados.
    // 1. 0x8235900 [token_val="minha_funcao"];
    // 2. 0x8235900, 0x82358e8.
    print_tree_token_vals(node);
    print_tree_hierarchy(node);
}

// Exemplo de uso das funções
int main() {
    Valor_lexico val1 = {1, IDENTIFIER, "root"};
    Valor_lexico val2 = {2, LITERAL, "child1"};
    Valor_lexico val3 = {3, IDENTIFIER, "child2"};
    Valor_lexico val4 = {4, IDENTIFIER, "child3"};
    Valor_lexico val5 = {5, IDENTIFIER, "child4"};

    Node* root = create_node(val1);
    Node* child1 = create_node(val2);
    Node* child2 = create_node(val3);
    Node* child3 = create_node(val4);
    Node* child4 = create_node(val5);

    add_child(root, child1);
    add_child(root, child2);
    add_child(child1, child3);
    add_child(child1, child4);

    print_tree_token_vals(root);
    print_tree_hierarchy(root);
    free_tree(root);

    return 0;
}