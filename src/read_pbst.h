#ifndef READDAT_H_
#define READDAT_H_

/* Nodo de un arbol binario con probabilidades, en v se guarda el valor de este
 * nodo mientras que en p su probabilidad.*/
typedef struct __node{
  int v;
  float p;
  struct __node *left, *right;
} node;

node   *node_new    (int v, float p);
node  **read_pbst   (FILE *fp, int *size);
void    node_print  (node *n);
void    node_del    (node *n);
float   tree_cost   (node *root, int h);
void    tree_print  (node *root);

#endif
