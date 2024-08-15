/* ======= GRUPO J ======= */
/* Luccas da Silva Lima 00324683 */
/* Matheus Almeida da Silva 00316326 */

%{
#include <stdio.h>
#include "valor_lexico.h"
#include "ast_tree.h"
#include "table.h"
#include "asm.h"

// Importa as funções necessárias.
int get_line_number();
int yylex(void);
void yyerror (char const *message);
extern Node* arvore;

DataType declared_type = TYPE_UNDECLARED; // O tipo atualmente declarado
Node* mainFunctionNode = NULL;

%}

%union{
    Valor_lexico valor_lexico;
    struct Node* node;
    char* ast_token;
    DataType data_type;
    Nature nature;
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
%type<node> function_argument_init
%type<node> function_arguments
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
        if($2){
            $$->asm_code_list = concatenate_code($$->asm_code_list, $2->asm_code_list); 
        }
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

    declared_type = TYPE_UNDECLARED;
}
ident_list: TK_IDENTIFICADOR ';' ident_list
{
    $$ = NULL;
    TableEntry value = create_table_entry(NATURE_IDENTIFIER, declared_type, $1);
    add_entry_to_global_stack(value);
}

| TK_IDENTIFICADOR
{
    $$ = NULL;
    TableEntry value = create_table_entry(NATURE_IDENTIFIER, declared_type, $1);
    add_entry_to_global_stack(value);
};

// -- Funções --
function: header body
{
    $$ = $1;
    if ($2){
        add_child($$, $2);
    }
    pop_global_stack();

    if ($2)
        $$->asm_code_list = $2->asm_code_list;

    if (strncmp($1->valor_lexico.token_val, "main", 4) == 0)
        mainFunctionNode = $$;
};

// Cabeçalho da função. Podendo conter uma lista de parametros ou nenhum parametro.
header: function_arguments TK_OC_OR type '/' TK_IDENTIFICADOR 
{
    TableEntry value = create_table_entry(NATURE_FUNCTION, declared_type, $5);
    add_entry_to_lower_stack(value);

    $$ = create_node_valor_lexico($5, $3);
}
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
    
    // Adiciona identificador à tabela de tipos
    TableEntry value = create_table_entry(NATURE_IDENTIFIER, declared_type, $2);
    add_entry_to_global_stack(value);

    freeValor_lexico($2);
};

// Corpo da função. Contendo um bloco de comandos.
body: '{' simple_command_list '}'
{
    $$ = $2;
}
| '{''}'
{
    $$ = NULL;
}

function_argument_init: '('
{
    push_table_to_global_stack(create_table());
}

function_arguments: function_argument_init ')'
{
    $$ = NULL;
};
| function_argument_init parameters_list ')'
{
    $$ = NULL;
};

// -- Blocos Comandos --
command_block_init: '{'
{  
    push_table_to_global_stack(create_table());
};

command_block_end: '}'
{
    pop_global_stack();
};

command_block: command_block_init command_block_end
{
    $$ = NULL;
}
| command_block_init simple_command_list command_block_end 
{
    $$ = $2;
};

