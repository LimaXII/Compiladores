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