#ifndef HOMEWORK_5_YUHAO12345_HASHTABLE_H
#define HOMEWORK_5_YUHAO12345_HASHTABLE_H
#include "LinkedList.h"

List* hashTable_init(int nbins);

void hash_insert_check_duplicate(List** hashTable,char *data, int nbins);

void print_HashTable(List *hashTable,int nbins);

void free_HashTable(List *hashTable,int nbins);

void extract_dict_from_HashTable(List *hashTable, int nbins, int length_threshold, int freq_threshold, char **dict, int *size_dict);

void free_HashTable(List *hashTable,int nbins);

#endif //HOMEWORK_5_YUHAO12345_HASHTABLE_H
