#include <stdio.h>
#include <stdlib.h>
#include "read_pbst.h"

/* Lee un problema desde fp y lo transforma en un conjunto de nodos. */
node **read_pbst (FILE *fp, int *size)
{
  int i = 0, treelen = 0;
  float tmp = 0.0;
  fscanf(fp, "%d\n", &treelen);
  if (!treelen) return NULL;
  node **nodes = malloc(sizeof(node) * treelen);
  for (i = 0; i < treelen; i++) {
    fscanf(fp, "%f ", &tmp);
    nodes[i] = node_new(i+1, tmp); 
  }
  *size = treelen;
  return nodes;
}

/* Crea un nodo de un arbol binario. */
node * node_new (int v, float p)
{
  node *n = malloc(sizeof(node));
  n->v = v;
  n->p = p;
  n->left = NULL;
  n->right = NULL;
  return n;
}

/* Elimina un nodo. */
void node_del (node *n)
{
  if (n->left)  node_del(n->left);
  if (n->right) node_del(n->right);
  free(n);
}

/* Imprime un arbol binario por salida estandar. debug. */
void tree_print (node *root)
{
  if (root->left) printf("(%d, %.2f) <- ", root->left->v, root->left->p);
  printf("(%d, %.2f)", root->v, root->p);
  if (root->right) printf(" -> (%d, %.2f)", root->right->v, root->right->p);
  printf("\n");
  if (root->left) tree_print(root->left);
  if (root->right) tree_print(root->right);
}

/* Calcula el costo del arbol. */
float tree_cost (node *root, int h)
{
  return root?
      h*root->p + tree_cost(root->right, h+1) + tree_cost(root->left, h+1) :
      0;
}
