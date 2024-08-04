/* ======= GRUPO J ======= */
/* Luccas da Silva Lima 00324683 */
/* Matheus Almeida da Silva 00316326 */

#include "table.h"

DataType determine_data_type(DataType type1, DataType type2){
    DataType result_type = TYPE_PLACEHOLDER;
    if(type1 == TYPE_INT){
        switch(type2){
            case TYPE_INT:     result_type = TYPE_INT;      break;
            case TYPE_FLOAT:   result_type = TYPE_FLOAT;    break;
            case TYPE_BOOL:    result_type = TYPE_INT;      break;
            default: printf("Erro: Tipo desconhecido para combinação INT e %d\n.", type2); break;
        }
    } else if(type1 == TYPE_FLOAT){
        switch(type2){
            case TYPE_INT:     result_type = TYPE_FLOAT;    break;
            case TYPE_FLOAT:   result_type = TYPE_FLOAT;    break;
            case TYPE_BOOL:    result_type = TYPE_FLOAT;    break;
            default: printf("Erro: Tipo desconhecido para combinação FLOAT e %d\n.", type2); break;
        }
    } else if(type1 == TYPE_BOOL){
        switch(type2){
            case TYPE_INT:     result_type = TYPE_INT;      break;
            case TYPE_FLOAT:   result_type = TYPE_FLOAT;    break;
            case TYPE_BOOL:    result_type = TYPE_BOOL;     break;
            default: printf("Erro: Tipo desconhecido para combinação BOOL e %d\n.", type2); break;
        }
    } else {
        printf("Erro: Tipo desconhecido para combinação %d e %d\n", type1, type2);
    }
    return result_type;
}

void initialize_global_stack()
{
    globalTableStack = create_table_stack();
    globalTableStack->table = create_table();
    globalTableStack->last_offset = 0;
    globalTableStack->isGlobal = true;
}

void push_table_to_global_stack(Table* table)
{
    TableStack* new_stack_frame = create_table_stack();
    new_stack_frame->next = globalTableStack;
    new_stack_frame->table = table;

    if(globalTableStack->isGlobal){
        new_stack_frame->last_offset = 0;
    } else {
        table->last_offset = globalTableStack->last_offset;
        new_stack_frame->last_offset = globalTableStack->last_offset;
    }

    globalTableStack = new_stack_frame;
}

void pop_global_stack()
{
    free_table(globalTableStack->table);
    globalTableStack = globalTableStack->next;
}

// Cria uma nova pilha.
TableStack* create_table_stack()
{
    TableStack* stack = malloc(sizeof(TableStack));
    if(!stack) return NULL;
    stack->table = NULL;
    stack->next = NULL;
    stack->isGlobal = false;
    stack->last_offset = 0;

    return stack;
}

// Cria uma nova tabela de simbolos.
Table* create_table()
{
    Table* table = malloc(sizeof(Table));
    if (!table) return NULL;

    table->bucket_count = TABLE_BUCKET_COUNT;
    table->buckets = calloc(TABLE_BUCKET_COUNT, sizeof(TableBucket));
    table->last_offset = 0;
    
    for(int i = 0; i < TABLE_BUCKET_COUNT; i++){
        table->buckets[i].index = i;
        table->buckets[i].nodes = NULL;
    }
    return table;
}

// Cria um valor para na tabela de símbolos.
TableEntry create_table_entry(Nature nature, DataType type, Valor_lexico lex_val){
    TableEntry entry;

    entry.line = lex_val.line_number;
    entry.nature = nature;
    entry.type = type;
    entry.lex_val = lex_val;
    entry.lex_val.token_val = strdup(lex_val.token_val);
    return entry;
}

void free_table_entry(TableEntry entry){
    freeValor_lexico(entry.lex_val);
}

void free_table(Table* table){
    for(int i = 0; i < TABLE_BUCKET_COUNT; i++){
        TableBucket* bucket = &table->buckets[i];
        TableNode* node = bucket->nodes;
        TableNode* next_node;

        while(node != NULL){
            next_node = node->next;
            free(node->identifier);
            free_table_entry(node->entry);
            free(node);
            node = next_node;
        }
    }
    free(table->buckets);
    free(table);
}

void free_table_stack(TableStack* stack){
    TableStack* next;
    do{
        next = stack->next;
        free_table(stack->table);
        free(stack);
        stack = next;
    }while(stack != NULL);

    free(stack);
}

// Retorna uma entrada vazia
TableEntry get_empty_table_entry()
{
    TableEntry entry;
    entry.nature = NATURE_NON_EXISTENT;
    return entry;
}

// Checa se há um valor associado a uma chave
TableEntry get_entry_by_key(Table* table, char* key)
{
    if (!table) return get_empty_table_entry();

    size_t index = fnv1a_hash(table->bucket_count, key);
    TableBucket* bucket = &table->buckets[index];
    TableNode* node = bucket->nodes;

    while(node != NULL){
        if (compare_keys(node, key)){
            return node->entry;
        }
        node = node->next;
    }

    return get_empty_table_entry();
}

// Hash function
// FNV-1a (Fowler-Noll-Vo hash function).
size_t fnv1a_hash(size_t capacity, char* key) {
    const size_t fnv_prime = 0x100000001b3;
    const size_t fnv_offset_basis = 0xcbf29ce484222325;
    size_t hash = fnv_offset_basis;

    while (*key) {
        hash ^= (unsigned char)*key++;
        hash *= fnv_prime;
    }

    return hash % capacity;
}

int compare_keys(TableNode* node, char* key)
{
    return strcmp(key, node->identifier) == 0;
}

