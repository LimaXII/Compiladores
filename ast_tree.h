#ifndef AST_TREE_H
#define AST_TREE_H
#include "valor_lexico.h"

// Definição da estrutura Node
typedef struct Node {
    Valor_lexico valor_lexico;
    struct Node** children;
    struct Node* daddy;
    int child_count;
} Node;

// Declarações das funções para manipulação da árvore
Node* create_node(Valor_lexico valor_lexico);
void add_child(Node* parent, Node* child);
void print_tree_labels(Node* node);
void print_tree_hierarchy(Node* node);
void free_tree(Node* node);
void exporta(Node* node);

#endif // AST_TREE_H