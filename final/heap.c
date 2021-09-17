#include "heap.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

Node* initialize_Node(int ascii,int freq){
    Node *node=malloc(sizeof(Node));
    node->ascii=ascii;
    node->freq=freq;
    node->isLeftChild=-1;
    node->right=NULL;
    node->left=NULL;
}


// Put all data in counter to the heap, not heapify yet
// ASCII 32 to 127 is initialized to A[0]~A[95],  LF (ASCII 10) is put in A[96] , CR (ASCII 13) is in A[97]
void initialize_heap(heap *hp, int counter[]){
    hp->heap_size=NC;
    for (int i=0; i<=95; i++) {
        hp->A[i] = initialize_Node(i + 32,counter[i + 32]);
    }

    hp->A[96]=initialize_Node(10,counter[10]);
    hp->A[97]=initialize_Node(13,counter[13]);
}

// index of parent,left,right in array A of heap
int parent(int i){
    return (i-1)/2;
}

int left(int i){
    return 2*i+1;
}

int right(int i){
    return 2*i+2;
}


// All operations of heap are based on CLRS Chapter 6

void min_heapify(heap *hp,int i){   // i is position in priorityQueue A, heapify the subtree rooted at i
    int heap_size=hp->heap_size;
    assert(i<=heap_size-1);
    int l=left(i);
    int r=right(i);

    if (l>heap_size-1 && r>heap_size-1 )    //no child
        return;

    int min=-1;
    Node *tmp;

    // get min among A[i], A[left(i)], A[right(i)]
    if (l<=heap_size-1 && hp->A[l]->freq < hp->A[i]->freq)
        min=l;
    else
        min=i;
    if (r<=heap_size-1) {
        if (hp->A[r]->freq < hp->A[min]->freq)
            min = r;
    }

    if (min != i){   // swap A[i] with A[min]
        tmp=hp->A[i];
        hp->A[i]=hp->A[min];
        hp->A[min]=tmp;

        min_heapify(hp,min);
    }
}

void build_min_heap(heap *hp){
    hp->heap_size=NC;
    for(int i=NC/2-1;i>=0;i--)
        min_heapify(hp,i);
}


void heap_extract_min(heap *hp,Node **min){  // min point to the extracted node
    assert(hp->heap_size>0);
    *min=hp->A[0];

    if(hp->heap_size==1) {     //only one element, finished
        hp->heap_size--;
        hp->A[0]=NULL;
    }

    else {     //lift A[heap_size-1] to A[0]
        hp->A[0]=hp->A[hp->heap_size-1];
        hp->A[hp->heap_size-1]=NULL;
        hp->heap_size--;
        min_heapify(hp,0);
    }

}

//exchange A[i] with its parent until root, terminate if itself is larger than parent
void goUp_if_node_isSmaller(heap *hp,int i){
    Node *tmp;

    while(i>0 && hp->A[parent(i)]->freq>hp->A[i]->freq){
        tmp=hp->A[i];
        hp->A[i]=hp->A[parent(i)];
        hp->A[parent(i)]=tmp;
        i=parent(i);
    }
}


// insert node to heap, if this node <  its parent, go up
void min_heap_insert(heap *hp,Node *node){
    hp->heap_size++;
    assert(hp->heap_size<=NC);  //NC: length of heap-array, heap_size cannot exceed the length
    assert(hp->A[hp->heap_size-1]==NULL);

    hp->A[hp->heap_size-1]=node;
    goUp_if_node_isSmaller(hp,hp->heap_size-1);
}

// print the priority queue in the heap
void print_heap(heap *hp){
    printf("heap array: ");
    for (int i=0;i<hp->heap_size;i++){
        assert(hp->A[i]!=NULL);
        printf("(%d %d)",hp->A[i]->ascii,hp->A[i]->freq);
    }
    printf("\n");
}

void convert_heap_to_HuffmanTree(heap *hp){
    if (hp->heap_size==1 && hp->A[0]->ascii==-1) return;   //conversion is finished
    Node *node1 ,*node2, *superNode; // two lowest-freq elements and their superNode
    while(hp->heap_size>1){
        heap_extract_min(hp,&node1);
        heap_extract_min(hp,&node2);
        combine_two_nodes(node1,node2,&superNode);

        min_heap_insert(hp, superNode);
    }
}

// node 1 and 2 are combined to superNode, their left and right  depends on their comparison
void combine_two_nodes(Node *node1,Node *node2,Node **superNode){
    (*superNode)=malloc(sizeof(Node));
    (*superNode)->ascii=-1;
    (*superNode)->freq=node1->freq+node2->freq;  //freq is sum of two children
    (*superNode)->isLeftChild=-1;    //The superNode currently is a root
    if (compare_nodes(node1,node2)==0){
        (*superNode)->left=node1;
        node1->isLeftChild=1;
        (*superNode)->right=node2;
        node2->isLeftChild=0;
    }else{
        (*superNode)->left=node2;
        node2->isLeftChild=1;
        (*superNode)->right=node1;
        node1->isLeftChild=0;
    }
}


//My convention: first compare ascii, if they are the same, then compare freq
int compare_nodes(Node *node1,Node *node2){
    if (node1->ascii<node2->ascii) return 0;
    else if (node1->ascii>node2->ascii) return 1;
    else{
        if (node1->freq>node2->freq) return 1;
        else return 0;
    }
}


void free_Tree(Node *root){
    if (root!=NULL){
        free_Tree(root->left);
        free_Tree(root->right);
        free(root);
    }
}

// The assertion in free_heap is a correctness-checking,
// We only need to free heap at the end or re-enter section 1
// In either case, heap has been converted to encoding tree; only A[0] has node, which is the root of tree
void free_heap(heap *hp){
    for (int i=1;i<NC;i++)
        assert(hp->A[i]==NULL);
    free_Tree(hp->A[0]);
    free(hp);
}



// For debug, all leaf have symbol while all inner nodes do not has ascii symbol
void check_Tree(Node *node){
    if (node==NULL) return;
    if (node->ascii!=-1){
        assert(node->left==NULL);
        assert(node->right==NULL);
    }
    else{
        assert(node->left!=NULL);
        assert(node->right!=NULL);
    }
    check_Tree(node->left);
    check_Tree(node->right);
}
