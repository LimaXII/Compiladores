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
    int first_block = 1;

    while (current != NULL) {
        // Verifica se a instrução é líder
        if (is_leader(current) || first_block) {
            if (!first_block) {
                printf("\t\t\"Block%d\" -> \"Block%d\";\n\t}\n", prev_block_id, block_id);
            }
            printf("\tsubgraph cluster_%d {\n", block_id);
            printf("\t\tlabel=\"Block %d\";\n", block_id);
            prev_block_id = block_id;
            block_id++;
            first_block = 0;
        }

        printf("\t\t\"%p\" [label=\"", (void*)current);
        printf("%d: ", prev_block_id);

        // Imprimir a instrução com base no opcode
        switch (current->asm_code.opcode) {
            case OP_NOP:
                printf("nop");
                break;
            case OP_ADD:
                printf("movl    _temp_r_%d(%s), %s ", current->asm_code.t1, "%rip", "%eax");
                printf("movl    _temp_r_%d(%s), %s ", current->asm_code.t2, "%rip", "%edx");
                printf("addl    %s, %s ", "%edx", "%eax");
                printf("movl    %s, _temp_r_%d(%s) ", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_SUB:
                printf("movl    _temp_r_%d(%s), %s ", current->asm_code.t1, "%rip", "%eax");
                printf("movl    _temp_r_%d(%s), %s ", current->asm_code.t2, "%rip", "%edx");
                printf("subl    %s, %s ", "%edx", "%eax");
                printf("movl    %s, _temp_r_%d(%s) ", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_MULT:
                printf("movl    _temp_r_%d(%s), %s ", current->asm_code.t1, "%rip", "%eax");
                printf("imull   _temp_r_%d(%s), %s ", current->asm_code.t2, "%rip", "%eax");
                printf("movl    %s, _temp_r_%d(%s) ", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_DIV:
                printf("movl    _temp_r_%d(%s), %s ", current->asm_code.t1, "%rip", "%eax");
                printf("cdq ");
                printf("idivl   _temp_r_%d(%s)", current->asm_code.t2, "%rip");
                printf("movl    %s, _temp_r_%d(%s) ", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_NEG:
                printf("movl    _temp_r_%d(%s), %s ", current->asm_code.t1, "%rip", "%eax");
                printf("negl    %s ", "%eax");
                printf("movl    %s, _temp_r_%d(%s) ", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_NEG_LOG:
                printf("movl    _temp_r_%d(%s), %s ", current->asm_code.t1, "%rip", "%eax");
                printf("test    %s, %s", "%eax", "%eax");
                printf("movl    $0, %s", "%eax");
                printf("sete    %s", "%al");
                printf("movl    %s, _temp_r_%d(%s)", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_AND:
                printf("movl    _temp_r_%d(%s), %s ", current->asm_code.t1, "%rip", "%eax");
                printf("movl    _temp_r_%d(%s), %s ", current->asm_code.t2, "%rip", "%edx");
                printf("test    %s, %s", "%eax", "%edx");
                printf("movl    $0, %s", "%eax");
                printf("setne    %s", "%al");
                printf("movl    %s, _temp_r_%d(%s)", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_OR:
                printf("movl    _temp_r_%d(%s), %s ", current->asm_code.t1, "%rip", "%eax");
                printf("movl    _temp_r_%d(%s), %s ", current->asm_code.t2, "%rip", "%edx");
                printf("or      %s, %s", "%eax", "%edx");
                printf("movl    $0, %s", "%eax");
                printf("setne    %s", "%al");
                printf("movl    %s, _temp_r_%d(%s)", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_CMP_EQ:
                printf("movl    _temp_r_%d(%s), %s ", current->asm_code.t1, "%rip", "%eax");
                printf("movl    _temp_r_%d(%s), %s ", current->asm_code.t2, "%rip", "%edx");
                printf("cmp     %s, %s", "%edx", "%eax");
                printf("movl    $0, %s", "%eax");
                printf("sete    %s", "%al");
                printf("movl    %s, _temp_r_%d(%s)", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_CMP_NE:
                printf("movl    _temp_r_%d(%s), %s ", current->asm_code.t1, "%rip", "%eax");
                printf("movl    _temp_r_%d(%s), %s ", current->asm_code.t2, "%rip", "%edx");
                printf("cmp     %s, %s", "%edx", "%eax");
                printf("movl    $0, %s", "%eax");
                printf("setne   %s", "%al");
                printf("movl    %s, _temp_r_%d(%s)", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_CMP_GT:
                printf("movl    _temp_r_%d(%s), %s ", current->asm_code.t1, "%rip", "%eax");
                printf("movl    _temp_r_%d(%s), %s ", current->asm_code.t2, "%rip", "%edx");
                printf("cmp      %s, %s", "%edx", "%eax");
                printf("movl    $0, %s", "%eax");
                printf("setg    %s", "%al");
                printf("movl    %s, _temp_r_%d(%s)", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_CMP_LT:
                printf("movl    _temp_r_%d(%s), %s ", current->asm_code.t1, "%rip", "%eax");
                printf("movl    _temp_r_%d(%s), %s ", current->asm_code.t2, "%rip", "%edx");
                printf("cmp      %s, %s", "%edx", "%eax");
                printf("movl    $0, %s", "%eax");
                printf("setl    %s", "%al");
                printf("movl    %s, _temp_r_%d(%s)", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_CMP_GE:
                printf("movl    _temp_r_%d(%s), %s ", current->asm_code.t1, "%rip", "%eax");
                printf("movl    _temp_r_%d(%s), %s ", current->asm_code.t2, "%rip", "%edx");
                printf("cmp      %s, %s", "%edx", "%eax");
                printf("movl    $0, %s", "%eax");
                printf("setge    %s", "%al");
                printf("movl    %s, _temp_r_%d(%s)", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_CMP_LE:
                printf("movl    _temp_r_%d(%s), %s ", current->asm_code.t1, "%rip", "%eax");
                printf("movl    _temp_r_%d(%s), %s ", current->asm_code.t2, "%rip", "%edx");
                printf("cmp      %s, %s", "%edx", "%eax");
                printf("movl    $0, %s", "%eax");
                printf("setle    %s", "%al");
                printf("movl    %s, _temp_r_%d(%s)", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_CBR:
                printf("movl    _temp_r_%d(%s), %s ", current->asm_code.t1, "%rip", "%eax");
                printf("test    %s, %s", "%eax", "%eax"); // eax AND eax
                printf("jnz  l%d", current->asm_code.t3);
                printf("jz  l%d", current->asm_code.t4);
                break;
            case OP_JUMPI:
                printf("jmp l%d", current->asm_code.t1);
                break;
            case OP_LOADI:
                printf("movl $%d, _temp_r_%d(%s)", current->asm_code.t1, current->asm_code.t3, "%rip");
                break;
            case OP_LOADAI_GLOBAL:
                printf("movl global%d(%s), %s"      , current->asm_code.t1/4   , "%rip"            , "%edx");
                printf("movl %s, _temp_r_%d(%s)"    , "%edx"            , current->asm_code.t3    , "%rip");
                break;
            case OP_LOADAI_LOCAL:
                printf("movl -%d(%s), %s"           , current->asm_code.t1     , "%rbp"            , "%edx");
                printf("movl %s, _temp_r_%d(%s)"    , "%edx"            , current->asm_code.t3    , "%rip");
                break;
            case OP_STOREAI_GLOBAL:
                printf("movl _temp_r_%d(%s), %s"    , current->asm_code.t1     , "%rip"            , "%edx");
                printf("movl %s, global%d(%s)"      , "%edx"            , current->asm_code.t3 / 4, "%rip");
                break;
            case OP_STOREAI_LOCAL:
                printf("movl _temp_r_%d(%s), %s"    , current->asm_code.t1     , "%rip"            , "%edx");
                printf("movl %s, -%d(%s)"            , "%edx"            , current->asm_code.t3   , "%rbp");
                break;
            case OP_LABEL:
                printf("l%d: ", current->asm_code.t1);
                break;
            case OP_RETURN:
                printf("movl _temp_r_%d(%s), %s", current->asm_code.t1, "%rip", "%eax");
                printf("popq %s", "%rbp");
                printf("ret");
                break;
            default:
                printf("Instrução desconhecida.");
                break;
        }

        printf("\"];\n");

        if (current->next == NULL) {
            printf("\t}\n");
        }

        current = current->next;
    }

    // Impressão do final do gráfico DOT
    printf("}\n");
}
