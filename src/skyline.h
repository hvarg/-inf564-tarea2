#ifndef SKYLINE_H_
#define SKYLINE_H_

/* Un strip es una parte de la solucion. */
typedef struct {
  int x, y;
} strip;

/* Un skyline es un array de strips que representa una solucion al problema. */
typedef struct {
  strip **data;
  int max, n;
} skyline;

skyline *skyline_merge  (skyline *s1, skyline *s2);
strip   *strip_new      (int x, int y);
skyline *skyline_new    (int max);
void     skyline_del    (skyline *s);
void     skyline_append (skyline *sl, strip *s);
void     skyline_print  (skyline *sl);
skyline *skyline_find   (int **b, int l, int h);
skyline *skyline_merge  (skyline *s1, skyline *s2);

#endif
