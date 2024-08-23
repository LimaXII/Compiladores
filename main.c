/* ======= GRUPO J ======= */
/* Luccas da Silva Lima 00324683 */
/* Matheus Almeida da Silva 00316326 */

#include <stdio.h>
#include "table.h"
#include "iloc.h"
#include "generate_cfg.h"
#include "ast_tree.h"

extern int yyparse(void);
extern int yylex_destroy(void);
extern Node* mainFunctionNode;

Node *arvore = NULL;
TableStack* globalTableStack;
void exporta (Node *arvore);

int main (int argc, char **argv)
{
  initialize_global_stack();
  int ret = yyparse();

  print_iloc_code_list(mainFunctionNode->iloc_code_list);

  generate_cfg_dot(mainFunctionNode->iloc_code_list);
  
  yylex_destroy();
  free_table_stack(globalTableStack);
  free_tree(arvore);
  return ret;
}