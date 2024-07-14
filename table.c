#include "table.h"

DataType infer_type_from_types(DataType first_type, DataType second_type){
    DataType inferred_type = DATA_TYPE_PLACEHOLDER;
    if(first_type == DATA_TYPE_INT){
        switch(second_type){
            case DATA_TYPE_INT:     inferred_type = DATA_TYPE_INT;      break;
            case DATA_TYPE_FLOAT:   inferred_type = DATA_TYPE_FLOAT;    break;
            case DATA_TYPE_BOOL:    inferred_type = DATA_TYPE_INT;      break;
            default: printf("Erro: Não foi possível inferir tipos a partir de INT e %d\n", second_type); break;
        }
    }

    else if(first_type == DATA_TYPE_FLOAT){
           switch(second_type){
            case DATA_TYPE_INT:     inferred_type = DATA_TYPE_FLOAT;    break;
            case DATA_TYPE_FLOAT:   inferred_type = DATA_TYPE_FLOAT;    break;
            case DATA_TYPE_BOOL:    inferred_type = DATA_TYPE_FLOAT;    break;
            default: printf("Erro: Não foi possível inferir tipos a partir de FLOAT e %d\n", second_type); break;
        } 
    }

    else if(first_type == DATA_TYPE_BOOL){
        switch(second_type){
            case DATA_TYPE_INT:     inferred_type = DATA_TYPE_INT;      break;
            case DATA_TYPE_FLOAT:   inferred_type = DATA_TYPE_FLOAT;    break;
            case DATA_TYPE_BOOL:    inferred_type = DATA_TYPE_BOOL;     break;
            default: printf("Erro: Não foi possível inferir tipos a partir de BOOL e %d\n", second_type); break;
        }
    }
    else{
        printf("Erro: Não foi possível inferir tipos a partir de %d e %d\n", first_type, second_type);
    }

    return inferred_type;
}

/*

    ESTRUTURA DA PILHA DE TABELAS

                                TableStack -> Table
                                    v
                                TableStack -> Table
                                    v
    globalTableStack ->        TableStack -> Table

*/

//////////////////////////////////////////////////////////////

//          CRIAÇÃO DE ESTRUTURAS DE DADOS

//////////////////////////////////////////////////////////////

/*

    Cria a pilha global de símbolos

*/

void init_global_symbol_stack()
{
    globalTableStack = create_table_stack();
    globalTableStack->table = create_table();
}

void add_table_to_global_stack(Table* table)
{
    TableStack* new_stack_frame = create_table_stack();
    // Novo frame aponta para o topo da pilha global
    new_stack_frame->next_item = globalTableStack;
    new_stack_frame->table = table;
    // O frame se torna o novo topo
    globalTableStack = new_stack_frame; 
}

void pop_global_stack()
{
    free_table(globalTableStack->table);
    globalTableStack = globalTableStack->next_item;
}

// Copia os valores 
void copy_symbols_to_global_stack_below()
{
    if(globalTableStack->next_item == NULL){
        printf("Erro: tentando copiar símbolos para tabela abaixo, mas tabela atual é a global\n");
        exit(1);
    }

    int i;
    for(i=0; i < N_TABLE_BUCKETS; i++){
        TableBucket* bucket = &globalTableStack->table->buckets[i];
        TableEntry* last = bucket->entries;

        while(last != NULL){
            add_symbol_value_to_table(globalTableStack->next_item->table, last->value);
            last = last->next;
        }
    }
}

/*

    Criação de uma nova pilha de tabela de símbolos

*/
TableStack* create_table_stack()
{
    TableStack* table_stack = malloc(sizeof(TableStack));
    if(!table_stack) return NULL;

    table_stack->table = NULL;
    table_stack->next_item = NULL;
    return table_stack;
}

/*

    Criação de uma nova tabela de símbolos

*/
Table* create_table()
{
    Table* table = malloc(sizeof(Table));
    if (!table) return NULL;

    table->n_buckets = N_TABLE_BUCKETS;
    table->buckets = calloc(N_TABLE_BUCKETS, sizeof(TableBucket));
    
    int i;
    for(i=0; i<N_TABLE_BUCKETS;i++){
        table->buckets[i].n = i;
        table->buckets[i].entries = NULL;
    }

    return table;
}

