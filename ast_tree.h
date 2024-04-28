/* ======= GRUPO J ======= */
/* Luccas da Silva Lima 00324683 */
/* Matheus Almeida da Silva 00316326 */

#ifndef AST_TREE_H
#define AST_TREE_H
#include "valor_lexico.h"

// Definição da estrutura Node
typedef struct Node {
    Valor_lexico valor_lexico;              // Valor do nodo.
    struct Node** children;                 // Ponteiro de ponteiro para o nodo filho.
    struct Node* daddy;                     // Ponteiro para o nodo pai.
    int child_count;                        // Para contar quantos filhos tem.
} Node;

// Declarações das funções para manipulação da árvore
Node* create_node(Valor_lexico valor_lexico);
void add_child(Node* parent, Node* child);  // Adiciona um filho a arvore.
void print_tree_labels(Node* node);         // Printa endereço e label, no formato: 0x8235900 [label="minha_funcao"];
void print_tree_hierarchy(Node* node);      // Printa hierarquia, no formato: 0x8235900, 0x82358e8.
void free_tree(Node* node);                 // Libera memória. 
void exporta(Node* node);                   // Exporta a árvore.

#endif