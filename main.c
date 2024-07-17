#include <stdio.h>
#include "table.h"
extern int yyparse(void);
extern int yylex_destroy(void);
void *arvore = NULL;
TableStack* globalTableStack;
void exporta (void *arvore);
int main (int argc, char **argv)
{
  int ret = yyparse(); 
  exporta (arvore);
  yylex_destroy();
  return ret;
}