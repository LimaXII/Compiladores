#include "../iloc.h"
#include "../ast_tree.h"
#include "../table.h"
#include "../valor_lexico.h"

TableStack* globalTableStack = NULL;

void test_table_entries() {
    initialize_global_stack();

    // Criando e adicionando entradas na tabela de símbolos
    Valor_lexico lex_val1 = createValor_lexico("x", OTHER, 1);
    TableEntry entry1 = create_table_entry(NATURE_IDENTIFIER, TYPE_INT, lex_val1);
    add_entry_to_global_stack(entry1);

    Valor_lexico lex_val2 = createValor_lexico("y", OTHER, 1);
    TableEntry entry2 = create_table_entry(NATURE_IDENTIFIER, TYPE_INT, lex_val2);
    add_entry_to_global_stack(entry2);

    Valor_lexico lex_val3 = createValor_lexico("z", OTHER, 1);
    TableEntry entry3 = create_table_entry(NATURE_IDENTIFIER, TYPE_INT, lex_val3);
    add_entry_to_global_stack(entry3);

    // Exibindo a pilha de tabelas para verificar os offsets
    display_global_stack(1);
}

int main() {
    // Teste das entradas na tabela
    test_table_entries();

    // Criando temporários para armazenar os valores
    int t1 = gen_temp();
    int t2 = gen_temp();
    int t3 = gen_temp();

    // Criando nós de código ILOC para testes usando os valores léxicos da tabela
    Valor_lexico lex_val1 = createValor_lexico("x", OTHER, 1);
    Valor_lexico lex_val2 = createValor_lexico("y", OTHER, 1);
    Valor_lexico lex_val3 = createValor_lexico("z", OTHER, 1);

    // Criando os nós com os valores léxicos correspondentes
    Node* node1 = create_node_valor_lexico(lex_val1, TYPE_INT);
    Node* node2 = create_node_valor_lexico(lex_val2, TYPE_INT);
    Node* node3 = create_node_valor_lexico(lex_val3, TYPE_INT);

    // Obtendo os offsets das variáveis da tabela
    TableEntry entry1 = get_entry_by_key(globalTableStack->table, lex_val1.token_val);
    TableEntry entry2 = get_entry_by_key(globalTableStack->table, lex_val2.token_val);
    TableEntry entry3 = get_entry_by_key(globalTableStack->table, lex_val3.token_val);

    // Adicionando código ILOC para carregar os valores das variáveis nos temporários
    gen_code(&(node1->iloc_code_list), OP_LOADAI_GLOBAL, entry1.offset, 0, t1, 0);
    gen_code(&(node2->iloc_code_list), OP_LOADAI_GLOBAL, entry2.offset, 0, t2, 0);
    gen_code(&(node3->iloc_code_list), OP_LOADAI_GLOBAL, entry3.offset, 0, t3, 0);

    // Concatenando código ILOC dos nós
    Node* root = create_node_valor_lexico(createValor_lexico("root", OTHER, 1), TYPE_PLACEHOLDER);
    root->iloc_code_list = concatenate_code(node1->iloc_code_list, node2->iloc_code_list);
    root->iloc_code_list = concatenate_code(root->iloc_code_list, node3->iloc_code_list);

    // Imprimindo o código ILOC gerado
    printf("Generated ILOC Code for root node:\n");
    print_iloc_code_list(root->iloc_code_list);

    // Limpando a memória
    free_tree(node1);
    free_tree(node2);
    free_tree(node3);
    free_tree(root);

    return 0;
}
