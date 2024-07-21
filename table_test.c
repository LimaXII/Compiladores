#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include <errno.h>
#include "table.h"
#include "valor_lexico.h"
#include "errors.h"

// Variável global para manusear o ambiente de longjmp/setjmp
jmp_buf env;

TableStack* globalTableStack;

// Funções de teste
void test_infer_type_from_types();
void test_table_operations();
void test_symbol_declaration();
void test_print_valor_lexico();  // Adicione esta linha

int main() {
    test_infer_type_from_types();
    test_table_operations();
    test_symbol_declaration();
    test_print_valor_lexico();  // Adicione esta linha

    return 0;
}

void test_infer_type_from_types() {
    printf("Testing infer_type_from_types function...\n");

    // Test case 1
    if (infer_type_from_types(DATA_TYPE_INT, DATA_TYPE_FLOAT) != DATA_TYPE_FLOAT) {
        printf("Test case 1 failed.\n");
    } else {
        printf("Test case 1 passed.\n");
    }

    // Test case 2
    if (infer_type_from_types(DATA_TYPE_BOOL, DATA_TYPE_BOOL) != DATA_TYPE_BOOL) {
        printf("Test case 2 failed.\n");
    } else {
        printf("Test case 2 passed.\n");
    }

    // Test case 3
    if (infer_type_from_types(DATA_TYPE_FLOAT, DATA_TYPE_INT) != DATA_TYPE_FLOAT) {
        printf("Test case 3 failed.\n");
    } else {
        printf("Test case 3 passed.\n");
    }
}

void test_table_operations() {
    printf("Testing table operations...\n");

    // Initialize the global symbol stack
    init_global_symbol_stack();

    // Create a valor_lexico example
    Valor_lexico lex_val1 = createValor_lexico("x", IDENTIFIER, 1);
    TableEntryValue entry_val1 = create_table_entry_value(SYMBOL_NATURE_IDENTIFIER, DATA_TYPE_INT, lex_val1);

    // Add the symbol to the global table stack
    add_symbol_value_to_global_table_stack(entry_val1);

    // Check if the symbol exists
    TableEntryValue retrieved_val = get_symbol_from_stack_by_key("x");
    if (retrieved_val.symbol_nature == SYMBOL_NATURE_IDENTIFIER) {
        printf("Test case 1 passed.\n");
    } else {
        printf("Test case 1 failed.\n");
    }

    // Free the table stack
    free_table_stack(globalTableStack);
}

void test_symbol_declaration() {
    printf("Testing symbol declaration...\n");

    // Initialize the global symbol stack
    init_global_symbol_stack();

    // Create valor_lexico examples
    Valor_lexico lex_val1 = createValor_lexico("x", IDENTIFIER, 1);
    TableEntryValue entry_val1 = create_table_entry_value(SYMBOL_NATURE_IDENTIFIER, DATA_TYPE_INT, lex_val1);

    // Add the symbol to the global table stack
    add_symbol_value_to_global_table_stack(entry_val1);

    // Attempt to add the same symbol again and catch the error
    if (setjmp(env) == 0) {
        add_symbol_value_to_global_table_stack(entry_val1);
        printf("Test case 1 failed.\n");
    } else {
        if (errno == ERR_DECLARED) {
            printf("Test case 1 passed.\n");
        } else {
            printf("Test case 1 failed with unexpected error code %d.\n", errno);
        }
    }

    // Free the table stack
    free_table_stack(globalTableStack);
}

void test_print_valor_lexico() {
    printf("Testing printValor_lexico function...\n");

    Valor_lexico lex_val = createValor_lexico("example", IDENTIFIER, 42);
    printValor_lexico(lex_val);
    freeValor_lexico(lex_val);
}
