/* ======= GRUPO J ======= */
/* Luccas da Silva Lima 00324683 */
/* Matheus Almeida da Silva 00316326 */

%{
#include <stdio.h>
#include "valor_lexico.h"
#include "ast_tree.h"
#include "table.h"

// Importa as funções necessárias.
int get_line_number();
int yylex(void);
void yyerror (char const *message);
extern Node* arvore;
extern SymbolTableStack* globalSymbolTableStack;

DataType declared_type = DATA_TYPE_UNDECLARED; // O tipo atualmente declarado
Node* mainFunctionNode = NULL;

%}

%union{
    Valor_lexico valor_lexico;
    struct Node* node;
    char* ast_token;
    DataType data_type;
    SymbolNature symbol_nature;
}

%define parse.error verbose

%token TK_PR_INT
%token TK_PR_FLOAT
%token TK_PR_BOOL
%token<ast_token> TK_PR_IF
%token TK_PR_ELSE
%token<ast_token> TK_PR_WHILE
%token<ast_token> TK_PR_RETURN
%token<ast_token> TK_OC_LE
%token<ast_token> TK_OC_GE
%token<ast_token> TK_OC_EQ
%token<ast_token> TK_OC_NE
%token<ast_token> TK_OC_AND
%token<ast_token> TK_OC_OR
%token<valor_lexico> TK_IDENTIFICADOR
%token<valor_lexico> TK_LIT_INT
%token<valor_lexico> TK_LIT_FLOAT
%token<valor_lexico> TK_LIT_FALSE
%token<valor_lexico> TK_LIT_TRUE
%token<ast_token> '=' '<' '>' '+' '-' '*' '/' '%' '!' '(' ')'

%token TK_ERRO

%type<node> program
%type<node> elements_list
%type<node> element
%type<node> global_vars_declaration
%type<node> function
%type<data_type> type
%type<node> operands
%type<node> literal
%type<node> ident_list
%type<node> header
%type<node> body
%type<node> parameters_list
%type<node> parameter
%type<node> command_block
%type<node> simple_command_list
%type<node> command
%type<node> attribution_command
%type<node> function_call
%type<node> return_command
%type<node> control_command
%type<node> arguments
%type<node> expression
%type<node> expression0
%type<node> expression1
%type<node> expression2
%type<node> expression3
%type<node> expression4
%type<node> expression5
%type<node> expression6
%type<node> expression7
%type<node> minus_expressison
%type<node> negation_expression

%%

// -- Programa -- 
program: elements_list
{
    $$ = $1;
    arvore = $$;
}
|
{
    $$ = NULL;
    arvore = NULL;
}; // Contendo uma lista de elementos ou vazio.

elements_list: element elements_list
{
    if ($1){
        $$ = $1;
        add_child($$, $2);
    }
    else{
        $$ = $2;
    }
}
| element
{
    $$ = $1;
};
element: global_vars_declaration 
{
    $$ = NULL;
}
| function
{
    $$ = $1;
}; // Elemento: Sendo uma declaração global ou uma definição de função.

// -- Declaração de Variáveis Globais -- 
global_vars_declaration: type ident_list ','
{
    $$ = NULL;
    remove_node($2);

    declared_type = DATA_TYPE_UNDECLARED;
}
ident_list: TK_IDENTIFICADOR ';' ident_list
{
    $$ = NULL;
    TableEntryValue value = create_table_entry_value(SYMBOL_NATURE_IDENTIFIER, declared_type, $1);
    add_symbol_value_to_global_table_stack(value);
}
| TK_IDENTIFICADOR
{
    $$ = NULL;
    TableEntryValue value = create_table_entry_value(SYMBOL_NATURE_IDENTIFIER, declared_type, $1);
    add_symbol_value_to_global_table_stack(value);
};

// -- Funções --
function: header body
{
    $$ = $1;
    if ($2){
        add_child($$, $2);
        pop_global_stack();
    }
};

// Cabeçalho da função. Podendo conter uma lista de parametros ou nenhum parametro.
header: '(' parameters_list ')' TK_OC_OR type '/' TK_IDENTIFICADOR 
{
    $$ = create_node_valor_lexico($7, $5);
}
| '('')' TK_OC_OR type '/' TK_IDENTIFICADOR
{
    $$ = create_node_valor_lexico($6, $4);
};
parameters_list: parameter ';' parameters_list
{
    $$ = NULL;
}
| parameter
{
    $$ = $1;
};
parameter: type TK_IDENTIFICADOR{
    $$ = NULL;
    freeValor_lexico($2);
};