/*

    Criação de um valor de símbolo para a tabela de símbolos

*/
TableEntryValue create_table_entry_value(SymbolNature symbol_nature, DataType data_type, Valor_lexico valor_lexico){
    TableEntryValue value;

    value.line_number = valor_lexico.line_number;
    value.symbol_nature = symbol_nature;
    value.data_type = data_type;
    value.valor_lexico = valor_lexico;
    // Copia a string
    value.valor_lexico.token_val = strdup(valor_lexico.token_val);

    return value;
}

void free_table_entry_value(TableEntryValue value){
    // Libera o valor léxico associado
    free_lexical_value(value.valor_lexico);
}

void free_table(Table* table){
    int i;
    TableBucket* bucket;
    TableEntry* entry;
    TableEntry* next_entry;
    // Percorre cada bucket e libera suas entradas
    for(i=0; i < N_TABLE_BUCKETS; i++){
        bucket = &table->buckets[i];
        entry = bucket->entries;
        // Percorre entradas
        while(entry != NULL){
            next_entry = entry->next;
            free(entry->key);
            free_table_entry_value(entry->value);
            free(entry);
            entry = next_entry;
        }

    }
    free(table->buckets);
    // Libera tabela
    free(table);
}

void free_table_stack(TableStack* stack){
    TableStack* next;
    do{
        next = stack->next_item;
        free_table(stack->table);
        free(stack);
        stack = next;
    }while(stack != NULL);

    free(stack);
}

//////////////////////////////////////////////////////////////

//          OPERAÇÕES COM CHAVES E VALORES

//////////////////////////////////////////////////////////////

// Retorna uma entrada vazia
TableEntryValue get_empty_table_entry_value()
{
    TableEntryValue value;
    value.symbol_nature = SYMBOL_NATURE_NON_EXISTENT;
    return value;
}

// Checa se há um valor associado a uma chave
TableEntryValue get_table_value_by_key(Table* table, char* key)
{
    if (!table) return get_empty_table_entry_value();

    // Pega o índice do bucket
    size_t index = get_index(table->n_buckets, key);

    // Obtém o bucket associado à chave
    TableBucket* bucket = &table->buckets[index];

    // Percorre os elementos do bucket até achar match ou o fim do bucket
    TableEntry* entry = bucket->entries;
    while(entry != NULL){
    
        if (is_same_key(entry, key))
        {
            // Match: retorna o valor da entrada
            return entry->value;
        }
        entry = entry->next;
    
    }

    return get_empty_table_entry_value();
}

