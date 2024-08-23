#include "generate_cfg.h"

// Função auxiliar para verificar se uma instrução é líder de bloco básico
int is_leader(IlocCodeList* instr) {
    if (instr == NULL) return 0;

    switch (instr->iloc_code.opcode) {
        case OP_LABEL:
            return 1;
        default:
            return 0;
    }
}

void generate_cfg_dot(IlocCodeList* iloc_code) {
    printf("digraph CFG {\n");

    IlocCodeList* current = iloc_code;
    int block_id = 0;
    int prev_block_id = -1;
    int line_number = 0;
    int after_jump = 0;

    // Primeiro bloco
    if (current != NULL) {
        printf("\t\"Block%d\" [label=\"", block_id);
        block_id++;
    }

    while (current != NULL) {
        // Verifica se a instrução é líder de bloco básico
        if (is_leader(current) && after_jump) {
            if (prev_block_id != -1) {
                printf("\t\"Block%d\" -> \"Block%d\";\n", prev_block_id, block_id - 1);
            }
            printf("\t\"Block%d\" [label=\"", current->iloc_code.t1);
            prev_block_id = block_id;
            block_id++;
            after_jump = 0;
        }
        else if (is_leader(current) || after_jump) {
            if (prev_block_id != -1) {
                printf("\"];\n"); // Fecha o bloco anterior
                printf("\t\"Block%d\" -> \"Block%d\";\n", prev_block_id, block_id - 1);
            }
            printf("\t\"Block%d\" [label=\"", block_id);
            prev_block_id = block_id;
            block_id++;
            after_jump = 0;
        }

        // Imprimir a instrução com base no opcode
        switch (current->iloc_code.opcode) {
            case OP_NOP:
                printf("%d: nop\\n", ++line_number);
                break;
            case OP_ADD:
                printf("%d: add r%d, r%d => r%d\\n", ++line_number, current->iloc_code.t1, current->iloc_code.t2, current->iloc_code.t3);
                break;
            case OP_SUB:
                printf("%d: sub r%d, r%d => r%d\\n", ++line_number, current->iloc_code.t1, current->iloc_code.t2, current->iloc_code.t3);
                break;
            case OP_MULT:
                printf("%d: mult r%d, r%d => r%d\\n", ++line_number, current->iloc_code.t1, current->iloc_code.t2, current->iloc_code.t3);
                break;
            case OP_DIV:
                printf("%d: div r%d, r%d => r%d\\n", ++line_number, current->iloc_code.t1, current->iloc_code.t2, current->iloc_code.t3);
                break;
            case OP_NEG:
                printf("%d: neg r%d => r%d\\n", ++line_number, current->iloc_code.t1, current->iloc_code.t3);
                break;
            case OP_NEG_LOG:
                printf("%d: lnot r%d => r%d\\n", ++line_number, current->iloc_code.t1, current->iloc_code.t3);
                break;
            case OP_AND:
                printf("%d: and r%d, r%d => r%d\\n", ++line_number, current->iloc_code.t1, current->iloc_code.t2, current->iloc_code.t3);
                break;
            case OP_OR:
                printf("%d: or r%d, r%d => r%d\\n", ++line_number, current->iloc_code.t1, current->iloc_code.t2, current->iloc_code.t3);
                break;
            case OP_CMP_EQ:
                printf("%d: cmp_EQ r%d, r%d => r%d\\n", ++line_number, current->iloc_code.t1, current->iloc_code.t2, current->iloc_code.t3);
                break;
            case OP_CMP_NE:
                printf("%d: cmp_NE r%d, r%d => r%d\\n", ++line_number, current->iloc_code.t1, current->iloc_code.t2, current->iloc_code.t3);
                break;
            case OP_CMP_GT:
                printf("%d: cmp_GT r%d, r%d => r%d\\n", ++line_number, current->iloc_code.t1, current->iloc_code.t2, current->iloc_code.t3);
                break;
            case OP_CMP_LT:
                printf("%d: cmp_LT r%d, r%d => r%d\\n", ++line_number, current->iloc_code.t1, current->iloc_code.t2, current->iloc_code.t3);
                break;
            case OP_CMP_GE:
                printf("%d: cmp_GE r%d, r%d => r%d\\n", ++line_number, current->iloc_code.t1, current->iloc_code.t2, current->iloc_code.t3);
                break;
            case OP_CMP_LE:
                printf("%d: cmp_LE r%d, r%d => r%d\\n", ++line_number, current->iloc_code.t1, current->iloc_code.t2, current->iloc_code.t3);
                break;
            case OP_CBR:
                printf("%d: cbr r%d => L%d, L%d\\n", ++line_number, current->iloc_code.t1, current->iloc_code.t3, current->iloc_code.t4);
                // Conecta o bloco atual aos destinos do CBR
                printf("\"];\n");
                printf("\t\"Block%d\" -> \"Block%d\";\n", prev_block_id, current->iloc_code.t3);
                printf("\t\"Block%d\" -> \"Block%d\";\n", prev_block_id, current->iloc_code.t4);
                after_jump = 1;
                break;
            case OP_JUMPI:
                printf("%d: jumpI -> L%d\\n", ++line_number, current->iloc_code.t1);
                printf("\"];\n");
                // Conecta o bloco atual ao destino do jumpI
                printf("\t\"Block%d\" -> \"Block%d\";\n", prev_block_id, current->iloc_code.t1);
                after_jump = 1;
                break;
            case OP_LOADI:
                printf("%d: loadI %d => r%d\\n", ++line_number, current->iloc_code.t1, current->iloc_code.t3);
                break;
            case OP_LOADAI_GLOBAL:
                printf("%d: loadAI rarp, %d => r%d\\n", ++line_number, current->iloc_code.t1, current->iloc_code.t3);
                break;
            case OP_LOADAI_LOCAL:
                printf("%d: loadAI rbss, %d => r%d\\n", ++line_number, current->iloc_code.t1, current->iloc_code.t3);
                break;
            case OP_STOREAI_GLOBAL:
                printf("%d: storeAI r%d => rbss, %d\\n", ++line_number, current->iloc_code.t1, current->iloc_code.t3);
                break;
            case OP_STOREAI_LOCAL:
                printf("%d: storeAI r%d => rfp, %d\\n", ++line_number, current->iloc_code.t1, current->iloc_code.t3);
                break;
            case OP_LABEL:
                printf("%d: L%d: \\n", ++line_number, current->iloc_code.t1);
                break;
            default:
                printf("Error: Unknown opcode %d\\n", current->iloc_code.opcode);
                break;
        }

        // Última instrução fecha o bloco
        if (current->next == NULL) {
            printf("\"];\n");
        }

        current = current->next;
    }

    // Impressão do final do gráfico DOT
    printf("}\n");
}
