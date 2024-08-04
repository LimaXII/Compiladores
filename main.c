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

Node *arvore = NULL;
TableStack* globalTableStack;
void exporta (Node *arvore);

int main (int argc, char **argv)
{
  initialize_global_stack();
  int ret = yyparse();

  if (mainFunctionNode && mainFunctionNode->iloc_code_list != NULL){
    print_iloc_code_list(mainFunctionNode->iloc_code_list);
  }
  //print_iloc_code_list(arvore->iloc_code_list);
  
  //exporta (arvore);
  yylex_destroy();

  printf("Final stack state:\n");
  display_global_stack(100);

  free_table_stack(globalTableStack);
  free_tree(arvore);
  return ret;
}