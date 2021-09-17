#include<stdio.h>
#include<stdlib.h>
#include "BSTree.h"
#include<string.h>
#include<assert.h>

TreeNode* createTreeNode(char *data){
    TreeNode *node=malloc(sizeof(TreeNode));
    node->data=malloc(strlen(data)*sizeof(char)+1);
    strcpy(node->data,data);
    node->count=1;
    node->right=NULL;
    node->left=NULL;
}

TreeNode* tree_insert_check_duplicate(TreeNode *root, char *data){
    if (data==NULL) return root;
    if (root==NULL){
        root = createTreeNode(data);
    }
    else if (strcasecmp(root->data,data)==0)
        root->count++;
    else if(strcasecmp(root->data,data)>0)
        root->left=tree_insert_check_duplicate(root->left,data);
    else
        root->right=tree_insert_check_duplicate(root->right,data);
    return root;
}

void free_tree(TreeNode *root){
    if(root==NULL) return;
    if (root!=NULL){
        free_tree(root->left);
        free_tree(root->right);
        free(root->data);
        free(root);
    }
}

void print_tree(TreeNode *root){
    if(root==NULL) return;
    print_tree(root->left);
    printf("%s : %d\n",root->data,root->count);
    print_tree(root->right);
}

//return a dictionary
void extract_dict_from_Tree(TreeNode *root, int length_threshold, int freq_threshold, char **dict, int *size_dict){
    if (root->left!=NULL)
        extract_dict_from_Tree(root->left,length_threshold,freq_threshold,dict,size_dict);

    if (strlen(root->data)>=length_threshold && root->count>=freq_threshold){
        dict[*size_dict]=malloc(strlen(root->data)*sizeof(char)+1);
        strcpy(dict[*size_dict],root->data);
        (*size_dict)++;
    }

    if (root->right!=NULL)
        extract_dict_from_Tree(root->right,length_threshold,freq_threshold,dict,size_dict);
}

