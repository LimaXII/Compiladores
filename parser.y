/* ======= GRUPO J ======= */
/* Luccas da Silva Lima 00324683 */
/* Matheus Almeida da Silva 00316326 */

%{
#include <stdio.h>
// Importa as funções necessárias.
int get_line_number();
int yylex(void);
void yyerror (char const *message);
%}

%define parse.error verbose

%token TK_PR_INT
%token TK_PR_FLOAT
%token TK_PR_BOOL
%token TK_PR_IF
%token TK_PR_ELSE
%token TK_PR_WHILE
%token TK_PR_RETURN
%token TK_OC_LE
%token TK_OC_GE
%token TK_OC_EQ
%token TK_OC_NE
%token TK_OC_AND
%token TK_OC_OR
%token TK_IDENTIFICADOR
%token TK_LIT_INT
%token TK_LIT_FLOAT
%token TK_LIT_FALSE
%token TK_LIT_TRUE
%token TK_ERRO

%%

// -- Programa -- 
program: elements_list | ; // Contendo uma lista de elementos ou vazio.
elements_list: elements_list element | element;
element: global_vars_declaration | function; // Elemento: Sendo uma declaração global ou uma definição de função.

// -- Declaração de Variáveis Globais -- 
global_vars_declaration: type ident_list ',';
ident_list: ident_list ';' TK_IDENTIFICADOR | TK_IDENTIFICADOR;

// -- Funções --
function: header body;
// Cabeçalho da função. Podendo conter uma lista de parametros ou nenhum parametro.
header: '(' parameters_list ')' TK_OC_OR type '/' TK_IDENTIFICADOR | '('')' TK_OC_OR type '/' TK_IDENTIFICADOR;
parameters_list: parameters_list ';' parameter | parameter;
parameter: type TK_IDENTIFICADOR;
// Corpo da função. Contendo um bloco de comandos.
body: command_block;
command_block: '{' simple_command_list '}' | '{''}';
simple_command_list: simple_command_list command | command;

// -- Comandos Simples --
command: command_block ',' | global_vars_declaration | attribution_command ',' | function_call ',' | return_command ',' | control_command ',';
attribution_command: TK_IDENTIFICADOR '=' expression;
function_call: TK_IDENTIFICADOR '(' arguments ')' | TK_IDENTIFICADOR '('')';
return_command: TK_PR_RETURN expression;
control_command: TK_PR_IF '(' expression ')' command_block | TK_PR_IF '(' expression ')' command_block TK_PR_ELSE command_block | TK_PR_WHILE '(' expression ')' command_block;
arguments: arguments ';' expression | expression;

// -- Expressões -- 
expression: expression7;
// Grau 7 de precedencia das expressões. Pode ser um OR ou uma expressão mais prioritária.
expression7: expression7 TK_OC_OR expression6 | expression6;
// Grau 6 de precedencia. Pode ser um AND ou uma expressão mais prioritária.
expression6: expression6 TK_OC_AND expression5 | expression5;
// Grau 5 de precedencia. Pode ser um EQUAL ou um NOT EQUAL ou uma expressão mais prioritária.
expression5: expression5 TK_OC_EQ expression4 | expression5 TK_OC_NE expression4 | expression4;
// Grau 4 de precedencia. Pode ser um < ou um > ou um LessEqual ou um GreaterEqual ou uma expressão mais prioritária.
expression4: expression4 TK_OC_LE expression3 | expression4 TK_OC_GE expression3 | expression4 '<' expression3 | expression4 '>' expression3 | expression3;
// Grau 3 de precedencia. Pode ser uma adição ou uma subtração ou uma expressão mais prioritária.
expression3: expression3 '+' expression2 | expression3 '-' expression2 | expression2;
// Grau 2 de precedencia. Pode ser uma * ou / ou % ou uma expressão mais prioritária.
expression2: expression2 '*' expression1 | expression2 '/' expression1 | expression2 '%' expression1 | expression1;
expression1: '!' expression0 |'-' expression0 | expression0;

expression0: operands | '(' expression ')';
operands: TK_IDENTIFICADOR | literal | function_call;

// -- Tipos --
type: TK_PR_INT | TK_PR_FLOAT | TK_PR_BOOL;

// -- Literais --
literal: TK_LIT_INT | TK_LIT_FLOAT | TK_LIT_TRUE | TK_LIT_FALSE;
%%

// Função que imprime na tela o erro encontrado.
void yyerror(char const *message)
{
    printf("Erro encontrado na linha %d: %s\n", get_line_number(), message);
}
