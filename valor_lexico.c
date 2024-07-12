/* ======= GRUPO J ======= */
/* Luccas da Silva Lima 00324683 */
/* Matheus Almeida da Silva 00316326 */

#include "valor_lexico.h"

// Função necessária para criar um Valor_lexico e retorná-lo.
Valor_lexico createValor_lexico(char* token_val, TokenType type, int line_number)
{
    // Dá store nos valores de um 'valor_lexico'
    Valor_lexico valor_lexico;
    valor_lexico.line_number = line_number;
    valor_lexico.type = type;
    valor_lexico.token_val = strdup(token_val); // Copia a string para 'token_val'

    return valor_lexico;
}

// Função necessária para liberar a memória alocada de um token_val.
void freeValor_lexico(Valor_lexico valor_lexico)
{
    if (!valor_lexico.token_val){
        return;
    }
    free(valor_lexico.token_val);
}