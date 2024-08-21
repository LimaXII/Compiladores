/* ======= GRUPO J ======= */
/* Luccas da Silva Lima 00324683 */
/* Matheus Almeida da Silva 00316326 */

#include <stdio.h>
#include "table.h"
#include "asm.h"
#include "ast_tree.h"
#include "generate_cfg.h"

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

  //if (mainFunctionNode && mainFunctionNode->iloc_code_list != NULL){
    //print_iloc_code_list(mainFunctionNode->iloc_code_list);
  //}

  //generateAsm(mainFunctionNode->asm_code_list);

  generate_cfg_dot(mainFunctionNode->asm_code_list);
  
  //exporta (arvore);
  yylex_destroy();
  free_table_stack(globalTableStack);
  free_tree(arvore);
  return ret;
}