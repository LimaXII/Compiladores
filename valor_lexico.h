/* ======= GRUPO J ======= */
/* Luccas da Silva Lima 00324683 */
/* Matheus Almeida da Silva 00316326 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef VALOR_LEXICO_H
#define VALOR_LEXICO_H

// Define o TokenType enum. Ele pode ser um identificador ou um Literal.
typedef enum TokenType
{
    IDENTIFIER,
    LITERAL,
    OTHER
} TokenType;

// Define o Valor_lexico. 
typedef struct Valor_lexico
{
    int line_number;
    TokenType type;
    char* token_val;
} Valor_lexico;

// Funções implementadas.
Valor_lexico createValor_lexico(char* token_val, TokenType type, int line_number);
void freeValor_lexico(Valor_lexico valor_lexico);
void printValor_lexico(Valor_lexico valor_lexico);

#endif // VALOR_LEXICO_H