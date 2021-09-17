#include <stdlib.h>
#include <stdio.h>
#include "heap.h"
#include "encode_decode.h"
#include <assert.h>

//Traverse encoding tree recursively, get code for each leaf, save them to dict
void extract_dict_from_EncodingTree(Node *node, int *dict[]){
    static int tmp[150]={-1};   // Array of 0/1, length=150 is enough
    static int lastPointer=0;   // tmp[0, lastPointer-1] indicates the path from root to current node
    if (node==NULL) return;

    //if node->isLeftChild is -1, means root of encoding tree, do nothing
    if (node->isLeftChild==1){
        tmp[lastPointer]=0;   //add 0 to tmp since node is leftChild
        lastPointer++;
    }
    if (node->isLeftChild==0){
        tmp[lastPointer]=1;   // add 1 to tmp since node is rightChild
        lastPointer++;
    }
    if (node->ascii!=-1){    //this node is leaf, contains symbol
        assert(lastPointer>0);
        dict[node->ascii]=malloc((lastPointer+1)*sizeof(int));
        dict[node->ascii][0]=lastPointer;  //1st element save length of code
        for (int i=1;i<=lastPointer;i++)
            dict[node->ascii][i]=tmp[i-1];   // store path to dictionary
    }

    //lastPointer_copy reserves the value of current lastPointer
    //So that after recursive call, we can still recover the lastPointer corresponding to current node
    int lastPointer_copy=lastPointer;
    extract_dict_from_EncodingTree(node->left,dict);

    //reset lastPointer and tmp
    lastPointer=lastPointer_copy;
    for (int i=lastPointer_copy;i<150;i++)
        tmp[i]=-1;

    extract_dict_from_EncodingTree(node->right,dict);

    lastPointer=lastPointer_copy;
    for (int i=lastPointer_copy;i<150;i++)
        tmp[i]=-1;
}


void print_dict_element(int *dict){   //print encoded stream of char based on dict
    if(dict!=NULL){
        int length_code=dict[0];
        for (int j=1;j<=length_code;j++)
            printf("%d",dict[j]);
    }
}

void print_dict(int *dict[]){    //print the whole dict
    for (int i=32;i<=127;i++){
        if(dict[i]!=NULL){
            printf("%c;",i);
            print_dict_element(dict[i]);
            printf("\n");
        }
    }
}

void free_dict(int *dict[]){
    for (int i=0;i<=127;i++){
        if (dict[i]!=NULL){
            free(dict[i]);
        }
    }
}

