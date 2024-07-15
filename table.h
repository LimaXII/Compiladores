#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "valor_lexico.h"
#include "errors.h"

// Tipo de Dado
typedef enum DataType
{
    DATA_TYPE_INT,
    DATA_TYPE_FLOAT,
    DATA_TYPE_BOOL,
    DATA_TYPE_UNDECLARED,
    DATA_TYPE_PLACEHOLDER
} DataType;

DataType infer_type_from_types(DataType first_type, DataType second_type);

#define N_TABLE_BUCKETS 32
// Natureza de um símbolo
typedef enum SymbolNature
{
    SYMBOL_NATURE_IDENTIFIER,
    SYMBOL_NATURE_LITERAL,
    SYMBOL_NATURE_FUNCTION,
    SYMBOL_NATURE_NON_EXISTENT
} SymbolNature;

// Conteúdo de uma entrada na tabela
typedef struct TableEntryValue
{
    int line_number;
    SymbolNature symbol_nature;
    DataType data_type;
    Valor_lexico valor_lexico;
} TableEntryValue;

// Entrada na tabela de símbolos
typedef struct TableEntry
{
    char* key;
    TableEntryValue value;
    struct TableEntry* next;
} TableEntry;

// Um bucket da tabela de símbolos (contém todas entradas que mapeiam para um mesmo índice)
typedef struct TableBucket
{
    int n;
    TableEntry* entries;
} TableBucket;

// Uma tabela de símbolo (um frame da stack)
#define N_SYMBOL_TABLE_BUCKETS 32

typedef struct Table
{
    int n_buckets;
    TableBucket* buckets;
} Table;

// Um elemento da pilha de tabelas de símbolos
typedef struct TableStack
{
    Table* table;
    struct TableStack* next_item;    
} TableStack;

extern TableStack* globalTableStack;

void init_global_symbol_stack();
void add_table_to_global_stack(Table* table);
void pop_global_stack();
void copy_symbols_to_global_stack_below();

// Criação de uma nova pilha de tabela de símbolos
TableStack* create_table_stack();

// Criação de uma nova tabela de símbolos
Table* create_table();

// Criação de um valor de símbolo para a tabela de símbolos
TableEntryValue create_table_entry_value(SymbolNature symbol_nature, DataType data_type, Valor_lexico valor_lexico);

// Operações de liberação de memória
void free_table_entry_value(TableEntryValue value);
void free_table(Table* table);
void free_table_stack(TableStack* stack);

//////////////////////////////////////////////////////////////
//          OPERAÇÕES COM CHAVES E VALORES
//////////////////////////////////////////////////////////////

// Retorna uma entrada vazia
TableEntryValue get_empty_table_entry_value();

// Checa se há um valor associado a uma chave numa tabela
TableEntryValue get_table_value_by_key(Table* table, char* key);

// Percorre as tabelas da pilha por um valor associado à chave
TableEntryValue get_symbol_from_stack_by_key(char* key);

// djba2 hash function
size_t get_index(size_t capacity, char* key);

int is_same_key(TableEntry* entry, char* key);

//////////////////////////////////////////////////////////////
//          OPERAÇÕES COM A TABELA DE PILHAS
//////////////////////////////////////////////////////////////

// Adiciona um símbolo a uma tabela de símbolos
void add_symbol_value_to_global_table_stack(TableEntryValue value);
void add_symbol_value_to_below_global_table_stack(TableEntryValue value);
void add_symbol_value_to_table(Table* table, TableEntryValue value);

// Verifica se a chave já existe em uma tabela dada
int is_key_in_table(Table* table, char* key);

// Verifica se o símbolo já foi declarado nas tabelas da pilhas
// (percorre do topo ao fim da pilha)
void check_symbol_declared(TableEntryValue value);

/////////////////////////////////////////////////////////////
//          UTILS
//////////////////////////////////////////////////////////////

void print_global_table_stack(int depth);
void print_table(Table* table);
void print_bucket(TableBucket* bucket);
void print_entry(TableEntry* entry);
void print_entry_value(TableEntryValue value);
DataType infer_type_from_identifier(Valor_lexico identifier);
void check_identifier_is_variable(Valor_lexico identifier);
void check_identifier_is_function(Valor_lexico identifier);

#endif
