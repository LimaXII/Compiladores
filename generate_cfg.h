#ifndef CFG_H
#define CFG_H

#include <stdio.h>
#include <stdlib.h>
#include "iloc.h"


// Função para identificar se uma instrução é líder
int is_leader(IlocCodeList* instr);

// Função para gerar o grafo de controle de fluxo no formato DOT
void generate_cfg_dot(IlocCodeList* iloc_code);

#endif // CFG_H
