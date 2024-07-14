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

//Natureza de um símbolo
typedef enum SymbolNature
{
    SYMBOL_NATURE_IDENTIFIER,
    SYMBOL_NATURE_LITERAL,
    SYMBOL_NATURE_FUNCTION,
    SYMBOL_NATURE_NON_EXISTENT
} SymbolNature;

//Valores associados a um símbolo na tabela
typedef struct TableEntryValue
{
    int lineNumber;
    SymbolNature symbol_nature;
    DataType dataType;
    Valor_lexico valor_lexico;
} TableEntryValue;

//Uma entrada numa tabela de símbolos
//Lista encadeada
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
 }TableBucket;


//Uma tabela de símbolo (um frame da stack)
#define N_SYMBOL_TABLE_BUCKETS 32

typedef struct Table
{
    int n_buckets;
    TableBucket* buckets;
} Table;

//Um elemento da pilha de tabelas de símbolos
typedef struct TableStack
{
    Table* Table;
    struct TableStack* nextItem;    
} TableStack;

extern TableStack* globalTableStack;

void initGlobalSymbolStack();

void addTableToGlobalStack(Table* Table);

void popGlobalStack();

void copySymbolsToGlobalStackBelow();

//Criação de uma nova pilha de tabela de símbolos
TableStack* createTableStack();

//Criação de uma nova tabela de símbolos
Table* createTable();

//Criação de um valor de símbolo para a tabela de símbolos
TableEntryValue createTableEntryValue(SymbolNature symbol_nature, DataType data_type, Valor_lexico valor_lexico);

//Operações de liberação de memória
void freeTableEntryValue(TableEntryValue value);
void freeTable(Table* table);
void freeTableStack(TableStack* stack);

//////////////////////////////////////////////////////////////
//          OPERAÇÕES COM CHAVES E VALORES
//////////////////////////////////////////////////////////////

// Retorna uma entrada vazia
TableEntryValue getEmptyTableEntryValue();

// Checa se há um valor associado a uma chave numa tabela
TableEntryValue getTableEntryValueByKey(Table* table, char* key);

// Percorre as tabelas da pilha por um valor associado à chave
TableEntryValue getSymbolFromStackByKey(char* key);

// djba2 hash function
size_t getIndex(size_t capacity, char* key);

int isSameKey(TableEntry* entry, char* key);


//////////////////////////////////////////////////////////////
//          OPERAÇÕES COM A TABELA DE PILHAS
//////////////////////////////////////////////////////////////

// Adiciona um símbolo a uma tabela de símbolos
void addSymbolValueToTable(Table* table, TableEntryValue value);
void addSymbolValueToGlobalTableStack(TableEntryValue value);
void addSymbolValueToBelowGlobalTableStack(TableEntryValue value);

// Verifica se a chave já existe em uma tabela dada
int isKeyInTable(Table* table, char* key);

// Verifica se o símbolo já foi declarado nas tabelas da pilhas
// (percorre do topo ao fim da pilha)
void checkSymbolDeclared(TableEntryValue value);

// Verifica se o identificador já foi declarado nas tabelas da pilhas
// (percorre do topo ao fim da pilha)
int isIdentifierDeclared(char* identifier);

/////////////////////////////////////////////////////////////
//          UTILS
//////////////////////////////////////////////////////////////

void printGlobalTableStack(int depth);
DataType inferTypeFromIdentifier(Valor_lexico identifier);
void checkIdentifierIsVariable(Valor_lexico identifier);
void checkIdentifierIsFunction(Valor_lexico identifier);

#endif