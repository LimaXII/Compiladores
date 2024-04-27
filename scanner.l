/* ======= GRUPO J ======= */
/* Luccas da Silva Lima 00324683 */
/* Matheus Almeida da Silva 00316326 */

%{
    #include <stdio.h>
    #include "parser.tab.h"
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
"int" {return TK_PR_INT;}
"float" {return TK_PR_FLOAT;}
"bool" {return TK_PR_BOOL;}
"true" {return TK_LIT_TRUE;}
"false" {return TK_LIT_FALSE;}
"if" {return TK_PR_IF;}
"else" {return TK_PR_ELSE;}
"while" {return TK_PR_WHILE;}
"return" {return TK_PR_RETURN;}
"<=" {return TK_OC_LE;}
">=" {return TK_OC_GE;}
"==" {return TK_OC_EQ;}
"!=" {return TK_OC_NE;}
"&" {return TK_OC_AND;}
"|" {return TK_OC_OR;}

[a-z_]+[a-z_0-9]* {return TK_IDENTIFICADOR;} 
[0-9]+ {return TK_LIT_INT;}
[0-9]*"."[0-9]+ {return TK_LIT_FLOAT;}

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