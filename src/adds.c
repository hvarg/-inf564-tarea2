#include <stdio.h>
#include <stdlib.h>
#include "read_adds.h"

int main (int argc, const char * args[])
{
  int i;
  addsInstance *ins = adds_readfile(stdin);

  printf("%d\n", ins->blen);
  for (i = 0; i < ins->blen; i++) {
    printf("%d %d %d\n", ins->b[i][0], ins->b[i][1], ins->b[i][2]);
  }
  printf("%d\n", ins->dlen);
  for (i = 0; i < ins->dlen; i++) {
    printf("%d %d\n", ins->d[i][0], ins->d[i][1]);
  }
  del_addsInstance(ins);
  return EXIT_SUCCESS;
}
