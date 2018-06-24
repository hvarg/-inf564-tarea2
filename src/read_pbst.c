#include <stdio.h>
#include <stdlib.h>
#include "read_pbst.h"

node ** read_pbst (FILE *fp, int *size)
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

node * node_new (int v, float p)
{
  node *n = malloc(sizeof(node));
  n->v = v;
  n->p = p;
  n->left = NULL;
  n->right = NULL;
  return n;
}

void node_del (node *n)
{
  if (n->left)  node_del(n->left);
  if (n->right) node_del(n->right);
  free(n);
}

void tree_print (node *root)
{
  if (root->left) printf("(%d, %.2f) <- ", root->left->v, root->left->p);
  printf("(%d, %.2f)", root->v, root->p);
  if (root->right) printf(" -> (%d, %.2f)", root->right->v, root->right->p);
  printf("\n");
  if (root->left) tree_print(root->left);
  if (root->right) tree_print(root->right);
}

float tree_cost (node *root, int h)
{
  return root?
      h*root->p + tree_cost(root->right, h+1) + tree_cost(root->left, h+1) :
      0;
}
