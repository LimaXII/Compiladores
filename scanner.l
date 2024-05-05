/* ======= GRUPO J ======= */
/* Luccas da Silva Lima 00324683 */
/* Matheus Almeida da Silva 00316326 */

%{
    #include <stdio.h>
    #include "valor_lexico.h"
    #include "ast_tree.h"
    #include "parser.tab.h"

    #define YYSTYPE Valor_lexico
%}

%option noyywrap
/* Necessário para contar as linhas. */
%option yylineno
/* Estado especial para lidar com comentários multi-linha. */
%s comment
/* Expressão regular para detectar qualquer caractere especial. */
special_char [-!*/%+<>{}()=,;] 
/* Expressão regular para detectar espaço em branco. */
whitespace [ \t\n\r]

%%
"int" { return TK_PR_INT; }
"float" { return TK_PR_FLOAT; }
"bool" { return TK_PR_BOOL; }
"true" { yylval.valor_lexico = createValor_lexico(yytext, LITERAL, yylineno); return TK_LIT_TRUE; }
"false" { yylval.valor_lexico = createValor_lexico(yytext, LITERAL, yylineno); return TK_LIT_FALSE; }
"if" { yylval.ast_token_val = strndup(yytext, 2); return TK_PR_IF; }
"else" { return TK_PR_ELSE; }
"while" { yylval.ast_token_val = strndup(yytext, 5); return TK_PR_WHILE; }
"return" { yylval.ast_token_val = strndup(yytext, 6); return TK_PR_RETURN; }
"<=" { yylval.ast_token_val = strndup(yytext, 2); return TK_OC_LE; }
">=" { yylval.ast_token_val = strndup(yytext, 2); return TK_OC_GE; }
"==" { yylval.ast_token_val = strndup(yytext, 2); return TK_OC_EQ; }
"!=" { yylval.ast_token_val = strndup(yytext, 2); return TK_OC_NE; }
"&" { yylval.ast_token_val = strndup(yytext, 1); return TK_OC_AND; }
"|" { yylval.ast_token_val = strndup(yytext, 1); return TK_OC_OR; }
{special_char}  { yylval.ast_token_val = strndup(yytext, 1); return yytext[0]; }

[a-z_]+[a-z_0-9]* { yylval.valor_lexico = createValor_lexico(yytext, IDENTIFIER, yylineno); return TK_IDENTIFICADOR; } 
[0-9]+ { yylval.valor_lexico = createValor_lexico(yytext, LITERAL, yylineno); return TK_LIT_INT; }
[0-9]*"."[0-9]+ { yylval.valor_lexico = createValor_lexico(yytext, LITERAL, yylineno); return TK_LIT_FLOAT; }


"//".* { }

"/*"         { BEGIN(comment); }
<comment>[^*\n]*        { }
<comment>[^*\n]*\n      { }
<comment>"*"+[^*/\n]*   { }
<comment>"*"+[^*/\n]*\n { }
<comment>"*"+"/"        { BEGIN(INITIAL); }

{whitespace} { }
{special_char}  {return yytext[0];}

. {return TK_ERRO;}
%%

// Função para retornar a linha atual.
int get_line_number(void) {
    return yylineno;
}