// Operações com a Pilha.
void add_entry_to_global_stack(TableEntry entry){
    add_entry_to_table(globalTableStack->table, entry, globalTableStack->isGlobal);
}

void add_entry_to_lower_stack(TableEntry entry){
    add_entry_to_table(globalTableStack->next->table, entry, globalTableStack->next->isGlobal);
}

// Adiciona um símbolo a uma tabela de símbolos
void add_entry_to_table(Table* table, TableEntry entry, bool isGlobal){
    if (entry.nature != NATURE_LITERAL){
        verify_declaration(entry);
    }

    entry.isGlobal = isGlobal;
    if (entry.nature == NATURE_LITERAL || entry.nature == NATURE_FUNCTION){
        entry.offset = -1;
    }
    else {
        entry.offset = table->last_offset;
        table->last_offset += 4;
    }

    char* key = strdup(entry.lex_val.token_val);
    size_t index = fnv1a_hash(table->bucket_count, key);
    TableBucket* bucket = &table->buckets[index];
    
    TableNode* new_node = malloc(sizeof(TableNode));
    new_node->identifier = strdup(key);
    new_node->entry = entry;
    new_node->next = NULL;

    if(bucket->nodes != NULL){
        TableNode* current_node = bucket->nodes;
        TableNode* last_node;

        do{
            last_node = current_node;
            current_node = current_node->next;
        }while (current_node != NULL);

        last_node->next = new_node;
    } else {
        bucket->nodes = new_node;
    }
}

int key_exists_in_table(Table* table, char* key){
    TableEntry entry = get_entry_by_key(table, key);
    return entry.nature != NATURE_NON_EXISTENT;
}

// Verifica se o símbolo já foi declarado nas tabelas da pilhas
void verify_declaration(TableEntry entry){
    char* key = entry.lex_val.token_val;
    TableEntry found;
    if (entry.nature == NATURE_FUNCTION){
        found = find_in_table(key, 1);
    }
    else{
        found = find_in_table(key, 0);
    }
    if(found.nature != NATURE_NON_EXISTENT){
        printf("Erro semântico encontrado na linha %d: Símbolo \"%s\" foi declarado anteriormente na linha %d.\n", entry.line, key, found.line);
        exit(ERR_DECLARED);
    }
}

TableEntry find_in_table(char* key, int is_function){
    TableStack* stack_top = globalTableStack;
    TableEntry entry;

    if (is_function){
        entry = get_entry_by_key(stack_top->next->table, key);
    }
    else{
        entry = get_entry_by_key(stack_top->table, key);
    }   
    return entry;
}

TableEntry find_in_stack(char* key){
    TableStack* stack_top = globalTableStack;
    TableEntry entry;

    do{
        entry = get_entry_by_key(stack_top->table, key);
        stack_top = stack_top->next;
    }while((stack_top != NULL) && (entry.nature == NATURE_NON_EXISTENT));

    return entry;
}

Table* get_table_with_key_in_stack(char* key){
    TableStack* stack_top = globalTableStack;

    while(stack_top != NULL && key_exists_in_table(stack_top->table, key)){
        stack_top = stack_top->next;
    }
    return stack_top->table;
}

// Print.
void display_global_stack(int verbose)
{
    printf("\n====================\n");

    TableStack* stack_top = globalTableStack;

    do{
        printf("Scope ID %p\n", stack_top);
        if(verbose) display_table(stack_top->table);
        stack_top = stack_top->next;
    }while(stack_top != NULL);

    printf("====================\n");
}

void display_table(Table* table){
    printf("====================\n");
    for(int i = 0; i < TABLE_BUCKET_COUNT; i++){
        TableBucket bucket = table->buckets[i];
        display_bucket(&bucket);
    }
    printf("====================\n");
}

void display_bucket(TableBucket* bucket){
    TableNode* node = bucket->nodes;

    while(node != NULL){
        display_node(node);
        node = node->next;
    }
}

void display_node(TableNode* node){
    printf("Key %s\t", node->identifier);
    display_entry(node->entry);
}

void display_entry(TableEntry entry){
    printf("Is Global: %d\t", entry.isGlobal);
    printf("Offset: %d\t", entry.offset);
    printValor_lexico(entry.lex_val);
}

DataType get_type_from_identifier(Valor_lexico identifier){
    TableEntry entry = find_in_stack(identifier.token_val);
    if(entry.nature == NATURE_NON_EXISTENT){
        printf("Erro semântico encontrado na linha %d: O identificador \"%s\" não foi declarado nesse escopo.\n", 
        identifier.line_number, identifier.token_val
        );
        exit(ERR_UNDECLARED);
    }
    return entry.type;
}

void validate_variable_identifier(Valor_lexico identifier){
    TableEntry entry = find_in_stack(identifier.token_val);
    if(entry.nature != NATURE_IDENTIFIER){
        printf("Erro semântico encontrado na linha %d: O identificador \"%s\" foi usado como variável, mas foi declarado como função na linha %d.\n", 
        identifier.line_number, identifier.token_val, entry.line
        );
        exit(ERR_FUNCTION);
    }
}

void validate_function_identifier(Valor_lexico identifier){
    TableEntry entry = find_in_stack(identifier.token_val);
    if(entry.nature != NATURE_FUNCTION){
        printf("Erro semântico encontrado na linha %d: O identificador \"%s\" foi usado como função, mas foi declarado como variável na linha %d.\n", 
        identifier.line_number, identifier.token_val, entry.line
        );
        exit(ERR_VARIABLE);
    }
}