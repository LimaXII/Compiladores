/* ======= GRUPO J ======= */
/* Luccas da Silva Lima 00324683 */
/* Matheus Almeida da Silva 00316326 */

#include <stdio.h>
#include "table.h"
extern int yyparse(void);
extern int yylex_destroy(void);
void *arvore = NULL;
TableStack* globalTableStack;
void exporta (void *arvore);
int main (int argc, char **argv)
{
  initialize_global_stack();
  int ret = yyparse(); 

  exporta (arvore);
  yylex_destroy();

  printf("Final stack state:\n");
  display_global_stack(100);

  free_table_stack(globalTableStack);
  return ret;
}