// djba2 hash function
size_t get_index(size_t capacity, char* key)
{
    unsigned long hash = 5381;
    int c;
    while ((c = *key++))
    {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % capacity;
}

int is_same_key(TableEntry* entry, char* key)
{
    return strcmp(key, entry->key) == 0;
}

//////////////////////////////////////////////////////////////

//          OPERAÇÕES COM A TABELA DE PILHAS

//////////////////////////////////////////////////////////////

void add_symbol_value_to_global_table_stack(TableEntryValue value){
    add_symbol_value_to_table(globalTableStack->table, value);
}

void add_symbol_value_to_below_global_table_stack(TableEntryValue value){
    add_symbol_value_to_table(globalTableStack->next_item->table, value);
}

// Adiciona um símbolo a uma tabela de símbolos
void add_symbol_value_to_table(Table* table, TableEntryValue value){

    // Se não for literal, checa se já foi declarado na tabela
    if (value.symbol_nature != SYMBOL_NATURE_LITERAL){
        check_symbol_declared(value);
    }
    
    ////////////////////////////
    // CÁLCULO DA CHAVE
    ////////////////////////////
    char* key = strdup(value.valor_lexico.token_val);

    ////////////////////////////
    // ADIÇÃO À HASH TABLE
    ////////////////////////////
    
    // Pega o índice do bucket
    size_t index = get_index(table->n_buckets, key);
    TableBucket* bucket = &table->buckets[index];
    
    // Aloca uma nova entrada
    TableEntry* new_entry = malloc(sizeof(TableEntry));
    new_entry->key = strdup(key);
    new_entry->value = value;
    new_entry->next = NULL;

    // Se já existem elementos no bucket, adiciona ao fim da lista encadeada
    if(bucket->entries != NULL){
        TableEntry* cur_entry = bucket->entries;
        TableEntry* last_entry;

        // Percorre lista encadeada até o fim
        do{
            last_entry = cur_entry;
            cur_entry = cur_entry->next;
        }while (cur_entry != NULL);

        // Adiciona a nova entrada ao fim da lista
        last_entry->next = new_entry;

    }
    else{
        bucket->entries = new_entry;
    }

}

// Verifica se a chave já existe em uma tabela dada
int is_key_in_table(Table* table, char* key){
    TableEntryValue value = get_table_value_by_key(table, key);
    if (value.symbol_nature == SYMBOL_NATURE_NON_EXISTENT){
        return 0;
    }
    return 1;
}

// Verifica se o símbolo já foi declarado nas tabelas da pilhas
// (percorre do topo ao fim da pilha)
void check_symbol_declared(TableEntryValue value){
    
    char* key = value.valor_lexico.token_val;
    TableEntryValue found = get_symbol_from_stack_by_key(key);
    if(found.symbol_nature != SYMBOL_NATURE_NON_EXISTENT){
        printf("Erro semântico:\n\t Símbolo \"%s\" (linha %d) foi previamente declarado (linha %d)\n", key, value.line_number, found.line_number);
        exit(ERR_DECLARED);
    }
}

TableEntryValue get_symbol_from_stack_by_key(char* key){
    // Percorre a pilha
    TableStack* stack_top = globalTableStack;
    TableEntryValue value;

    do{
        value = get_table_value_by_key(stack_top->table, key);
        stack_top = stack_top->next_item;
    
    }while((stack_top != NULL) && (value.symbol_nature == SYMBOL_NATURE_NON_EXISTENT));

    return value;
}

Table* get_table_from_stack_with_matching_key(char* key){
    // Percorre a pilha
    TableStack* stack_top = globalTableStack;

    while(stack_top != NULL && is_key_in_table(stack_top->table, key)){
        stack_top = stack_top->next_item;
    }

    return stack_top->table;
}

//////////////////////////////////////////////////////////////

//          IMPRESSÃO E DEBUG

//////////////////////////////////////////////////////////////

void print_global_table_stack(int verbose)
{
    printf("\n====================\n");

    int i;
    TableStack* stack_top = globalTableStack;

    do{
        printf("Scope ID %p\n", stack_top);
        if(verbose) print_table(stack_top->table);
        stack_top = stack_top->next_item;
    }while(stack_top != NULL);

    printf("====================\n");
}

void print_table(Table* table){
    printf("====================\n");
    int i;
    for(i=0; i < N_TABLE_BUCKETS; i++){
        TableBucket bucket = table->buckets[i];
        print_bucket(&bucket);
    }
    printf("====================\n");
}

void print_bucket(TableBucket* bucket){
    TableEntry* entry = bucket->entries;
    printf("bucket %d\n", bucket->n);

    while(entry != NULL){
        print_entry(entry);
        entry = entry->next;
    }
}

void print_entry(TableEntry* entry){
    printf("Key %s\t", entry->key);
    print_entry_value(entry->value);
}

void print_entry_value(TableEntryValue value){
    print_lexical_value(value.valor_lexico);
}

DataType infer_type_from_identifier(Valor_lexico identifier){
    TableEntryValue value = get_table_value_by_key(identifier.token_val);
    if(value.symbol_nature == SYMBOL_NATURE_NON_EXISTENT){
        printf("Erro semântico: O identificador \"%s\" (linha %d) não foi declarado nesse escopo\n", 
        identifier.token_val, identifier.line_number
        );
        exit(ERR_UNDECLARED);
    }

    return value.dataType;
}

void check_identifier_is_variable(Valor_lexico identifier){
    TableEntryValue value = get_table_value_by_key(identifier.token_val);
    if(value.symbol_nature != SYMBOL_NATURE_IDENTIFIER){
        printf("Erro semântico: O identificador \"%s\" (linha %d) foi usado como variável, mas foi declarado como função (linha %d)\n", 
        identifier.token_val, identifier.line_number, value.line_number
        );
        exit(ERR_FUNCTION);
    }
}

void check_identifier_is_function(Valor_lexico identifier){
    TableEntryValue value = get_table_value_by_key(identifier.token_val);
    if(value.symbol_nature != SYMBOL_NATURE_FUNCTION){
        printf("Erro semântico: O identificador \"%s\" (linha %d) foi usado como função, mas foi declarado como variável (linha %d)\n", 
        identifier.token_val, identifier.line_number, value.line_number
        );
        exit(ERR_FUNCTION);
    }
}
