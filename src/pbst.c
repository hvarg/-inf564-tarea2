#include <stdio.h>
#include <stdlib.h>
#include "read_pbst.h"

node *tree_add (node *root, node *new)
{
  if (new->p <= root->p) {
    if (new->v < root->v) {
      if (root->left) root->left = tree_add(root->left, new);
      else root->left = new;
    } else {
      if (root->right) root->right = tree_add(root->right, new);
      else root->right = new;
    }
  } else {
    if (new->v < root->v) new->right = root;
    else new->left = root;
    root = new;
  }
  return root;
}

int main (int argc, const char * args[])
{
  int size, i;
  node **nodes, *root;
  while( (nodes = read_pbst(stdin, &size)) ) {
    printf("%d\n", size);
    for (i = 0; i < size; printf("%.2f ", nodes[i++]->p) );
    printf("\n");

    root = nodes[0];
    for (i = 1; i < size; i++) {
      root = tree_add(root, nodes[i]);
    }
    tree_print(root);
    printf("=%.4f\n", tree_cost(root, 1));

    //for (i = 0; i < size; node_del(nodes[i++]) );
    node_del(root);
    free(nodes);
  }
  return EXIT_SUCCESS;
}