// Corpo da função. Contendo um bloco de comandos.
body: command_block
{
    $$ = $1;
};
command_block: '{' simple_command_list '}' 
{
    $$ = $2;
}
| '{''}'
{
    $$ = NULL;
};
simple_command_list: command simple_command_list
{
    if ($1)
    {
        $$ = $1;
        add_child($$, $2);
    }
    else
    {
        $$ = $2;
    }
}
| command
{
    $$ = $1;
}

// -- Comandos Simples --
command: command_block ',' 
{
    $$ = $1;
}
| global_vars_declaration 
{
    $$ = $1;
}
| attribution_command ',' 
{
    $$ = $1;
}
| function_call ',' 
{
    $$ = $1;
}
| return_command ',' 
{
    $$ = $1;
}
| control_command ','
{
    $$ = $1;
};
attribution_command: TK_IDENTIFICADOR '=' expression
{
    DataType type = infer_type_from_identifier($1);
    check_identifier_is_variable($1);
    
    $$ = create_node_token($2, type);
    add_child($$, create_node_valor_lexico($1, type));
    add_child($$, $3);
};
function_call: TK_IDENTIFICADOR '(' arguments ')'
{
    DataType type = infer_type_from_identifier($1);
    check_identifier_is_function($1);

    $$ = create_node_function($1, type);
    add_child($$, $3);
} 
| TK_IDENTIFICADOR '('')'
{
    DataType type = infer_type_from_identifier($1);
    check_identifier_is_function($1);

    $$ = create_node_function($1, type);
};

return_command: TK_PR_RETURN expression
{
    $$ = create_node_token($1, infer_type_from_node($2));
    add_child($$, $2);
};

control_command: TK_PR_IF '(' expression ')' command_block 
{
    $$ = create_node_token($1, infer_type_from_node($3));
    add_child($$, $3);
    if ($5){
        add_child($$, $5);
    }
}
| TK_PR_IF '(' expression ')' command_block TK_PR_ELSE command_block 
{
    $$ = create_node_token($1, infer_type_from_node($3));
    add_child($$, $3);
    if ($5){
        add_child($$, $5);
    }
    if ($7){
        add_child($$, $7);
    }
}
| TK_PR_WHILE '(' expression ')' command_block
{
    $$ = create_node_token($1, infer_type_from_node($3));
    add_child($$, $3);
    if ($5){
        add_child($$, $5);
    }
};
arguments: expression ';' arguments
{
    $$ = $1;
    add_child($$, $3);
}
| expression
{
    $$ = $1;
};

