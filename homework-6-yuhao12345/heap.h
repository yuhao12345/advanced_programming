#ifndef HOMEWORK_6_YUHAO12345_HEAP_H
#define HOMEWORK_6_YUHAO12345_HEAP_H

#define MAXV 265214 /* maximum number of vertices */

#include <assert.h>

typedef struct heapNode_{
    int index;    //index of vertex
    int distance;
} heapNode;

typedef struct heap_{
    int heap_size;
    heapNode *priorityQueue[MAXV];
    int pos[MAXV];  // index of node in priorityQueue
} heap;


void initialize_heap(heap *hp);

void heap_extract_min(heap *hp,int *dist,int *endNode);

void heap_decrease_key(heap *hp,int i,int key);

void min_heap_insert(heap *hp,int key, int node);

void print_heap(heap *hp);

void free_heap(heap *hp);

#endif //HOMEWORK_6_YUHAO12345_HEAP_H
