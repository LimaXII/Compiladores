#include <stdio.h>
#include <stdlib.h>
#include "ast_tree.h"

// Função para criar um novo nó
Node* create_node(Valor_lexico valor_lexico) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Erro ao alocar memória para um novo nó.\n");
        exit(1);
    }
    new_node->valor_lexico = valor_lexico;
    new_node->children = NULL;
    new_node->daddy = NULL;
    new_node->child_count = 0;
    return new_node;
}

// Função para adicionar um filho a um nó
void add_child(Node* parent, Node* child) {
    parent->child_count++;
    parent->children = (Node**)realloc(parent->children, parent->child_count * sizeof(Node*));
    if (parent->children == NULL) {
        fprintf(stderr, "Erro ao realocar memória para adicionar um novo filho.\n");
        exit(1);
    }
    parent->children[parent->child_count - 1] = child;
    child->daddy = parent;
}

// Função para imprimir a árvore recursivamente
void print_tree_labels(Node* node) {
    if (node == NULL) return;
    printf("%p [label=\"%s\"];\n", node, node->valor_lexico.token_val);
    for (int i = 0; i < node->child_count; i++) {
        print_tree_labels(node->children[i]);
    }
}

// Função para imprimir a hierarquia da árvore
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

// Função para exportar a árvore (implementação vazia conforme solicitado)
void exporta(Node* node) {
    if (node == NULL) return;

    print_tree_labels(node);
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

    print_tree_labels(root);
    print_tree_hierarchy(root);
    free_tree(root);

    return 0;
}