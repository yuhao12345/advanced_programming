#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef struct tnode_{
  int data;                      /* each node's data (in this case int) */
  struct tnode_ *left, *right;   /* pointer to the two children of this node */
  int count;                     /* number of occurrences of data encountered so far */
} Tnode;


Tnode *addtree(Tnode *p, int data);
void treeprint(Tnode *p);

int main(){
  Tnode *root, *node;
  int data[] = {67,1,1,3,5,3,42,777,99,99,1,3,2,0,1,6,5,3,3,67,777,43};
  int val, i, n = sizeof(data)/sizeof(int);
  
  root = NULL;
  node = root = addtree(root,data[0]); /* handle root separately */

  for (i=1;i<n;++i){                   /* loop over input data */
    val = data[i];
    node = addtree(node,val);
  }

  treeprint(root);
  return 1;
}

Tnode *addtree(Tnode *p, int data){
  if (p == NULL){
    p = malloc(sizeof(Tnode));
    p->data = data;
    p->left = p->right = NULL;
    p->count = 1;
  }

  else if (p->data == data)
    ++p->count;

  else if (data < p->data)
    p->left = addtree(p->left,data);

  else if (data > p->data)
    p->right = addtree(p->right,data);
  
  return p;

}

void treeprint(Tnode *p){
  if (p != NULL){
    treeprint(p->left);
    printf("data:%d count:%d\n", p->data, p->count);
    treeprint(p->right);
  }
}
