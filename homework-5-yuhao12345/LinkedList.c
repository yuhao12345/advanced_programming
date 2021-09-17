#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include "LinkedList.h"


void list_init(List *list){
    list->head=NULL;
    list->tail=NULL;
    list->length=0;
}

//scanning each word into the linkedlist and record the duplicate of each word
void list_append_check_duplicate(List *list,char *data){
    if (data==NULL) return;     //token is at the end of each line

    if (list->length==0){           //when list is empty, insert head
        ListNode *node=malloc(sizeof(ListNode));
        // add extra 1 in malloc since strcpy adds a null terminator character '\0'
        node->data=malloc(strlen(data)*sizeof(char)+1);
        strcpy(node->data,data);
        node->count=1;
        node->next=NULL;
        list->head=node;
        list->tail=node;
        list->length++;
        return;
    }
    //scan each node from the beginning and check if node has existed
    ListNode *current=list->head;
    for (int i=0;i<list->length;i++){
        if (strcasecmp(current->data,data)==0){   //case-insensitive
            current->count++;
            return;
        }
        current=current->next;
    }
    assert(current==NULL);
    //attach new node at the end
    ListNode *node=malloc(sizeof(ListNode));
    node->data=malloc(strlen(data)*sizeof(char)+1);
    strcpy(node->data,data);
    node->count=1;
    node->next=NULL;
    list->tail->next=node;
    list->tail=node;
    list->length++;
}


void print_list(List *list){
    assert(list->length>0);
    for (ListNode *node=list->head;node!=NULL;node=node->next)
        printf("%s : %d\n",node->data,node->count);
    //printf("length of linkedlist: %d\n",list->length);
}

void free_list(List *list){
    if (list->length>0){
        ListNode *current=list->head;
        ListNode *next;
        for(int i=0;i<list->length;i++){
            next=current->next;
            free(current->data);
            free(current);
            current=next;
        }
    }
    free(list);
}


// scan linkedlist, if a word exceeds length_threshold and freq_threshold, extract it to string array
char** extract_dict(List *list, int length_threshold, int freq_threshold, int *size_dict){
    assert(list->length>0);

    *size_dict=0;
    ListNode *current=list->head;
    for(int i=0;i<list->length;i++){
        if (strlen(current->data)>=length_threshold && current->count>=freq_threshold){
            (*size_dict)++;        //number of dict turple
        }
        current=current->next;
    }
    //printf("size of dict :%d\n",size_dict);
    char **dict=malloc(*size_dict*sizeof(char*));
    current=list->head;
    int k=0;
    for(int i=0;i<list->length;i++){
        if (strlen(current->data)>=length_threshold && current->count>=freq_threshold){
            dict[k]=malloc(strlen(current->data)*sizeof(char)+1);
            strcpy(dict[k],current->data);
            //printf("%s \n",*dict[k]);
            k++;
        }
        current=current->next;
    }
    assert(k==*size_dict);
    return dict;
}

