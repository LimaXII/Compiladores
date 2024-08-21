#ifndef CFG_H
#define CFG_H

#include <stdio.h>
#include <stdlib.h>
#include "asm.h"


// Função para identificar se uma instrução é líder
int is_leader(AsmCodeList* instr);

// Função para gerar o grafo de controle de fluxo no formato DOT
void generate_cfg_dot(AsmCodeList* asm_code_list);

#endif // CFG_H
