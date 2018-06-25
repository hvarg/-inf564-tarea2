#include <stdio.h>
#include <stdlib.h>
#include "read_adds.h"

typedef struct {
  int left, ht;
} strip;

typedef struct {
  strip **arr;
  int max, n;
} skyline;

skyline *skyline_merge(skyline *s1, skyline *s2);

strip *strip_new (int left, int ht)
{
  strip *s = malloc(sizeof(strip));
  s->left = left;
  s->ht = ht;
  return s;
}


skyline *skyline_new (int max)
{
  skyline *sl = malloc(sizeof(skyline));
  sl->max = max;
  sl->n = 0;
  sl->arr = malloc(sizeof(strip) * max);
  return sl;
}

void skyline_del (skyline *s)
{
  free(s->arr);
  free(s);
}

void skyline_append (skyline *sl, strip *s)
{
  //printf("skyline_append (%x <- %x)\n", sl, s);
  if (sl->n > 0 && sl->arr[sl->n-1]->ht == s->ht) return;
  if (sl->n > 0 && sl->arr[sl->n-1]->left == s->left) {
    sl->arr[sl->n-1]->ht = sl->arr[sl->n-1]->ht > s->ht ? sl->arr[sl->n-1]->ht : s->ht;
    return;
  }
  sl->arr[sl->n++] = s;
  //printf("skyline_append (%x) ended\n", sl);
}

void skyline_print (skyline *sl)
{
  int i;
  for (i = 0; i < sl->n; i++) {
    printf("%d, %d\n", sl->arr[i]->left, sl->arr[i]->ht);
  }
}

skyline *skyline_find (addsInstance *ins, int l, int h)
{
  //printf("skyline_find %d, %d\n", l, h);
  skyline *res = NULL;
  if (l == h) {
    res = skyline_new(2);
    skyline_append(res, strip_new(ins->b[l][0], ins->b[l][1]) );
    skyline_append(res, strip_new(ins->b[l][2], 0) );
    //printf("skyline_find %d, %d ended\n", l, h);
    //skyline_print(res);
    return res;
  }
  int mid = (l+h)/2;
  skyline *sl = skyline_find(ins, l, mid);
  skyline *sr = skyline_find(ins, mid+1, h);
  res = skyline_merge(sl, sr);

  skyline_del(sl);
  skyline_del(sr);
  /*
  free sl free sr;
  */
  //printf("skyline_find %d, %d ended\n", l, h);
  //skyline_print(res);
  return res;
}

skyline *skyline_merge(skyline *s1, skyline *s2)
{
  //printf("skyline_merge %d, %d\n", s1->n, s2->n);
  //printf("Mergin:\n");
  //skyline_print(s1);
  //skyline_print(s2);
  skyline *res = skyline_new(s1->n + s2->n);
  int h1 = 0, h2 = 0,
      i = 0, j = 0, maxh, x;
  while ( i < s1->n && j < s2->n) {
    if (s1->arr[i]->left < s2->arr[j]->left) {
      x = s1->arr[i]->left;
      h1 = s1->arr[i++]->ht;
    } else {
      x = s2->arr[j]->left;
      h2 = s2->arr[j++]->ht;
    }
    maxh = h1 > h2 ? h1 : h2;
    skyline_append(res, strip_new(x, maxh));
  }
  while (i < s1->n) skyline_append(res, (s1->arr[i++]));
  while (j < s2->n) skyline_append(res, (s2->arr[j++]));

  //printf("Result:\n");
  //skyline_print(res);
  return res;
  //printf("skyline_merge %d, %d ended\n", s1->n, s2->n);
}




int main (int argc, const char * args[])
{
  int i, j;
  addsInstance *ins = adds_readfile(stdin);

  /*printf("%d\n", ins->blen);
  for (i = 0; i < ins->blen; i++) {
    printf("%d %d %d\n", ins->b[i][0], ins->b[i][1], ins->b[i][2]);
  }
  printf("%d\n", ins->dlen);
  for (i = 0; i < ins->dlen; i++) {
    printf("%d %d\n", ins->d[i][0], ins->d[i][1]);
  }*/

  skyline *ptr = skyline_find(ins, 0, ins->blen-1);
  printf("%d\n", ptr->n);
  skyline_print(ptr);
  printf("%d\n", ins->dlen);
  int b = 0;
  for (i = 0; i < ins->dlen; i++) {
    for (j = 0; j < ptr->n; j++) {
      if (ptr->arr[j]->left > ins->d[i][0] && ptr->arr[j]->ht > ins->d[i][1]) {
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
