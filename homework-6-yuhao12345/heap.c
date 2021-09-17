#include "heap.h"
#include <stdlib.h>
#include <stdio.h>

void initialize_heap(heap *hp){
    hp->heap_size=0;
    for (int i=0; i<MAXV; i++){
        hp->pos[i]=-1;  //by default, no node is in the heap
        hp->priorityQueue[i]=NULL;
    }
}

void min_heapify(heap *hp,int i){   // i is position in priorityQueue
    int heap_size=hp->heap_size;
    assert(i<=heap_size-1);
    int l=2*i+1;
    int r=2*i+2;
    if (l>heap_size-1 && r>heap_size-1 )
        return;
    int min=-1;
    heapNode *tmp;
    //printf("min0 %d\n",min);
    if (l<=heap_size-1 && hp->priorityQueue[l]->distance < hp->priorityQueue[i]->distance)
        min=l;
    else
        min=i;
    //printf("min1 %d\n",min);
    if (r<=heap_size-1) {
        if (hp->priorityQueue[r]->distance < hp->priorityQueue[min]->distance)
            min = r;
    }
    //printf("min2 %d\n",min);
    if (min != i){   // swap priorityQueue[i] with priorityQueue[min]
        int node1=hp->priorityQueue[i]->index;
        int node2=hp->priorityQueue[min]->index;
        //printf("n1 n2 %d %d\n",node1,node2);
        tmp=hp->priorityQueue[i];
        hp->priorityQueue[i]=hp->priorityQueue[min];
        hp->priorityQueue[min]=tmp;

        hp->pos[node1]=min;
        hp->pos[node2]=i;

        min_heapify(hp,min);
    }

}

// define operations for min-heap
void heap_extract_min(heap *hp,int *dist,int *minNode){
    assert(hp->heap_size>0);

    int node;

    heapNode *min=hp->priorityQueue[0];

    *dist=min->distance;
    *minNode=min->index;
    //printf("extract (%d %d)\n",*minNode,*dist);
    if(hp->heap_size==1)
        hp->heap_size--;

    else {
        hp->priorityQueue[0]->index=hp->priorityQueue[hp->heap_size-1]->index;
        hp->priorityQueue[0]->distance=hp->priorityQueue[hp->heap_size-1]->distance;

        node=hp->priorityQueue[0]->index;  //put last node to the 1st position
        hp->pos[node]=0;

        hp->heap_size--;
        //printf("%d\n",hp->heap_size);
        min_heapify(hp,0);
        //printf("%d\n",hp->heap_size);
    }

}


//key is distance. i is index for priorityQueue, decrease priorityQueue[i] to key
void heap_decrease_key(heap *hp,int i,int key){
    assert(key<hp->priorityQueue[i]->distance);

    heapNode *tmp;

    hp->priorityQueue[i]->distance=key;
    while(i>0 && hp->priorityQueue[(i-1)/2]->distance>hp->priorityQueue[i]->distance){
        int node1=hp->priorityQueue[i]->index;
        int node2=hp->priorityQueue[(i-1)/2]->index;

        tmp=hp->priorityQueue[i];
        hp->priorityQueue[i]=hp->priorityQueue[(i-1)/2];
        hp->priorityQueue[(i-1)/2]=tmp;

        hp->pos[node1]=(i-1)/2;
        hp->pos[node2]=i;

        i=(i-1)/2;
    }
}


// key is distance, node is index of node in graph
void min_heap_insert(heap *hp,int key, int node){
    hp->heap_size++;

    if (hp->priorityQueue[hp->heap_size-1]==NULL){
        hp->priorityQueue[hp->heap_size-1]=malloc(sizeof(heapNode));
    }
    hp->priorityQueue[hp->heap_size-1]->index=node;
    hp->priorityQueue[hp->heap_size-1]->distance=10000;

    hp->pos[node]=hp->heap_size-1;

    heap_decrease_key(hp,hp->heap_size-1,key);
    //printf("current heap-min: (node dist) %d %d\n",hp->priorityQueue[0]->index,hp->priorityQueue[0]->distance);
}


void print_heap(heap *hp){
    printf("heap: ");
    for (int i=0;i<hp->heap_size;i++)
        printf("(%d %d)",hp->priorityQueue[i]->index,hp->priorityQueue[i]->distance);
    printf("\n");
}

void free_heap(heap *hp){
    for (int i=0;i<MAXV;i++){
        if (hp->priorityQueue[i]!=NULL)
            free(hp->priorityQueue[i]);
    }

    free(hp);
}