#include <stdio.h>
#include <stdlib.h>
#include "read_pbst.h"

void print_sol(int **root, int i, int j) {
		if (i <= j) {
			printf("%d ", root[i][j]+1);
			print_sol(root,i,root[i][j]-1);
			print_sol(root,root[i][j]+1,j);
		}
}

float sum(node **nodes, int i, int j)
{
  float sum = 0.0;
  for (; i <= j; i++)
    sum += nodes[i]->p;
  return sum;
}
void print_array(int **arr, int l)
{
  int i,j;
  for (i=0; i<l; i++) {
    for(j=0; j<l; j++)
      printf("%d ", arr[i][j]+1);
    printf("\n");
  }
}

float optimalSearchTree(node **nodes, int n)
{
  int i, j, L, r;
  float c;
  float **cost = malloc(sizeof(float *) * n);
  int **root = malloc(sizeof(int *) * n);
  for (i = 0; i < n; i++) cost[i] = calloc(n, sizeof(float));
  for (i = 0; i < n; i++) root[i] = calloc(n, sizeof(int));
  for (i = 0; i < n; i++) {
    cost[i][i] = nodes[i]->p;
    root[i][i] = i;
  }

  for (L = 2; L <= n; L++) {
    for (i = 0; i < n-L+1; i++) {
      j = i+L-1;
      cost[i][j] = 1000;
      for (r = i; r <= j; r++) {
        c = ((r>i) ? cost[i][r-1] : 0) + 
            ((r<j) ? cost[r+1][j] : 0) +
            sum(nodes, i, j);

        if (c < cost[i][j]) {
          cost[i][j] = c;
          root[i][j] = r;
        }
      }
    }
  }
  print_sol(root, 0, n-1); printf("\n----\n");
  print_array(root, n);
  return cost[0][n-1];
}

int min_index (float *array, int size)
{
  int i, index;
  float min = array[0];
  for (i = 1; i < size; i++) {
    if (min > array[i]) {
      index = i;
      min = array[i];
    }
  }
  return index;
}

node *tree_opt (node **nodes, int start, int end, int h)
{
  int i;
  //for (i = start; i < end; printf("%.2f ", nodes[i++]->p) );
  //printf("[%d-%d]\n", start, end);
  if (end-start < 1) return NULL; //FIXME
  if (end-start == 1) return nodes[start];
  if (end-start == 2) {
    if (nodes[start]->p > nodes[start+1]->p) {
      nodes[start]->right = nodes[start+1];
      return nodes[start];
    } else {
      nodes[start+1]->left = nodes[start];
      return nodes[start+1];
    }
  }
  node *root = NULL;


  float max[3] = {
    nodes[start]->p,
    nodes[start+1]->p,
    nodes[start+2]->p
  };
  int maxid[3] = {start, start+1, start+2};
  int id = 0, b = 0,
      minid = (max[0] < max[1] && max[0] < max[2]) ? 0 : (max[1] < max[2]) ? 1 : 2;
  for (i = start+3; i < end; i++) {
    if (nodes[i]->p > max[minid] || (nodes[i]->p == max[minid] && b)) {
      //printf("[%.2f, %.2f, %.2f] %d\n", max[0], max[1], max[2], id);
      //printf("[%4d, %4d, %4d] %d\n", maxid[0], maxid[1], maxid[2], minid);
      if ((minid-1)%3 == id) { //swap
        //printf("swap!\n");
        max[minid] = max[(minid+1)%3];
        maxid[minid] = maxid[(minid+1)%3];
        minid = (minid+1) % 3;
      } else if (minid == id) id = (id+1) % 3;

      max[minid] = nodes[i]->p;
      maxid[minid] = i;
      minid = (max[0] < max[1] && max[0] < max[2]) ? 0 : (max[1] < max[2]) ? 1 : 2;
      if (b) b=0;
    } else if (nodes[i]->p == max[minid] && !b) b=1;
  }
  //printf("[%.2f, %.2f, %.2f]\n", max[id], max[(id+1)%3], max[(id+2)%3]);
  //printf("[%4d, %4d, %4d]\n\n", maxid[id], maxid[(id+1)%3], maxid[(id+2)%3]);

  if (h*max[id] > (h+1)*max[(id+1)%3] && h*max[id] > (h+1)*max[(id+2)%3]) {
    root = nodes[maxid[id]];
    //printf("root=%.2f\n", root->p);
    root->left = tree_opt(nodes, start, maxid[id], h+1);
    root->right = tree_opt(nodes, maxid[id]+1, end, h+1);
  } else
  if (h*max[(id+2)%3] > (h+1)*max[(id+1)%3] && h*max[(id+2)%3] > (h+1)*max[id]) {
    root = nodes[maxid[(id+2)%3]];
    //printf("root=%.2f\n", root->p);
    root->left = tree_opt(nodes, start, maxid[(id+2)%3], h+1);
    root->right = tree_opt(nodes, maxid[(id+2)%3]+1, end, h+1);
  } else {
    root = nodes[maxid[(id+1)%3]];
    //printf("root=%.2f\n", root->p);
    root->left = tree_opt(nodes, start, maxid[(id+1)%3], h+1);
    root->right = tree_opt(nodes, maxid[(id+1)%3]+1, end, h+1);
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
    root = tree_opt(nodes, 0, size, 1);
    tree_print(root);
    printf("=%.4f\n", tree_cost(root, 1));
    printf("=%.4f\n\n", optimalSearchTree(nodes, size));
    //tree_print(root);

    /*root = nodes[0];
    for (i = 1; i < size; i++) {
      root = tree_add(root, nodes[i]);
    }
    tree_print(root);
    printf("=%.4f\n", tree_cost(root, 1));*/

    //for (i = 0; i < size; node_del(nodes[i++]) );
    node_del(root);
    free(nodes);
  }
  return EXIT_SUCCESS;
}
