//
// Created by kymws on 11/24/2020.
//

#ifndef HOMEWORK_5_YUHAO12345_LINKEDLIST_H
#define HOMEWORK_5_YUHAO12345_LINKEDLIST_H


typedef struct ListNode_{
    char *data;
    struct ListNode_ *next;
    int count;
} ListNode;

typedef struct List_{
    ListNode *head;
    ListNode *tail;
    int length;
} List;

void list_init(List *list);

void list_append_check_duplicate(List *list,char *data);

void print_list(List *list);

void print_dict(char **dict);

char** extract_dict(List *list, int length_threshold, int freq_threshold, int *size_dict);

int convert_StringToInt(char *data,char **dict,int size_dict);

void save_compressedFile_ToText(int tmp,char *token,FILE **fp);

void save_dict_toText(char** dict,int size_dict,FILE **fp);

void free_list(List *list);

#endif //HOMEWORK_5_YUHAO12345_LINKEDLIST_H