// -- Expressões -- 
expression: expression7
{
    $$ = $1;
};
// Grau 7 de precedencia das expressões. Pode ser um OR ou uma expressão mais prioritária.
expression7: expression7 TK_OC_OR expression6 
{
    $$ = create_node_token($2, infer_type_from_nodes($1, $3));
    add_child($$, $1);
    add_child($$, $3);
}
| expression6
{
    $$ = $1;
};
// Grau 6 de precedencia. Pode ser um AND ou uma expressão mais prioritária.
expression6: expression6 TK_OC_AND expression5 
{
    $$ = create_node_token($2, infer_type_from_nodes($1, $3));
    add_child($$, $1);
    add_child($$, $3);
}
| expression5
{
    $$ = $1;
};
// Grau 5 de precedencia. Pode ser um EQUAL ou um NOT EQUAL ou uma expressão mais prioritária.
expression5: expression5 TK_OC_EQ expression4 
{
    $$ = create_node_token($2, infer_type_from_nodes($1, $3));
    add_child($$, $1);
    add_child($$, $3);
}
| expression5 TK_OC_NE expression4 
{
    $$ = create_node_token($2, infer_type_from_nodes($1, $3));
    add_child($$, $1);
    add_child($$, $3);
}
| expression4
{
    $$ = $1;
};
// Grau 4 de precedencia. Pode ser um < ou um > ou um LessEqual ou um GreaterEqual ou uma expressão mais prioritária.
expression4: expression4 TK_OC_LE expression3 
{
    $$ = create_node_token($2, infer_type_from_nodes($1, $3));
    add_child($$, $1);
    add_child($$, $3);
}
| expression4 TK_OC_GE expression3 
{
    $$ = create_node_token($2, infer_type_from_nodes($1, $3));
    add_child($$, $1);
    add_child($$, $3);
}
| expression4 '<' expression3 
{
    $$ = create_node_token($2, infer_type_from_nodes($1, $3));
    add_child($$, $1);
    add_child($$, $3);
}
| expression4 '>' expression3 
{
    $$ = create_node_token($2, infer_type_from_nodes($1, $3));
    add_child($$, $1);
    add_child($$, $3);
}
| expression3
{
    $$ = $1;
};
// Grau 3 de precedencia. Pode ser uma adição ou uma subtração ou uma expressão mais prioritária.
expression3: expression3 '+' expression2 
{
    $$ = create_node_token($2, infer_type_from_nodes($1, $3));
    add_child($$, $1);
    add_child($$, $3);
}
| expression3 '-' expression2 
{
    $$ = create_node_token($2, infer_type_from_nodes($1, $3));
    add_child($$, $1);
    add_child($$, $3);
}
| expression2
{
    $$ = $1;
};
// Grau 2 de precedencia. Pode ser uma * ou / ou % ou uma expressão mais prioritária.
expression2: expression2 '*' expression1 
{
    $$ = create_node_token($2, infer_type_from_nodes($1, $3));
    add_child($$, $1);
    add_child($$, $3);
}
| expression2 '/' expression1 
{
    $$ = create_node_token($2, infer_type_from_nodes($1, $3));
    add_child($$, $1);
    add_child($$, $3);
}
| expression2 '%' expression1 
{
    $$ = create_node_token($2, infer_type_from_nodes($1, $3));
    add_child($$, $1);
    add_child($$, $3);
}
| expression1
{
    $$ = $1;
};
// Grau 1 de precedencia. Pode ser uma ! ou - ou uma expressão mais prioritária.
expression1: negation_expression expression0
{
    $$ = $1;
    add_child($$, $2);
}
|minus_expressison expression0 
{
    $$ = $1;
    add_child($$, $2);
}
| expression0
{
    $$ = $1;
};

negation_expression: negation_expression '!' 
{
    $$ = create_node_token($2, infer_type_from_node($1));
    add_child($$, $1);
}
| '!'
{
    $$ = create_node_token($1, );
};
minus_expressison: minus_expressison '-' 
{
    $$ = create_node_token($2, infer_type_from_node($1));
    add_child($$, $1);
}
| '-' 
{
    $$ = create_node_token($1, );
};

expression0: operands 
{
    $$ = $1;
}
| '(' expression ')'
{
    $$ = $2;
};
operands: TK_IDENTIFICADOR 
{
    DataType type = infer_type_from_identifier($1);
    check_identifier_is_variable($1);

    $$ = create_node_valor_lexico($1, type);
}
| literal 
{
    $$ = $1;
}
| function_call
{
    $$ = $1;
};

// -- Tipos --
type: TK_PR_INT
{
    declared_type = DATA_TYPE_INT;
    $$ = DATA_TYPE_INT;
} 
| TK_PR_FLOAT 
{
    declared_type = DATA_TYPE_FLOAT;
    $$ = DATA_TYPE_FLOAT;
}
| TK_PR_BOOL
{
    declared_type = DATA_TYPE_BOOL;
    $$ = DATA_TYPE_BOOL;
};

// -- Literais --
literal: TK_LIT_INT
{
    $$ = create_node_valor_lexico($1, DATA_TYPE_INT);
} 
| TK_LIT_FLOAT 
{
    $$ = create_node_valor_lexico($1, DATA_TYPE_FLOAT);
}
| TK_LIT_TRUE 
{
    $$ = create_node_valor_lexico($1, DATA_TYPE_BOOL);
    TableEntryValue value = create_table_entry_value(SYMBOL_NATURE_LITERAL, DATA_TYPE_BOOL, $1);
    add_symbol_value_to_global_table_stack(value);
}
| TK_LIT_FALSE
{
    $$ = create_node_valor_lexico($1, DATA_TYPE_BOOL);
    TableEntryValue value = create_table_entry_value(SYMBOL_NATURE_LITERAL, DATA_TYPE_BOOL, $1);
    add_symbol_value_to_global_table_stack(value);
};
%%

// Função que imprime na tela o erro encontrado.
void yyerror(char const *message)
{
    printf("Erro Sintático encontrado na linha %d: %s\n", get_line_number(), message);
}