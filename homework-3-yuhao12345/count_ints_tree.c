#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef struct tnode_{
  int data;                      /* each node's data (in this case int) */
  struct tnode_ *left, *right;   /* pointer to the two children of this node */
  int count;                     /* number of occurrences of data encountered so far */
} Tnode;


Tnode* add_node(int data);

int main(int argc, char **argv){
  int data[] = {67,1,1,3,5,3,42,777,99,99,1,3,2,0,1,6,5,3,3,67};
  
  int val, i, n = sizeof(data)/sizeof(int);
  
  Tnode *node, *root;
  node = root = NULL;
  
  /* let's do root outside of loop */
  
  root = malloc(sizeof(Tnode));    /* create memory for root node */
  root->left = root->right = NULL; /* important -- indicates leaf of tree */
  root->data = data[0];            /* stick data in root node */
  root->count = 1;                 /* intialize count */
  
  for (i=1;i<n;++i){               /* loop over input data and place in tree */              
    node = root;                   /* start at the top of tree */
    val = data[i];                 /* get the next value in input stream */
    
    while (1){                    /* now we need to walk the tree to see where to put data */
      if (val == node->data){
	++node->count;
	printf("%d occurences of %d encountered \n", node->count, val);
	break; 
      }
      
      else if (val > node->data){  /* two possibilities: either = node->right or need to create */
	if (node->right == NULL){
	  node->right = add_node(val); /* need to create node then stop */
	  break;
	}
	else{
	  node = node->right;       /* child node exists, set it to node */
	}
      }
      
      else if (val < node->data){
	if (node->left == NULL){
	  node->left = add_node(val); /* need to create node then stop */
	  break;
	}
	
	else{
	  node = node->left;           /* child node exists */
	}
      }
    }
  }
  return EXIT_SUCCESS;
}

Tnode* add_node(int val){
  Tnode* node = malloc(sizeof(Tnode));
  node->data = val;
  node->left = node->right = NULL;
  node->count = 1;
  return node;
}
