#include <stdio.h>
#include <stdlib.h>
#include "read_adds.h"

addsInstance * adds_readfile (FILE *fp)
{
  int i;
  addsInstance *ins = malloc(sizeof(addsInstance));
  /* reading buildings */
  fscanf(fp, "%d\n", &(ins->blen));
  ins->b = malloc(sizeof(int*) * ins->blen);
  for (i = 0; i < ins->blen; i++) {
    ins->b[i] = malloc(sizeof(int) * 3);
    fscanf(fp, BFORMAT, &ins->b[i][0], &ins->b[i][1], &ins->b[i][2]);
  }
  /* reading drones */
  fscanf(fp, "%d\n", &(ins->dlen));
  ins->d = malloc(sizeof(int*) * ins->dlen);
  for (i = 0; i < ins->dlen; i++) {
    ins->d[i] = malloc(sizeof(int) * 2);
    fscanf(fp, DFORMAT, &ins->d[i][0], &ins->d[i][1]);
  }
  return ins;
}

void del_addsInstance (addsInstance *ins)
{
  int i;
  for (i = 0; i < ins->blen; free(ins->b[i++]) );
  free(ins->b);
  for (i = 0; i < ins->dlen; free(ins->d[i++]) );
  free(ins->d);
  free(ins);
}
