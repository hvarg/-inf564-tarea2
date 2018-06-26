#include <stdio.h>
#include <stdlib.h>
#include "skyline.h"

/* Crea un nuevo strip. */
strip *strip_new (int x, int y)
{
  strip *s = malloc(sizeof(strip));
  s->x = x;
  s->y = y;
  return s;
}

/* Crea un nuevo skyline. */
skyline *skyline_new (int max)
{
  skyline *sl = malloc(sizeof(skyline));
  sl->max = max;
  sl->n = 0;
  sl->data = malloc(sizeof(strip) * max);
  return sl;
}

/* Elimina un skyline. */
void skyline_del (skyline *s)
{
  free(s->data);
  free(s);
}

/* Agrega un strip al skyline. */
void skyline_append (skyline *sl, strip *s)
{
  if (sl->n > 0 && sl->data[sl->n-1]->y == s->y) return;
  if (sl->n > 0 && sl->data[sl->n-1]->x == s->x) {
    sl->data[sl->n-1]->y = 
        sl->data[sl->n-1]->y > s->y ?
        sl->data[sl->n-1]->y : s->y;
    return;
  }
  sl->data[sl->n++] = s;
}

/* Imprime en salida estandar un skyline. */
void skyline_print (skyline *sl)
{
  int i;
  for (i = 0; i < sl->n; i++) {
    printf("%d %d\n", sl->data[i]->x, sl->data[i]->y);
  }
}

/* Encuentra un skyline para un conjunto 'b' de edificios desde b[l] hasta * b[r]. */
skyline *skyline_find (int **b, int l, int r)
{
  skyline *res = NULL;
  if (l == r) {
    /* Caso base, graba los dos 'strips' de un edificio (arriba izq, abajo,der ). */
    res = skyline_new(2);
    skyline_append(res, strip_new(b[l][0], b[l][1]));
    skyline_append(res, strip_new(b[l][2], 0));
    return res;
  }
  /* Dividir y conquistar. T(n) = 2*T(n/2) + O(n) */
  int mid = (l+r)/2;
  skyline *sl = skyline_find(b, l, mid);
  skyline *sr = skyline_find(b, mid+1, r);
  res = skyline_merge(sl, sr);

  skyline_del(sl);
  skyline_del(sr);
  return res;
}

/* Une dos skylines y retorna el resultante. */
skyline *skyline_merge(skyline *s1, skyline *s2)
{
  /*El nuevo skyline tendra a lo mas la suma de puntos. */
  skyline *res = skyline_new(s1->n + s2->n);
  int x, y, y1 = 0, y2 = 0,
      i = 0, j = 0;
  while ( i < s1->n && j < s2->n) { // O(s1->n + s2->n)
    if (s1->data[i]->x < s2->data[j]->x) { // itera comparando 'x'
      x = s1->data[i]->x;
      y1 = s1->data[i++]->y;
    } else {
      x = s2->data[j]->x;
      y2 = s2->data[j++]->y;
    }
    y = y1 > y2 ? y1 : y2; // 'y' es el mayo de los 'y' anteriores.
    skyline_append(res, strip_new(x, y));
  }
  while (i < s1->n) skyline_append(res, (s1->data[i++]));
  while (j < s2->n) skyline_append(res, (s2->data[j++]));

  return res;
}