simple_command_list: command simple_command_list
{
    if ($1){
        $$ = $1;
        add_child($$, $2);

        if ($1->asm_code_list){
            $1->asm_code_list = concatenate_code($1->asm_code_list, $2->asm_code_list);
        }
        else{
            $$->asm_code_list = $2->asm_code_list ;
        }
    }
    else{
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

// -------------- ETAPA 5 ------------------------
// CONSTRUCOES DE LINGUAGEM
attribution_command: TK_IDENTIFICADOR '=' expression
{
    DataType type = get_type_from_identifier($1);
    validate_variable_identifier($1);
    
    $$ = create_node_token($2, type);
    add_child($$, create_node_valor_lexico($1, type));
    add_child($$, $3);

    $$->asm_code_list = concatenate_code($$->asm_code_list, $3->asm_code_list);
    TableEntry symbol = find_in_stack($1.token_val);
    int address = symbol.offset;
    int t1 = $3->out_r;

    if(symbol.isGlobal){
        gen_code(&($$->asm_code_list), OP_STOREAI_GLOBAL, t1, -1, address, -1);
    } else{
        gen_code(&($$->asm_code_list), OP_STOREAI_LOCAL, t1, -1, address, -1);
    }

};
function_call: TK_IDENTIFICADOR '(' arguments ')'
{
    DataType type = get_type_from_identifier($1);
    validate_function_identifier($1);

    $$ = create_node_function($1, type);
    add_child($$, $3);
} 
| TK_IDENTIFICADOR '('')'
{
    DataType type = get_type_from_identifier($1);
    validate_function_identifier($1);

    $$ = create_node_function($1, type);
};

return_command: TK_PR_RETURN expression
{
    $$ = create_node_token($1, infer_type_from_node($2));
    add_child($$, $2);

    $$->asm_code_list = concatenate_code($$->asm_code_list, $2->asm_code_list);
    int r1 = $2->out_r;   

    gen_code(&($$->asm_code_list), OP_RETURN, r1, -1, -1, -1);
};

control_command: TK_PR_IF '(' expression ')' command_block 
{
    $$ = create_node_token($1, infer_type_from_node($3));
    add_child($$, $3);

    $$->asm_code_list = concatenate_code($$->asm_code_list, $3->asm_code_list);
    int t1 = $3->out_r;
    int t2 = gen_temp();
    int t3 = gen_temp();
    int labelTrue = gen_label();
    int labelFalse = gen_label();

    gen_code(&($$->asm_code_list), OP_LOADI, 0, -1, t2, -1);
    gen_code(&($$->asm_code_list), OP_CMP_NE, t1, t2, t3, -1);
    gen_code(&($$->asm_code_list), OP_CBR, t3, -1, labelTrue, labelFalse);

    gen_label_code(&($$->asm_code_list), labelTrue);
    gen_code(&($$->asm_code_list), OP_NOP, -1, -1, -1, -1);

    if ($5){
        add_child($$, $5);
        $$->asm_code_list = concatenate_code($$->asm_code_list, $5->asm_code_list);
    }
    
    gen_label_code(&($$->asm_code_list), labelFalse);
    gen_code(&($$->asm_code_list), OP_NOP, -1, -1, -1, -1);

}
| TK_PR_IF '(' expression ')' command_block TK_PR_ELSE command_block 
{
    $$ = create_node_token($1, infer_type_from_node($3));
    add_child($$, $3);
    $$->asm_code_list = concatenate_code($$->asm_code_list, $3->asm_code_list);
    int t1 = $3->out_r;
    int t2 = gen_temp();
    int t3 = gen_temp();
    int labelTrue = gen_label();
    int labelFalse = gen_label();
    int labelEnd = gen_label();

    gen_code(&($$->asm_code_list), OP_LOADI, 0, -1, t2, -1);
    gen_code(&($$->asm_code_list), OP_CMP_NE, t1, t2, t3, -1);
    gen_code(&($$->asm_code_list), OP_CBR, t3, -1, labelTrue, labelFalse);

    gen_label_code(&($$->asm_code_list), labelTrue);
    gen_code(&($$->asm_code_list), OP_NOP, -1, -1, -1, -1);

    if ($5){
        add_child($$, $5);
        $$->asm_code_list = concatenate_code($$->asm_code_list, $5->asm_code_list);
    }
    gen_code(&($$->asm_code_list), OP_JUMPI, labelEnd, -1, -1, -1);
    gen_label_code(&($$->asm_code_list), labelFalse);
    gen_code(&($$->asm_code_list), OP_NOP, -1, -1, -1, -1);

    if ($7){
        add_child($$, $7);
        $$->asm_code_list = concatenate_code($$->asm_code_list, $7->asm_code_list);
    }

    gen_label_code(&($$->asm_code_list), labelEnd);
    gen_code(&($$->asm_code_list), OP_NOP, -1, -1, -1, -1);
}
| TK_PR_WHILE '(' expression ')' command_block
{
    $$ = create_node_token($1, infer_type_from_node($3));
    add_child($$, $3);

    int t1 = $3->out_r;
    int t2 = gen_temp();
    int t3 = gen_temp();
    int labelLoop = gen_label();
    int labelTrue = gen_label();
    int labelFalse = gen_label();

    gen_code(&($$->asm_code_list), OP_LOADI, 0, -1, t2, -1);
    gen_label_code(&($$->asm_code_list), labelLoop);
    gen_code(&($$->asm_code_list), OP_NOP, -1, -1, -1, -1);

    $$->asm_code_list = concatenate_code($$->asm_code_list, $3->asm_code_list);

    gen_code(&($$->asm_code_list), OP_CMP_NE, t1, t2, t3, -1);
    gen_code(&($$->asm_code_list), OP_CBR, t3, -1, labelTrue, labelFalse);

    gen_label_code(&($$->asm_code_list), labelTrue);
    gen_code(&($$->asm_code_list), OP_NOP, -1, -1, -1, -1);

    if ($5){
        add_child($$, $5);
        $$->asm_code_list = concatenate_code($$->asm_code_list, $5->asm_code_list);
    }
    gen_code(&($$->asm_code_list), OP_JUMPI, labelLoop, -1, -1, -1);

    gen_label_code(&($$->asm_code_list), labelFalse);
    gen_code(&($$->asm_code_list), OP_NOP, -1, -1, -1, -1);
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

    $$->asm_code_list = concatenate_code($1->asm_code_list, $3->asm_code_list);
    int t1 = $1->out_r;
    int t2 = $3->out_r;
    int t3 = gen_temp();

    gen_code(&($$->asm_code_list), OP_OR, t1, t2, t3, -1);
    $$->out_r = t3;
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

    $$->asm_code_list = concatenate_code($1->asm_code_list, $3->asm_code_list);
    int t1 = $1->out_r;
    int t2 = $3->out_r;
    int t3 = gen_temp();

    gen_code(&($$->asm_code_list), OP_AND, t1, t2, t3, -1);
    $$->out_r = t3;
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

    $$->asm_code_list = concatenate_code($1->asm_code_list, $3->asm_code_list);
    int t1 = $1->out_r;
    int t2 = $3->out_r;
    int t3 = gen_temp();
    int t4 = gen_temp();
    int labelTrue = gen_label();
    int labelFalse = gen_label();
    int labelEnd = gen_label();

    gen_code(&($$->asm_code_list), OP_CMP_EQ, t1, t2, t3, -1);
    gen_code(&($$->asm_code_list), OP_CBR, t3, -1, labelTrue, labelFalse);
    gen_label_code(&($$->asm_code_list), labelTrue);
    gen_code(&($$->asm_code_list), OP_LOADI, 1, -1, t4, -1);

    gen_code(&($$->asm_code_list), OP_JUMPI, labelEnd, -1, -1, -1);
    gen_label_code(&($$->asm_code_list), labelFalse);
    gen_code(&($$->asm_code_list), OP_LOADI, 0, -1, t4, -1);
    
    
    gen_label_code(&($$->asm_code_list), labelEnd);
    gen_code(&($$->asm_code_list), OP_NOP, -1, -1, -1, -1);

    $$->out_r = t4;
}
| expression5 TK_OC_NE expression4 
{
    $$ = create_node_token($2, infer_type_from_nodes($1, $3));
    add_child($$, $1);
    add_child($$, $3);

    $$->asm_code_list = concatenate_code($1->asm_code_list, $3->asm_code_list);
    int t1 = $1->out_r;
    int t2 = $3->out_r;
    int t3 = gen_temp();
    int t4 = gen_temp();
    int labelTrue = gen_label();
    int labelFalse = gen_label();
    int labelEnd = gen_label();

    gen_code(&($$->asm_code_list), OP_CMP_NE, t1, t2, t3, -1);
    gen_code(&($$->asm_code_list), OP_CBR, t3, -1, labelTrue, labelFalse);
    gen_label_code(&($$->asm_code_list), labelTrue);
    gen_code(&($$->asm_code_list), OP_LOADI, 1, -1, t4, -1);

    gen_code(&($$->asm_code_list), OP_JUMPI, labelEnd, -1, -1, -1);
    gen_label_code(&($$->asm_code_list), labelFalse);
    gen_code(&($$->asm_code_list), OP_LOADI, 0, -1, t4, -1);
    
    
    gen_label_code(&($$->asm_code_list), labelEnd);
    gen_code(&($$->asm_code_list), OP_NOP, -1, -1, -1, -1);

    $$->out_r = t4;
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

    $$->asm_code_list = concatenate_code($1->asm_code_list, $3->asm_code_list);
    int t1 = $1->out_r;
    int t2 = $3->out_r;
    int t3 = gen_temp();
    int t4 = gen_temp();
    int labelTrue = gen_label();
    int labelFalse = gen_label();
    int labelEnd = gen_label();

    gen_code(&($$->asm_code_list), OP_CMP_LE, t1, t2, t3, -1);
    gen_code(&($$->asm_code_list), OP_CBR, t3, -1, labelTrue, labelFalse);
    gen_label_code(&($$->asm_code_list), labelTrue);
    gen_code(&($$->asm_code_list), OP_LOADI, 1, -1, t4, -1);

    gen_code(&($$->asm_code_list), OP_JUMPI, labelEnd, -1, -1, -1);
    gen_label_code(&($$->asm_code_list), labelFalse);
    gen_code(&($$->asm_code_list), OP_LOADI, 0, -1, t4, -1);
    
    
    gen_label_code(&($$->asm_code_list), labelEnd);
    gen_code(&($$->asm_code_list), OP_NOP, -1, -1, -1, -1);

    $$->out_r = t4;
}
| expression4 TK_OC_GE expression3 
{
    $$ = create_node_token($2, infer_type_from_nodes($1, $3));
    add_child($$, $1);
    add_child($$, $3);

    $$->asm_code_list = concatenate_code($1->asm_code_list, $3->asm_code_list);
    int t1 = $1->out_r;
    int t2 = $3->out_r;
    int t3 = gen_temp();
    int t4 = gen_temp();
    int labelTrue = gen_label();
    int labelFalse = gen_label();
    int labelEnd = gen_label();

    gen_code(&($$->asm_code_list), OP_CMP_GE, t1, t2, t3, -1);
    gen_code(&($$->asm_code_list), OP_CBR, t3, -1, labelTrue, labelFalse);
    gen_label_code(&($$->asm_code_list), labelTrue);
    gen_code(&($$->asm_code_list), OP_LOADI, 1, -1, t4, -1);

    gen_code(&($$->asm_code_list), OP_JUMPI, labelEnd, -1, -1, -1);
    gen_label_code(&($$->asm_code_list), labelFalse);
    gen_code(&($$->asm_code_list), OP_LOADI, 0, -1, t4, -1);
    
    
    gen_label_code(&($$->asm_code_list), labelEnd);
    gen_code(&($$->asm_code_list), OP_NOP, -1, -1, -1, -1);

    $$->out_r = t4;
}
| expression4 '<' expression3 
{
    $$ = create_node_token($2, infer_type_from_nodes($1, $3));
    add_child($$, $1);
    add_child($$, $3);

    $$->asm_code_list = concatenate_code($1->asm_code_list, $3->asm_code_list);
    int t1 = $1->out_r;
    int t2 = $3->out_r;
    int t3 = gen_temp();
    int t4 = gen_temp();
    int labelTrue = gen_label();
    int labelFalse = gen_label();
    int labelEnd = gen_label();

    gen_code(&($$->asm_code_list), OP_CMP_LT, t1, t2, t3, -1);
    gen_code(&($$->asm_code_list), OP_CBR, t3, -1, labelTrue, labelFalse);
    gen_label_code(&($$->asm_code_list), labelTrue);
    gen_code(&($$->asm_code_list), OP_LOADI, 1, -1, t4, -1);

    gen_code(&($$->asm_code_list), OP_JUMPI, labelEnd, -1, -1, -1);
    gen_label_code(&($$->asm_code_list), labelFalse);
    gen_code(&($$->asm_code_list), OP_LOADI, 0, -1, t4, -1);
    
    
    gen_label_code(&($$->asm_code_list), labelEnd);
    gen_code(&($$->asm_code_list), OP_NOP, -1, -1, -1, -1);

    $$->out_r = t4;
}
| expression4 '>' expression3 
{
    $$ = create_node_token($2, infer_type_from_nodes($1, $3));
    add_child($$, $1);
    add_child($$, $3);

    $$->asm_code_list = concatenate_code($1->asm_code_list, $3->asm_code_list);
    int t1 = $1->out_r;
    int t2 = $3->out_r;
    int t3 = gen_temp();
    int t4 = gen_temp();
    int labelTrue = gen_label();
    int labelFalse = gen_label();
    int labelEnd = gen_label();

    gen_code(&($$->asm_code_list), OP_CMP_GT, t1, t2, t3, -1);
    gen_code(&($$->asm_code_list), OP_CBR, t3, -1, labelTrue, labelFalse);
    gen_label_code(&($$->asm_code_list), labelTrue);
    gen_code(&($$->asm_code_list), OP_LOADI, 1, -1, t4, -1);

    gen_code(&($$->asm_code_list), OP_JUMPI, labelEnd, -1, -1, -1);
    gen_label_code(&($$->asm_code_list), labelFalse);
    gen_code(&($$->asm_code_list), OP_LOADI, 0, -1, t4, -1);
    
    
    gen_label_code(&($$->asm_code_list), labelEnd);
    gen_code(&($$->asm_code_list), OP_NOP, -1, -1, -1, -1);

    $$->out_r = t4;
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

    $$->asm_code_list = concatenate_code($1->asm_code_list, $3->asm_code_list);

    int t1 = $1->out_r;
    int t2 = $3->out_r;
    int t3 = gen_temp();

    gen_code(&($$->asm_code_list), OP_ADD, t1, t2, t3, -1);
    
    $$->out_r = t3;
}
| expression3 '-' expression2 
{
    $$ = create_node_token($2, infer_type_from_nodes($1, $3));
    add_child($$, $1);
    add_child($$, $3);

    $$->asm_code_list = concatenate_code($1->asm_code_list, $3->asm_code_list);
    int t1 = $1->out_r;
    int t2 = $3->out_r;
    int t3 = gen_temp();

    gen_code(&($$->asm_code_list), OP_SUB, t1, t2, t3, -1);
    $$->out_r = t3;
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

    $$->asm_code_list = concatenate_code($1->asm_code_list, $3->asm_code_list);
    int t1 = $1->out_r;
    int t2 = $3->out_r;
    int t3 = gen_temp();

    gen_code(&($$->asm_code_list), OP_MULT, t1, t2, t3, -1);
    $$->out_r = t3;
}
| expression2 '/' expression1 
{
    $$ = create_node_token($2, infer_type_from_nodes($1, $3));
    add_child($$, $1);
    add_child($$, $3);

    $$->asm_code_list = concatenate_code($1->asm_code_list, $3->asm_code_list);
    int t1 = $1->out_r;
    int t2 = $3->out_r;
    int t3 = gen_temp();

    gen_code(&($$->asm_code_list), OP_DIV, t1, t2, t3, -1);
    $$->out_r = t3;
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

    $$->asm_code_list = concatenate_code($$->asm_code_list, $2->asm_code_list);
    int t1 = $2->out_r;
    int t2 = gen_temp();
    gen_code(&($$->asm_code_list), OP_NEG_LOG, t1, -1, t2, -1);

    $$->out_r = t2;
}
|minus_expressison expression0 
{
    $$ = $1;
    add_child($$, $2);

    $$->asm_code_list = concatenate_code($$->asm_code_list, $2->asm_code_list);
    int t1 = $2->out_r;
    int t2 = gen_temp();
    gen_code(&($$->asm_code_list), OP_NEG, t1, -1, t2, -1);

    $$->out_r = t2;
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
    DataType declared_exclamation = TYPE_PLACEHOLDER;
    $$ = create_node_token($1, declared_exclamation);
};
minus_expressison: minus_expressison '-' 
{
    $$ = create_node_token($2, infer_type_from_node($1));
    add_child($$, $1);
}
| '-' 
{
    DataType declared_minus = TYPE_PLACEHOLDER;
    $$ = create_node_token($1, declared_minus);
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
    DataType type = get_type_from_identifier($1);
    validate_variable_identifier($1);

    $$ = create_node_valor_lexico($1, type);

    TableEntry symbol = find_in_stack($1.token_val);
    int address = symbol.offset;
    int t = gen_temp();

    if(symbol.isGlobal){
        gen_code(&($$->asm_code_list), OP_LOADAI_GLOBAL, address, -1, t, -1);
    } else{
        gen_code(&($$->asm_code_list), OP_LOADAI_LOCAL, address, -1, t, -1);
    }

    $$->out_r = t;
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
    declared_type = TYPE_INT;
    $$ = TYPE_INT;
} 
| TK_PR_FLOAT 
{
    declared_type = TYPE_FLOAT;
    $$ = TYPE_FLOAT;
}
| TK_PR_BOOL
{
    declared_type = TYPE_BOOL;
    $$ = TYPE_BOOL;
};

// -- Literais --
literal: TK_LIT_INT
{
    $$ = create_node_valor_lexico($1, TYPE_INT);

    int value = atoi($1.token_val);
    int t = gen_temp();

    gen_code(&($$->asm_code_list), OP_LOADI, value, -1, t, -1);

    $$->out_r = t;
} 
| TK_LIT_FLOAT 
{
    $$ = create_node_valor_lexico($1, TYPE_FLOAT);
}
| TK_LIT_TRUE 
{
    $$ = create_node_valor_lexico($1, TYPE_BOOL);
    TableEntry value = create_table_entry(NATURE_LITERAL, TYPE_BOOL, $1);
    add_entry_to_global_stack(value);
}
| TK_LIT_FALSE
{
    $$ = create_node_valor_lexico($1, TYPE_BOOL);
    TableEntry value = create_table_entry(NATURE_LITERAL, TYPE_BOOL, $1);
    add_entry_to_global_stack(value);
};
%%

// Função que imprime na tela o erro encontrado.
void yyerror(char const *message)
{
    printf("Erro Sintático encontrado na linha %d: %s\n", get_line_number(), message);
} 