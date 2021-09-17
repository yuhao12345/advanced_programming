#include<stdlib.h>
#include<stdio.h>
#include "HashTable.h"
#include<assert.h>
#include <string.h>
unsigned int naive_hash(char *word, int nbins)
{
    unsigned int h = 0;
    int c;
    while(c = *word++)
        h += c;
    return h % nbins;
}
unsigned int bernstein_hash(char *word, int nbins)
{
    unsigned int h = 5381;
    int c;
    while(c == *word++)
        h = 33 * h + c;
    return h % nbins;
}
unsigned int FNV_hash(char *word, int nbins)
{
    unsigned long h = 14695981039346656037lu;
    char c;
    while(c = *word++)
    {
        h = h * 1099511628211lu;
        h = h ^ c;
    }
    return h % nbins;
}

List* hashTable_init(int nbins){
    List* hashTable=malloc(nbins*sizeof(List));
    for(int i=0;i<nbins;i++){
        hashTable[i].head=NULL;
        hashTable[i].length=0;
        hashTable[i].tail=NULL;
    }
    return hashTable;
}

void hash_insert_check_duplicate(List** hashTable,char *data, int nbins){
    if (data==NULL) return;
    unsigned int k=bernstein_hash(data, nbins);
    assert(k<=nbins);
    list_append_check_duplicate(&((*hashTable)[k]),data);
}

void print_HashTable(List *hashTable,int nbins){
    for (int i=0;i<nbins;i++)
        if (hashTable[i].length>0){
            print_list(&hashTable[i]);
        }
}

//should alloc memory for dict before useing this function
void extract_dict_from_HashTable(List *hashTable, int nbins, int length_threshold, int freq_threshold, char **dict, int *size_dict){
    *size_dict=0;
    for (int j=0;j<nbins;j++)
        if (hashTable[j].length>0){
            ListNode *current=hashTable[j].head;
            for(int i=0;i<hashTable[j].length;i++){
                if (strlen(current->data)>=length_threshold && current->count>=freq_threshold){
                    dict[*size_dict]=malloc(strlen(current->data)*sizeof(char)+1);
                    strcpy(dict[*size_dict],current->data);
                    (*size_dict)++;
                }
                current=current->next;
            }
        }
}

void free_HashTable(List *hashTable,int nbins){
    for (int i=0;i<nbins;i++){
        if (hashTable[i].length>0){
            ListNode *current=hashTable[i].head;
            ListNode *next;
            for(int i=0;i<hashTable[i].length;i++){
                next=current->next;
                free(current->data);
                free(current);
                current=next;
            }
        }
    }
    free(hashTable);
}