#include "list.h"

void list_init(List* list,
               int (*des)(void *data),
               int (*match)(const void *key1,const void *key2),
               char* (*tostr)(void *data)){
    list->head=NULL;
    list->tail=NULL;
    list->size=0;
    list->destroy=des;
    list->tostr=tostr;
    list->match=match;
}


int list_prepend(List* list,void *data){
    LE* new=malloc(sizeof(LE));
    new->data=data;
    new->prev=NULL;
    new->next=list->head;
    if (list->head!=NULL){
        list->head->prev=new;
    }
    if (list->head==NULL){
        list->tail=new;
    }
    list->head=new;
    list->size++;
    return 1;
}
int list_append(List* list,void *data){
    LE* new=malloc(sizeof(LE));
    new->data=data;
    new->next=NULL;
    new->prev=list->tail;
    if (list->tail!=NULL)
        list->tail->next=new;
    if (list->tail==NULL)
        list->head=new;
    list->tail=new;
    list->size++;
    return 1;
}

int list_ins_next(List* list,LE* element,void* data){   /*     element is pointer to previous pos*/
    if (element==NULL) return list_prepend(list,data);    /*add element to the beginning*/
    if (element==list->tail) return list_append(list,data);  /* add element to the end*/
    LE* new=malloc(sizeof(LE));
    new->data=data;
    new->next=element->next;
    new->prev=element;
    element->next=new;
    new->next->prev=new;

    list->size++;

    return 1;
}

void list_rem_first(List* list){
    if (list->size==0) return;
    LE* discard=list->head;
    if (list->size==1){
        list->head=NULL;
        list->tail=NULL;
    }else{
        list->head=discard->next;
        discard->next->prev=NULL;
    }
    list->size--;
    free(discard);
    return;
}
void list_rem_next(List* list,LE* element){
    if (element==NULL){
        list_rem_first(list);
        return;
    }
    if (list->size==0 || element->next==NULL) return;

    LE* discard=element->next;
    discard->next->prev=element;
    element->next=discard->next;

    free(discard);
    list->size--;
    return;
}

void list_print(List* list){
    LE *node=list_head(list);
    printf("[");
    while (node!=NULL){
        printf("%s ",list->tostr(node->data));
        node=node->next;
    }
    printf("]\n");
}
int list_add(List* list,int index,void* data){
    int i;
    LE* node=list_head(list);
    for (i=0;i<index;i++){
        node=node->next;
    }
    return list_ins_next(list,node,data);
}

void* list_element_at(List *list,int index){
    int i;
    LE* node=list_head(list);
    for (i=0;i<index;i++){
        node=node->next;
    }
    return node->data;
}

int list_find_first(List* list,void* data){
    int index;
    LE* curr=list->head;
    for (index=0;index<list->size;index++){
        if ((*list->match)(data,curr->data)==1)
            return index;
        curr=curr->next;
    }
    return -1;
}
