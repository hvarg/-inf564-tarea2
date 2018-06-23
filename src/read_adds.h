#ifndef READDAT_H_
#define READDAT_H_

#define BFORMAT "%d %d %d"
#define DFORMAT "%d %d"

typedef struct {
  int blen, dlen;
  int **b, **d;
} addsInstance;

addsInstance * adds_readfile (FILE *fp);
void del_addsInstance (addsInstance *ins);

#endif
