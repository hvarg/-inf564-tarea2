#include <stdio.h>
#include <stdlib.h>
#include "read_adds.h"
#include "skyline.h"

int main (int argc, const char * args[])
{
  int i, j;
  /* Leemos la entrada estandar y generamos la instancia a resolver. */
  addsInstance *ins = adds_readfile(stdin);
  /* Calculamos el skyline solucion. */
  skyline *sol = skyline_find(ins->b, 0, ins->blen-1);
  printf("%d\n", sol->n);
  skyline_print(sol);
  printf("%d\n", ins->dlen);
  
  int b = 0;
  for (i = 0; i < ins->dlen; i++) { //TODO logn
    for (j = 0; j < sol->n; j++) {
      if (sol->data[j]->x > ins->d[i][0] && sol->data[j]->y > ins->d[i][1]) {
        printf("true\n");
        b++;
        break;
      }
    }
    if (b == 0) {
      printf("false\n");
    }
    b = 0;
  }

  del_addsInstance(ins);
  return EXIT_SUCCESS;
}
