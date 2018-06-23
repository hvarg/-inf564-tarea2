#include <stdio.h>
#include <stdlib.h>

int read_pbst (FILE *fp, float **p)
{
  int i, treelen;
  fscanf(fp, "%d\n", &treelen);
  (*p) = malloc(sizeof(float) * treelen);
  for (i = 0; i < treelen; i++) {
    fscanf(fp, "%f ", &(*p)[i]);
  }
  return treelen;
}
