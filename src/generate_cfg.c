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
    int line_number=1;

    // Criação do primeiro bloco com as instruções padrão
    printf("\tsubgraph cluster_%d {\n", block_id);
    printf("\t\tlabel=\"Block %d\";\n", block_id);
    printf("\t\t\"init_block\" [label=\"%d: pushq   %%rbp\\n%d: movq    %%rsp, %%rbp\\n\"];\n", line_number, line_number+1);
    prev_block_id = block_id;
    block_id++;
    line_number = line_number + 2;

    while (current != NULL) {
        // Verifica se a instrução é líder
        if (is_leader(current)) {
            printf("\t\t\"Block%d\" -> \"Block%d\";\n\t}\n", prev_block_id, block_id);
            printf("\tsubgraph cluster_%d {\n", block_id);
            printf("\t\tlabel=\"Block %d\";\n", block_id);
            prev_block_id = block_id;
            block_id++;
        }

        printf("\t\t\"%p\" [label=\"", (void*)current);

        // Imprimir a instrução com base no opcode
        switch (current->asm_code.opcode) {
            case OP_NOP:
                printf("nop\\n");
                break;
            case OP_ADD:
                printf("movl    _temp_r_%d(%s), %s\\n", current->asm_code.t1, "%rip", "%eax");
                printf("movl    _temp_r_%d(%s), %s\\n", current->asm_code.t2, "%rip", "%edx");
                printf("addl    %s, %s\\n", "%edx", "%eax");
                printf("movl    %s, _temp_r_%d(%s)\\n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_SUB:
                printf("movl    _temp_r_%d(%s), %s\\n", current->asm_code.t1, "%rip", "%eax");
                printf("movl    _temp_r_%d(%s), %s\\n", current->asm_code.t2, "%rip", "%edx");
                printf("subl    %s, %s\\n", "%edx", "%eax");
                printf("movl    %s, _temp_r_%d(%s)\\n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_MULT:
                printf("movl    _temp_r_%d(%s), %s\\n", current->asm_code.t1, "%rip", "%eax");
                printf("imull   _temp_r_%d(%s), %s\\n", current->asm_code.t2, "%rip", "%eax");
                printf("movl    %s, _temp_r_%d(%s)\\n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_DIV:
                printf("movl    _temp_r_%d(%s), %s\\n", current->asm_code.t1, "%rip", "%eax");
                printf("cdq\\n");
                printf("idivl   _temp_r_%d(%s)\\n", current->asm_code.t2, "%rip");
                printf("movl    %s, _temp_r_%d(%s)\\n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_NEG:
                printf("movl    _temp_r_%d(%s), %s\\n", current->asm_code.t1, "%rip", "%eax");
                printf("negl    %s\\n", "%eax");
                printf("movl    %s, _temp_r_%d(%s)\\n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_NEG_LOG:
                printf("movl    _temp_r_%d(%s), %s\\n", current->asm_code.t1, "%rip", "%eax");
                printf("test    %s, %s\\n", "%eax", "%eax");
                printf("movl    $0, %s\\n", "%eax");
                printf("sete    %s\\n", "%al");
                printf("movl    %s, _temp_r_%d(%s)\\n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_AND:
                printf("movl    _temp_r_%d(%s), %s\\n", current->asm_code.t1, "%rip", "%eax");
                printf("movl    _temp_r_%d(%s), %s\\n", current->asm_code.t2, "%rip", "%edx");
                printf("test    %s, %s\\n", "%eax", "%edx");
                printf("movl    $0, %s\\n", "%eax");
                printf("setne    %s\\n", "%al");
                printf("movl    %s, _temp_r_%d(%s)\\n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_OR:
                printf("movl    _temp_r_%d(%s), %s\\n", current->asm_code.t1, "%rip", "%eax");
                printf("movl    _temp_r_%d(%s), %s\\n", current->asm_code.t2, "%rip", "%edx");
                printf("or      %s, %s\\n", "%eax", "%edx");
                printf("movl    $0, %s\\n", "%eax");
                printf("setne    %s\\n", "%al");
                printf("movl    %s, _temp_r_%d(%s)\\n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_CMP_EQ:
                printf("movl    _temp_r_%d(%s), %s\\n", current->asm_code.t1, "%rip", "%eax");
                printf("movl    _temp_r_%d(%s), %s\\n", current->asm_code.t2, "%rip", "%edx");
                printf("cmp     %s, %s\\n", "%edx", "%eax");
                printf("movl    $0, %s\\n", "%eax");
                printf("sete    %s\\n", "%al");
                printf("movl    %s, _temp_r_%d(%s)\\n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_CMP_NE:
                printf("movl    _temp_r_%d(%s), %s\\n", current->asm_code.t1, "%rip", "%eax");
                printf("movl    _temp_r_%d(%s), %s\\n", current->asm_code.t2, "%rip", "%edx");
                printf("cmp     %s, %s\\n", "%edx", "%eax");
                printf("movl    $0, %s\\n", "%eax");
                printf("setne   %s\\n", "%al");
                printf("movl    %s, _temp_r_%d(%s)\\n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_CMP_GT:
                printf("movl    _temp_r_%d(%s), %s\\n", current->asm_code.t1, "%rip", "%eax");
                printf("movl    _temp_r_%d(%s), %s\\n", current->asm_code.t2, "%rip", "%edx");
                printf("cmp      %s, %s\\n", "%edx", "%eax");
                printf("movl    $0, %s\\n", "%eax");
                printf("setg    %s\\n", "%al");
                printf("movl    %s, _temp_r_%d(%s)", "%eax\\n", current->asm_code.t3, "%rip");
                break;
            case OP_CMP_LT:
                printf("movl    _temp_r_%d(%s), %s\\n", current->asm_code.t1, "%rip", "%eax");
                printf("movl    _temp_r_%d(%s), %s\\n", current->asm_code.t2, "%rip", "%edx");
                printf("cmp      %s, %s\\n", "%edx", "%eax");
                printf("movl    $0, %s\\n", "%eax");
                printf("setl    %s\\n", "%al");
                printf("movl    %s, _temp_r_%d(%s)\\n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_CMP_GE:
                printf("movl    _temp_r_%d(%s), %s\\n", current->asm_code.t1, "%rip", "%eax");
                printf("movl    _temp_r_%d(%s), %s\\n", current->asm_code.t2, "%rip", "%edx");
                printf("cmp      %s, %s\\n", "%edx", "%eax");
                printf("movl    $0, %s\\n", "%eax");
                printf("setge    %s\\n", "%al");
                printf("movl    %s, _temp_r_%d(%s)\\n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_CMP_LE:
                printf("movl    _temp_r_%d(%s), %s\\n", current->asm_code.t1, "%rip", "%eax");
                printf("movl    _temp_r_%d(%s), %s\\n", current->asm_code.t2, "%rip", "%edx");
                printf("cmp      %s, %s\\n", "%edx", "%eax");
                printf("movl    $0, %s\\n", "%eax");
                printf("setle    %s\\n", "%al");
                printf("movl    %s, _temp_r_%d(%s)\\n", "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_CBR:
                printf("movl    _temp_r_%d(%s), %s \\n", current->asm_code.t1, "%rip", "%eax");
                printf("test    %s, %s\\n", "%eax", "%eax"); // eax AND eax
                printf("jnz  l%d\\n", current->asm_code.t3);
                printf("jz  l%d\\n", current->asm_code.t4);
                break;
            case OP_JUMPI:
                printf("jmp l%d\\n", current->asm_code.t1);
                break;
            case OP_LOADI:
                printf("movl $%d, _temp_r_%d(%s)\\n", current->asm_code.t1, current->asm_code.t3, "%rip");
                break;
            case OP_LOADAI_GLOBAL:
                printf("movl global%d(%s), %s\\n"      , current->asm_code.t1/4   , "%rip"            , "%edx");
                printf("movl %s, _temp_r_%d(%s)\\n"    , "%edx"            , current->asm_code.t3    , "%rip");
                break;
            case OP_LOADAI_LOCAL:
                printf("movl -%d(%s), %s\\n"           , current->asm_code.t1     , "%rbp"            , "%edx");
                printf("movl %s, _temp_r_%d(%s)\\n"    , "%edx"            , current->asm_code.t3    , "%rip");
                break;
            case OP_STOREAI_GLOBAL:
                printf("movl _temp_r_%d(%s), %s\\n"    , current->asm_code.t1     , "%rip"            , "%edx");
                printf("movl %s, global%d(%s)\\n"      , "%edx"            , current->asm_code.t3 / 4, "%rip");
                break;
            case OP_STOREAI_LOCAL:
                printf("movl _temp_r_%d(%s), %s\\n"    , current->asm_code.t1     , "%rip"            , "%edx");
                printf("movl %s, -%d(%s)\\n"            , "%edx"            , current->asm_code.t3   , "%rbp");
                break;
            case OP_LABEL:
                printf("l%d: \\n", current->asm_code.t1);
                break;
            case OP_RETURN:
                printf("movl _temp_r_%d(%s), %s\\n", current->asm_code.t1, "%rip", "%eax");
                printf("popq %s\\n", "%rbp");
                printf("ret\\n");
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
