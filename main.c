/* ======= GRUPO J ======= */
/* Luccas da Silva Lima 00324683 */
/* Matheus Almeida da Silva 00316326 */

#include <stdio.h>
#include "table.h"
#include "iloc.h"
#include "ast_tree.h"

extern int yyparse(void);
extern int yylex_destroy(void);
extern Node* mainFunctionNode;

void *arvore = NULL;
TableStack* globalTableStack;
//void exporta (void *arvore);
int main (int argc, char **argv)
{
  initialize_global_stack();
  int ret = yyparse();

  // Código da função main
  if (mainFunctionNode->iloc_code_list != NULL)
  {
    print_iloc_code_list(mainFunctionNode->iloc_code_list);
  } 

  // exporta (arvore);
  arvore = NULL;
  mainFunctionNode = NULL;
  yylex_destroy();
  free_table_stack(globalTableStack);
  return ret;
}