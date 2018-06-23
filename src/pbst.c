#include <stdio.h>
#include <stdlib.h>
#include "read_pbst.h"

int main (int argc, const char * args[])
{
  float *p = NULL;
  int i = 0, l = 0;
  while( (l = read_pbst(stdin, &p)) ) {
    printf("%d\n", l);
    for (i = 0; i < l; printf("%.2f ", p[i++]) );
    printf("\n");
    free(p);
  }
  return EXIT_SUCCESS;
}
