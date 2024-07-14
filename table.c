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

                                SymbolTableStack -> SymbolTable
                                    v
                                SymbolTableStack -> SymbolTable
                                    v
    globalSymbolTableStack ->   SymbolTableStack -> SymbolTable
*/

void init_global_symbol_stack(){
    return 0; //todo
}



void add_table_to_global_stack(Table* table){
    return 0; //todo
}



void pop_global_stack(){
    return 0; //todo
}


void copy_symbols_to_global_stack_below(){
    return 0; //todo
}


TableStack* create_table_stack(){
    return 0; //todo
}


Table* create_table(){
    return 0; //todo
}


TableEntryValue create_table_entry_value(SymbolNature symbol_nature, DataType data_type, Valor_lexico valor_lexico){
    return 0; //todo
}


void free_table_entry_value(TableEntryValue value){
    return 0; //todo
}


void free_table(Table* table){
    return 0; //todo
}


void free_table_stack(TableStack* stack){
    return 0; //todo
}


TableEntryValue get_empty_table_entry_value(){
    return 0; //todo
}

TableEntryValue get_table_value_by_key(Table* table, char* key){
    return 0; //todo
}

TableEntryValue get_symbol_from_stack_by_key(char* key){
    return 0; //todo
}

size_t get_index(size_t capacity, char* key){
    unsigned long hash = 5381;
    int c;
    while ((c = *key++))
    {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % capacity;
}

int is_same_key(TableEntry* entry, char* key){
    return 0; //todo
}

void add_symbol_value_to_table(Table* table, TableEntryValue value){
    return 0; //todo
}

void add_symbol_value_to_global_table_stack(TableEntryValue value){
    return 0; //todo
}

void add_symbol_value_to_below_global_table_stack(TableEntryValue value){
    return 0; //todo
}


int is_key_in_table(Table* table, char* key){
    return 0; //todo
}

void check_symbol_declared(TableEntryValue value){
    return 0; //todo
}


int is_identifier_declared(char* identifier){
    return 0; //todo
}

void print_global_table_stack(int depth){
    return 0; //todo
}

DataType infer_type_from_identifier(Valor_lexico identifier){
    return 0; //todo
}

void check_identifier_is_variable(Valor_lexico identifier){
    return 0; //todo
}

void check_identifier_is_function(Valor_lexico identifier){
    return 0; //todo
}