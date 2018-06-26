#include <stdio.h>
#include <stdlib.h>
#include "read_adds.h"
#include "skyline.h"

int lower_bound (skyline *sol, int x)
{
  int l = 0;
  int h = sol->n;
  int mid;
  while (l < h) {
    mid =(l+h)/2;
    if (x <= sol->data[mid]->x) h = mid;
    else l = mid + 1;
  }
  return l;
}

int bs_lower_bound(int a[], int n, int x) {
    int l = 0;
    int h = n; // Not n - 1
    while (l < h) {
        int mid = (l + h) / 2;
        if (x <= a[mid]) {
            h = mid;
        } else {
            l = mid + 1;
        }
    }
    return l;
}

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
  for (i = 0; i < ins->dlen; i++) { // Por cada dron
    /* lower_bound para obtener solo los edificios con x mayor al dron. */
    for (j = lower_bound(sol, ins->d[i][0]); j < sol->n; j++) {
      if (sol->data[j]->y > ins->d[i][1]) {
        printf("true\n");
        b++;
        break;
      }
    }
    if (b == 0) printf("false\n");
    b = 0;
  }

  del_addsInstance(ins);
  return EXIT_SUCCESS;
}
