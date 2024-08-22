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
    printf("\t\t\"init_block\" [label=\"%d: pushq   %%rbp\\n", line_number);
    printf("%d: movq    %%rsp, %%rbp\\n\"];\n", ++line_number);
    prev_block_id = block_id;
    block_id++;

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
                printf("%d: nop\\n", ++line_number);
                break;
            case OP_ADD:
                printf("%d: movl    _temp_r_%d(%s), %s\\n", ++line_number, current->asm_code.t1, "%rip", "%eax");
                printf("%d: movl    _temp_r_%d(%s), %s\\n", ++line_number, current->asm_code.t2, "%rip", "%edx");
                printf("%d: addl    %s, %s\\n", ++line_number, "%edx", "%eax");
                printf("%d: movl    %s, _temp_r_%d(%s)\\n", ++line_number, "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_SUB:
                printf("%d: movl    _temp_r_%d(%s), %s\\n", ++line_number, current->asm_code.t1, "%rip", "%eax");
                printf("%d: movl    _temp_r_%d(%s), %s\\n", ++line_number, current->asm_code.t2, "%rip", "%edx");
                printf("%d: subl    %s, %s\\n", ++line_number, "%edx", "%eax");
                printf("%d: movl    %s, _temp_r_%d(%s)\\n", ++line_number, "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_MULT:
                printf("%d: movl    _temp_r_%d(%s), %s\\n", ++line_number, current->asm_code.t1, "%rip", "%eax");
                printf("%d: imull   _temp_r_%d(%s), %s\\n", ++line_number, current->asm_code.t2, "%rip", "%eax");
                printf("%d: movl    %s, _temp_r_%d(%s)\\n", ++line_number, "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_DIV:
                printf("%d: movl    _temp_r_%d(%s), %s\\n", ++line_number, current->asm_code.t1, "%rip", "%eax");
                printf("%d: cdq\\n", ++line_number);
                printf("%d: idivl   _temp_r_%d(%s)\\n", ++line_number, current->asm_code.t2, "%rip");
                printf("%d: movl    %s, _temp_r_%d(%s)\\n", ++line_number, "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_NEG:
                printf("%d: movl    _temp_r_%d(%s), %s\\n", ++line_number, current->asm_code.t1, "%rip", "%eax");
                printf("%d: negl    %s\\n", ++line_number, "%eax");
                printf("%d: movl    %s, _temp_r_%d(%s)\\n", ++line_number, "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_NEG_LOG:
                printf("%d: movl    _temp_r_%d(%s), %s\\n", ++line_number, current->asm_code.t1, "%rip", "%eax");
                printf("%d: test    %s, %s\\n", ++line_number, "%eax", "%eax");
                printf("%d: movl    $0, %s\\n", ++line_number, "%eax");
                printf("%d: sete    %s\\n", ++line_number, "%al");
                printf("%d: movl    %s, _temp_r_%d(%s)\\n", ++line_number, "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_AND:
                printf("%d: movl    _temp_r_%d(%s), %s\\n", ++line_number, current->asm_code.t1, "%rip", "%eax");
                printf("%d: movl    _temp_r_%d(%s), %s\\n", ++line_number, current->asm_code.t2, "%rip", "%edx");
                printf("%d: test    %s, %s\\n", ++line_number, "%eax", "%edx");
                printf("%d: movl    $0, %s\\n", ++line_number, "%eax");
                printf("%d: setne    %s\\n", ++line_number, "%al");
                printf("%d: movl    %s, _temp_r_%d(%s)\\n", ++line_number, "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_OR:
                printf("%d: movl    _temp_r_%d(%s), %s\\n", ++line_number, current->asm_code.t1, "%rip", "%eax");
                printf("%d: movl    _temp_r_%d(%s), %s\\n", ++line_number, current->asm_code.t2, "%rip", "%edx");
                printf("%d: or      %s, %s\\n", ++line_number, "%eax", "%edx");
                printf("%d: movl    $0, %s\\n", ++line_number, "%eax");
                printf("%d: setne    %s\\n", ++line_number, "%al");
                printf("%d: movl    %s, _temp_r_%d(%s)\\n", ++line_number, "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_CMP_EQ:
                printf("%d: movl    _temp_r_%d(%s), %s\\n", ++line_number, current->asm_code.t1, "%rip", "%eax");
                printf("%d: movl    _temp_r_%d(%s), %s\\n", ++line_number, current->asm_code.t2, "%rip", "%edx");
                printf("%d: cmp     %s, %s\\n", ++line_number, "%edx", "%eax");
                printf("%d: movl    $0, %s\\n", ++line_number, "%eax");
                printf("%d: sete    %s\\n", ++line_number, "%al");
                printf("%d: movl    %s, _temp_r_%d(%s)\\n", ++line_number, "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_CMP_NE:
                printf("%d: movl    _temp_r_%d(%s), %s\\n", ++line_number, current->asm_code.t1, "%rip", "%eax");
                printf("%d: movl    _temp_r_%d(%s), %s\\n", ++line_number, current->asm_code.t2, "%rip", "%edx");
                printf("%d: cmp     %s, %s\\n", ++line_number, "%edx", "%eax");
                printf("%d: movl    $0, %s\\n", ++line_number, "%eax");
                printf("%d: setne   %s\\n", ++line_number, "%al");
                printf("%d: movl    %s, _temp_r_%d(%s)\\n", ++line_number, "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_CMP_GT:
                printf("%d: movl    _temp_r_%d(%s), %s\\n", ++line_number, current->asm_code.t1, "%rip", "%eax");
                printf("%d: movl    _temp_r_%d(%s), %s\\n", ++line_number, current->asm_code.t2, "%rip", "%edx");
                printf("%d: cmp      %s, %s\\n", ++line_number, "%edx", "%eax");
                printf("%d: movl    $0, %s\\n", ++line_number, "%eax");
                printf("%d: setg    %s\\n", ++line_number, "%al");
                printf("%d: movl    %s, _temp_r_%d(%s)\\n",++line_number, "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_CMP_LT:
                printf("%d: movl    _temp_r_%d(%s), %s\\n", ++line_number, current->asm_code.t1, "%rip", "%eax");
                printf("%d: movl    _temp_r_%d(%s), %s\\n", ++line_number, current->asm_code.t2, "%rip", "%edx");
                printf("%d: cmp      %s, %s\\n", ++line_number, "%edx", "%eax");
                printf("%d: movl    $0, %s\\n", ++line_number, "%eax");
                printf("%d: setl    %s\\n", ++line_number, "%al");
                printf("%d: movl    %s, _temp_r_%d(%s)\\n", ++line_number, "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_CMP_GE:
                printf("%d: movl    _temp_r_%d(%s), %s\\n", ++line_number, current->asm_code.t1, "%rip", "%eax");
                printf("%d: movl    _temp_r_%d(%s), %s\\n", ++line_number, current->asm_code.t2, "%rip", "%edx");
                printf("%d: cmp      %s, %s\\n", ++line_number, "%edx", "%eax");
                printf("%d: movl    $0, %s\\n", ++line_number, "%eax");
                printf("%d: setge    %s\\n", ++line_number, "%al");
                printf("%d: movl    %s, _temp_r_%d(%s)\\n", ++line_number, "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_CMP_LE:
                printf("%d: movl    _temp_r_%d(%s), %s\\n", ++line_number, current->asm_code.t1, "%rip", "%eax");
                printf("%d: movl    _temp_r_%d(%s), %s\\n", ++line_number, current->asm_code.t2, "%rip", "%edx");
                printf("%d: cmp      %s, %s\\n", ++line_number, "%edx", "%eax");
                printf("%d: movl    $0, %s\\n", ++line_number, "%eax");
                printf("%d: setle    %s\\n", ++line_number, "%al");
                printf("%d: movl    %s, _temp_r_%d(%s)\\n", ++line_number, "%eax", current->asm_code.t3, "%rip");
                break;
            case OP_CBR:
                printf("%d: movl    _temp_r_%d(%s), %s \\n", ++line_number, current->asm_code.t1, "%rip", "%eax");
                printf("%d: test    %s, %s\\n", ++line_number, "%eax", "%eax"); // eax AND eax
                printf("%d: jnz  l%d\\n", ++line_number, current->asm_code.t3);
                printf("%d: jz  l%d\\n", ++line_number, current->asm_code.t4);
                break;
            case OP_JUMPI:
                printf("%d: jmp l%d\\n", ++line_number, current->asm_code.t1);
                break;
            case OP_LOADI:
                printf("%d: movl $%d, _temp_r_%d(%s)\\n", ++line_number, current->asm_code.t1, current->asm_code.t3, "%rip");
                break;
            case OP_LOADAI_GLOBAL:
                printf("%d: movl global%d(%s), %s\\n", ++line_number,current->asm_code.t1/4, "%rip", "%edx");
                printf("%d: movl %s, _temp_r_%d(%s)\\n", ++line_number, "%edx", current->asm_code.t3, "%rip");
                break;
            case OP_LOADAI_LOCAL:
                printf("%d: movl -%d(%s), %s\\n", ++line_number, current->asm_code.t1, "%rbp", "%edx");
                printf("%d: movl %s, _temp_r_%d(%s)\\n", ++line_number, "%edx", current->asm_code.t3, "%rip");
                break;
            case OP_STOREAI_GLOBAL:
                printf("%d: movl _temp_r_%d(%s), %s\\n",++line_number, current->asm_code.t1, "%rip", "%edx");
                printf("%d: movl %s, global%d(%s)\\n", ++line_number, "%edx", current->asm_code.t3 / 4, "%rip");
                break;
            case OP_STOREAI_LOCAL:
                printf("%d: movl _temp_r_%d(%s), %s\\n", ++line_number, current->asm_code.t1, "%rip", "%edx");
                printf("%d: movl %s, -%d(%s)\\n", ++line_number,"%edx", current->asm_code.t3, "%rbp");
                break;
            case OP_LABEL:
                printf("%d: l%d: \\n", ++line_number, current->asm_code.t1);
                break;
            case OP_RETURN:
                printf("%d: movl _temp_r_%d(%s), %s\\n", ++line_number, current->asm_code.t1, "%rip", "%eax");
                printf("%d: popq %s\\n", ++line_number, "%rbp");
                printf("%d: ret\\n", ++line_number);
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
