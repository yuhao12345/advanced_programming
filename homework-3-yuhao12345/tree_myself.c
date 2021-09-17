#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node *left;
    struct node *right;
    int count;
} node;


node* addNode(node* nd,int val);
void printTree(node *root);

void main(){
    int a[]={3,6,8,2,3,9};
    int i;
    int length=sizeof(a)/sizeof(a[0]);
    node *root;
    root=malloc(sizeof(node));
    root->data=a[0];
    root->count=1;
    root->left=NULL;
    root->right=NULL;
    for (i=1;i<length;i++)
        root=addNode(root,a[i]);
    printTree(root);
}

node* addNode(node* nd,int val){
    if (nd==NULL){
        nd=malloc(sizeof(node));  /* important to give space*/
        nd->data=val;
        nd->right=NULL;
        nd->left=NULL;
        nd->count=1;
        return nd;
    }
    if (val==nd->data){
        nd->count++;
        return nd;
    }
    if (val<nd->data){
        nd->left=addNode(nd->left,val);
        return nd;
    }
    nd->right=addNode(nd->right,val);
    return nd;
}

void printTree(node *root){
    if (root!=NULL){
        printTree(root->left);
        printf("%d  count:%d  \n",root->data,root->count);
        printTree(root->right);
    }
}