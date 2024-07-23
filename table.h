/* ======= GRUPO J ======= */
/* Luccas da Silva Lima 00324683 */
/* Matheus Almeida da Silva 00316326 */

#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "valor_lexico.h"
#include "errors.h"

// Tipo de Dado
typedef enum DataType
{
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_BOOL,
    TYPE_UNDECLARED,
    TYPE_PLACEHOLDER
} DataType;

DataType determine_data_type(DataType type1, DataType type2);

#define TABLE_BUCKET_COUNT 32
// Natureza de um símbolo
typedef enum Nature
{
    NATURE_IDENTIFIER,
    NATURE_LITERAL,
    NATURE_FUNCTION,
    NATURE_NON_EXISTENT
} Nature;

// Conteúdo de uma entrada na tabela
typedef struct TableEntry
{
    int line;
    Nature nature;
    DataType type;
    Valor_lexico lex_val;
} TableEntry;

// Entrada na tabela de símbolos
typedef struct TableNode
{
    char* identifier;
    TableEntry entry;
    struct TableNode* next;
} TableNode;

// Um bucket da tabela de símbolos (contém todas entradas que mapeiam para um mesmo índice)
// Um bucket da tabela de símbolos (contém todas entradas que mapeiam para um mesmo índice)
typedef struct TableBucket
{
    int index;
    TableNode* nodes;
} TableBucket;

// Uma tabela de símbolo (um frame da stack)
#define TABLE_BUCKET_COUNT 32

typedef struct Table
{
    int bucket_count;
    TableBucket* buckets;
} Table;

// Um elemento da pilha de tabelas de símbolos
typedef struct TableStack
{
    Table* table;
    struct TableStack* next;    
} TableStack;

extern TableStack* globalTableStack;

void initialize_global_stack();
void push_table_to_global_stack(Table* table);
void pop_global_stack();
void transfer_to_lower_stack();

// Criação de uma nova pilha de tabela de símbolos
TableStack* create_table_stack();

// Criação de uma nova tabela de símbolos
Table* create_table();

// Criação de um valor de símbolo para a tabela de símbolos
TableEntry create_table_entry(Nature nature, DataType type, Valor_lexico lex_val);

// Liberação de memória
void free_table_entry(TableEntry entry);
void free_table(Table* table);
void free_table_stack(TableStack* stack);

// Operações com chaves.

TableEntry get_empty_table_entry();
TableEntry get_entry_by_key(Table* table, char* key);
TableEntry find_in_stack(char* key);
TableEntry find_in_table(char* key, int is_function);
size_t fnv1a_hash(size_t capacity, char* key);
int compare_keys(TableNode* node, char* key);

// Operações que a tabela de pilhas.

void add_entry_to_global_stack(TableEntry entry);
void add_entry_to_lower_stack(TableEntry entry);
void add_entry_to_table(Table* table, TableEntry entry);

// Verifica se a chave já existe em uma tabela dada
int key_exists_in_table(Table* table, char* key);

// Verifica se o símbolo já foi declarado nas tabelas da pilhas
void verify_declaration(TableEntry entry);

// Funções utilitárias.

void display_global_stack(int depth);
void display_table(Table* table);
void display_bucket(TableBucket* bucket);
void display_node(TableNode* node);
void display_entry(TableEntry entry);
DataType get_type_from_identifier(Valor_lexico identifier);
void validate_variable_identifier(Valor_lexico identifier);
void validate_function_identifier(Valor_lexico identifier);

#endif
