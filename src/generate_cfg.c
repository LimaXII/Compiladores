#include "generate_cfg.h"

// Função auxiliar para verificar se uma instrução é líder de bloco básico
int is_leader(AsmCodeList* instr) {
    if (instr == NULL) return 0;

    switch (instr->asm_code.opcode) {
        case OP_CBR:
        case OP_JUMPI:
        case OP_LABEL:
        case OP_RETURN:
            return 1;
        default:
            return 0;
    }
}

void generate_cfg_dot(AsmCodeList* asm_code_list) {
    // Impressão do início do gráfico DOT
    printf("digraph CFG {\n");

    AsmCodeList* current = asm_code_list;
    int block_id = 0;
    int prev_block_id = -1;

    while (current != NULL) {
        // Verifica se a instrução é líder
        if (is_leader(current)) {
            if (block_id > 0) {
                printf("\"Block%d\" -> \"Block%d\";\n", prev_block_id, block_id);
            }
            printf("subgraph cluster_%d {\n", block_id);
            printf("label=\"Block %d\";\n", block_id);
            prev_block_id = block_id;
            block_id++;
        }

        printf("\"%p\" [label=\"", (void*)current);
        printf("%d: ", prev_block_id);

        // Imprimir a instrução com base no opcode
        switch (current->asm_code.opcode) {
            case OP_NOP:
                printf("\tnop\n");
                break;
            case OP_ADD:
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t1, "%rip", "%eax");
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t2, "%rip", "%edx");
                printf("\taddl    %s, %s \n", "%edx", "%eax");
                printf("\tmovl    %s, _temp_r_%d(%s) \n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_SUB:
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t1, "%rip", "%eax");
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t2, "%rip", "%edx");
                printf("\tsubl    %s, %s \n", "%edx", "%eax");
                printf("\tmovl    %s, _temp_r_%d(%s) \n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_MULT:
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t1, "%rip", "%eax");
                printf("\timull   _temp_r_%d(%s), %s \n", current->asm_code.t2, "%rip", "%eax");
                printf("\tmovl    %s, _temp_r_%d(%s) \n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_DIV:
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t1, "%rip", "%eax");
                printf("\tcdq \n");
                printf("\tidivl   _temp_r_%d(%s)\n", current->asm_code.t2, "%rip");
                printf("\tmovl    %s, _temp_r_%d(%s) \n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_NEG:
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t1, "%rip", "%eax");
                printf("\tnegl    %s \n", "%eax");
                printf("\tmovl    %s, _temp_r_%d(%s) \n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_NEG_LOG:
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t1, "%rip", "%eax");
                printf("\ttest    %s, %s\n", "%eax", "%eax");
                printf("\tmovl    $0, %s\n", "%eax");
                printf("\tsete    %s\n", "%al");
                printf("\tmovl    %s, _temp_r_%d(%s)\n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_AND:
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t1, "%rip", "%eax");
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t2, "%rip", "%edx");
                printf("\ttest    %s, %s\n", "%eax", "%edx");
                printf("\tmovl    $0, %s\n", "%eax");
                printf("\tsetne    %s\n", "%al");
                printf("\tmovl    %s, _temp_r_%d(%s)\n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_OR:
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t1, "%rip", "%eax");
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t2, "%rip", "%edx");
                printf("\tor      %s, %s\n", "%eax", "%edx");
                printf("\tmovl    $0, %s\n", "%eax");
                printf("\tsetne    %s\n", "%al");
                printf("\tmovl    %s, _temp_r_%d(%s)\n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_CMP_EQ:
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t1, "%rip", "%eax");
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t2, "%rip", "%edx");
                printf("\tcmp     %s, %s\n", "%edx", "%eax");
                printf("\tmovl    $0, %s\n", "%eax");
                printf("\tsete    %s\n", "%al");
                printf("\tmovl    %s, _temp_r_%d(%s)\n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_CMP_NE:
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t1, "%rip", "%eax");
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t2, "%rip", "%edx");
                printf("\tcmp     %s, %s\n", "%edx", "%eax");
                printf("\tmovl    $0, %s\n", "%eax");
                printf("\tsetne   %s\n", "%al");
                printf("\tmovl    %s, _temp_r_%d(%s)\n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_CMP_GT:
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t1, "%rip", "%eax");
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t2, "%rip", "%edx");
                printf("\tcmp      %s, %s\n", "%edx", "%eax");
                printf("\tmovl    $0, %s\n", "%eax");
                printf("\tsetg    %s\n", "%al");
                printf("\tmovl    %s, _temp_r_%d(%s)\n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_CMP_LT:
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t1, "%rip", "%eax");
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t2, "%rip", "%edx");
                printf("\tcmp      %s, %s\n", "%edx", "%eax");
                printf("\tmovl    $0, %s\n", "%eax");
                printf("\tsetl    %s\n", "%al");
                printf("\tmovl    %s, _temp_r_%d(%s)\n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_CMP_GE:
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t1, "%rip", "%eax");
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t2, "%rip", "%edx");
                printf("\tcmp      %s, %s\n", "%edx", "%eax");
                printf("\tmovl    $0, %s\n", "%eax");
                printf("\tsetge    %s\n", "%al");
                printf("\tmovl    %s, _temp_r_%d(%s)\n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_CMP_LE:
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t1, "%rip", "%eax");
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t2, "%rip", "%edx");
                printf("\tcmp      %s, %s\n", "%edx", "%eax");
                printf("\tmovl    $0, %s\n", "%eax");
                printf("\tsetle    %s\n", "%al");
                printf("\tmovl    %s, _temp_r_%d(%s)\n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_CBR:
                printf("\tmovl    _temp_r_%d(%s), %s \n", current->asm_code.t1, "%rip", "%eax");
                printf("\ttest    %s, %s\n", "%eax", "%eax"); // eax AND eax
                printf("\tjnz  l%d\n", current->asm_code.t3);
                printf("\tjz  l%d\n", current->asm_code.t4);
                break;
            case OP_JUMPI:
                printf("\tjmp l%d\n", current->asm_code.t1);
                break;
            case OP_LOADI:
                printf("\tmovl $%d, _temp_r_%d(%s)\n", current->asm_code.t1, current->asm_code.t3, "%rip");
                break;
            case OP_LOADAI_GLOBAL:
                printf("\tmovl global%d(%s), %s\n"      , current->asm_code.t1/4   , "%rip"            , "%edx");
                printf("\tmovl %s, _temp_r_%d(%s)\n"    , "%edx"            , current->asm_code.t3    , "%rip");
                break;
            case OP_LOADAI_LOCAL:
                printf("\tmovl -%d(%s), %s\n"           , current->asm_code.t1     , "%rbp"            , "%edx");
                printf("\tmovl %s, _temp_r_%d(%s)\n"    , "%edx"            , current->asm_code.t3    , "%rip");
                break;
            case OP_STOREAI_GLOBAL:
                printf("\tmovl _temp_r_%d(%s), %s\n"    , current->asm_code.t1     , "%rip"            , "%edx");
                printf("\tmovl %s, global%d(%s)\n"      , "%edx"            , current->asm_code.t3 / 4, "%rip");
                break;
            case OP_STOREAI_LOCAL:
                printf("\tmovl _temp_r_%d(%s), %s\n"    , current->asm_code.t1     , "%rip"            , "%edx");
                printf("\tmovl %s, -%d(%s)\n"            , "%edx"            , current->asm_code.t3   , "%rbp");
                break;
            case OP_LABEL:
                printf("l%d: \n", current->asm_code.t1);
                break;
            case OP_RETURN:
                printf("\tmovl _temp_r_%d(%s), %s\n", current->asm_code.t1, "%rip", "%eax");
                printf("\tpopq %s\n", "%rbp");
                printf("\tret\n");
                break;
            default:
                printf("Instrução desconhecida.\n");
                break;
        }

        printf("\"];\n");

        if (current->next == NULL) {
            printf("}\n");
        }

        current = current->next;
    }

    // Impressão do final do gráfico DOT
    printf("}\n");
}
