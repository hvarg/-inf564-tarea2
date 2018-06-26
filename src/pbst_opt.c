#include <stdio.h>
#include <stdlib.h>
#include "read_pbst.h"

/* Crea un array con los nodos del arbol en notacion preorden. */
void preorder_get (int **root, int i, int j, int *p, int *k)
{
  if (i <= j) {
    p[(*k)++] = root[i][j];
    preorder_get(root,i,root[i][j]-1,p,k);
    preorder_get(root,root[i][j]+1,j,p,k);
  }
}

/* Transforma la matriz root en un arbol binario y lo retorna. */
node *tree_create (int **root, int size, node **nodes)
{
  int *pre = malloc(sizeof(int) * size);
  int i, k=0;
  preorder_get(root, 0, size-1, pre, &k); //obtiene el arbol en preorden.

  node *sol = nodes[pre[0]], 
       *tmp;
  /* Transforma el preorden en un arbol. */
  for (i = 1; i < size; i++) {
    tmp = sol;
    while (1) {
      if (pre[i] < tmp->v) {
        if (tmp->left) tmp = tmp->left;
        else {
          tmp->left = nodes[pre[i]];
          break;
        }
      } else {
        if (tmp->right) tmp = tmp->right;
        else {
          tmp->right = nodes[pre[i]];
          break;
        }
      }
    }
  }
  //tree_print(sol);
  return sol;
}

/* Suma las probabilidades de los nodos desde i a j.
 * Se pueden guardar en memoria los calculos para mejorar esto. */
float sum(node **nodes, int i, int j)
{
  float sum = 0.0;
  for (; i <= j; i++)
    sum += nodes[i]->p;
  return sum;
}

/* Calcula el arbol de costo minimo y luego lo crea. */
float tree_opt(node **nodes, int n, node *tree)
{
  int i, j, L, r;
  float c;
  /* Matrices para guardar los costos y nodos minimos. */
  float **cost = malloc(sizeof(float *) * n);
  int **root = malloc(sizeof(int *) * n);
  for (i = 0; i < n; i++) cost[i] = calloc(n, sizeof(float));
  for (i = 0; i < n; i++) root[i] = calloc(n, sizeof(int));
  for (i = 0; i < n; i++) { // Llenando la diagonal.
    cost[i][i] = nodes[i]->p;
    root[i][i] = i;
  }

  /* Comparando con los L siguientes. */
  for (L = 2; L <= n; L++) {
    for (i = 0; i < n-L+1; i++) {
      j = i+L-1;
      cost[i][j] = 100000; //Numero muy grande.
      for (r = i; r <= j; r++) {
        c = ((r>i) ? cost[i][r-1] : 0) + 
            ((r<j) ? cost[r+1][j] : 0) +
            sum(nodes, i, j);

        if (c < cost[i][j]) { //Guarda el costo y nodo minimo.
          cost[i][j] = c;
          root[i][j] = r;
        }
      }
    }
  }
  /* Crea el arbol de costo minimo. */
  tree = tree_create(root, n, nodes);
  //print_array(root, n);
  return cost[0][n-1];
}

int main (int argc, const char * args[])
{
  int size;
  node **nodes, *root = NULL;
  /* Lee mientras queden instancias. */
  while( (nodes = read_pbst(stdin, &size)) ) {
    /* tree_opt retorna el optimo y crea el arbol. */
    printf("%.4f\n", tree_opt(nodes, size, root));
    free(nodes);
  }
  return EXIT_SUCCESS;
}
