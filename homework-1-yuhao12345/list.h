#include<stdio.h>
#include<stdlib.h>

typedef struct ListElement{
    void* data;
    struct ListElement* next;
    struct ListElement* prev;
}LE;

typedef struct List{
    LE* head;
    LE* tail;
    int size;
    char* (*tostr)(void *data);
    int (*destroy)(void *data);
    int (*match)(const void *key1,const void *key2);
}List;

void list_init(List* list,
               int (*destroy)(void *data),
               int (*match)(const void *key1,const void *key2),
               char* (*tostr)(void *data));
int list_destroy(void *data);
int list_prepend(List* list,void *data);
int list_append(List* list,void *data);
int list_ins_next(List* list,LE* element,void* data);
void list_rem_first(List* list);
void list_rem_next(List* list,LE* element);
void list_print(List* list);
int list_add(List* list,int index,void* data);
void* list_element_at(List *list,int index);
int list_find_first(List* list,void* data);

#define list_size(list) ((list)->size)
#define list_head(list) ((list)->head)
