#include <stdio.h>
#include "table.h"
extern int yyparse(void);
extern int yylex_destroy(void);
void *arvore = NULL;
TableStack* globalTableStack;
void exporta (void *arvore);
int main (int argc, char **argv)
{
  init_global_symbol_stack();
  int ret = yyparse(); 

  exporta (arvore);
  yylex_destroy();

  printf("Final stack state:\n");
  print_global_table_stack(100);

  free_table_stack(globalTableStack);
  return ret;
}