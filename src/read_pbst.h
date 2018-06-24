#ifndef READDAT_H_
#define READDAT_H_

typedef struct __node{
  int v;
  float p;
  struct __node *left, *right;
} node;

node * node_new (int v, float p);
node ** read_pbst (FILE *fp, int *size);
void node_print (node *n);
void node_del (node *n);
float tree_cost (node *root, int h);
void tree_print (node *root);

#endif
