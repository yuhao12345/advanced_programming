#ifndef FINAL_HEAP_H
#define FINAL_HEAP_H

#define NC 98     //# of ASCII characters: 32 to 127, LF, CR

typedef struct Node_{
    int ascii;    //ASCII value of char; For super node, ascii=-1
    int freq;
    struct Node_ *left;
    struct Node_ *right;
    int isLeftChild;  // 1: Node is a left child;  0: Node is right child; -1:Node is root
} Node;

typedef struct heap_{
    int heap_size;
    Node *A[NC];  //array A represents a min-heap

} heap;

Node* initialize_Node(int ascii,int freq);

void initialize_heap(heap *hp, int counter[]);

void min_heapify(heap *hp,int i);

void build_min_heap(heap *hp);

void heap_extract_min(heap *hp,Node **min);

void goUp_if_node_isSmaller(heap *hp,int i);

void min_heap_insert(heap *hp,Node *node);

void convert_heap_to_HuffmanTree(heap *hp);

void combine_two_nodes(Node *node1,Node *node2,Node **superNode);

int compare_nodes(Node *node1,Node *node2);

void print_heap(heap *hp);

void free_Tree(Node *root);

void free_heap(heap *hp);

void check_Tree(Node *node);

#endif //FINAL_HEAP_H
