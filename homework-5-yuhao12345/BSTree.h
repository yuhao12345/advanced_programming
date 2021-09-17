#ifndef HOMEWORK_5_YUHAO12345_BSTREE_H
#define HOMEWORK_5_YUHAO12345_BSTREE_H

typedef struct TreeNode_{
    char *data;
    struct TreeNode_* left;
    struct TreeNode_* right;
    int count;
}TreeNode;

TreeNode* tree_insert_check_duplicate(TreeNode *root, char *data);

void print_tree(TreeNode *root);

void extract_dict_from_Tree(TreeNode *root, int length_threshold, int freq_threshold, char **dict, int *size_dict);

void free_tree(TreeNode *root);

#endif //HOMEWORK_5_YUHAO12345_BSTREE_H
