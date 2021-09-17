#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph.h"
#include "heap.h"
#include "timer.h"
#include <omp.h>

int **Dijkstra(graph *g,int s);

int main(int argc, char** argv) {
    FILE *fp=fopen(argv[1],"r");

    int NT;  /*number of threads*/
    NT  =   atoi(argv[2]);

    graph *g=malloc(sizeof(graph));
    read_graph(g, fp);
    fclose(fp);
    int nvertices=g->nvertices;
    //print_graph(g);

    StartTimer();

    // for each starting node, only save 10 largest dist with endNode,
    // Each list of 10 dist's value are already non-decreasingly sorted due to the  property of Dijk's algorithm

    //The parallel loop will fill top10, which contains nvertices lists
    // Eg: top10[0] contains 10 largest value as well as endNode  from starting node 0
    int **top10[g->nvertices];   //1st row: dist   2nd row:endNode

#pragma omp parallel shared(g) num_threads(NT)
#pragma omp for
    for (int i=0;i<nvertices;i++){   /////i<g->nvertices
        top10[i]=Dijkstra(g,i);
    }

    free_graph(g);


    // To get 10 largest dist from top10, compare the rightmost element of each list and find max
    //if a max value is found, move the maxPointer of this corresponding list left 1 step
    int output_dist[10]={-1};  //dist
    int output_endNode[10]={-1};  //endNode
    int output_startNode[10]={-1};  //startNode

    int *maxPointer;
    maxPointer=malloc(nvertices*sizeof(int));

    for (int i=0;i<nvertices;i++)
        maxPointer[i]=9;   //for each list, largest dist is at position 9

    for (int k=0;k<10;k++){
        int max=-1;   //vertex with largest dist
        for (int i=0;i<nvertices;i++){    /////i<nvertices
            if (top10[i][0][maxPointer[i]]>output_dist[k]){
                output_dist[k]=top10[i][0][maxPointer[i]];
                output_endNode[k]=top10[i][1][maxPointer[i]];
                output_startNode[k]=i;
                max=i;
            }
        }
        maxPointer[max]--;
    }

    free(maxPointer);

    for (int i=0;i<nvertices;i++){  ////i<nvertices
        free(top10[i][0]);
        free(top10[i][1]);
        free(top10[i]);
    }

    const double totalTime = GetTimer() ;
    printf("Time cost: %f s\n", totalTime/1000.0);

    FILE* fp_output=fopen("output.txt","w");
    for (int k=0;k<10;k++){
        fprintf(fp_output,"%d ",output_startNode[k]);
        fprintf(fp_output,"%d ",output_endNode[k]);
        fprintf(fp_output,"%d ",output_dist[k]);
        fprintf(fp_output,"\n");
    }
    fclose(fp_output);

    return 0;
}

int **Dijkstra(graph *g,int s){   // int s is the starting node
    int nvertices=g->nvertices;

    bool processed[nvertices];
    for (int i=0;i<nvertices;i++)
        processed[i]=false;
    heap *hp=malloc(sizeof(heap));
    initialize_heap(hp);

    int list_dist[MAXV];  //list of min dist
    int list_endNode[MAXV];  //corresponding end vertices

    //initialize starting node s
    heapNode *hNode=malloc(sizeof(heapNode));
    hNode->distance=0;
    hNode->index=s;

    // insert starting node s into min-heap
    hp->heap_size=1;
    hp->priorityQueue[0]=hNode;
    hp->pos[s]=0;
    //printf("%d\n",hp->priorityQueue[0]->index);
    int count=0;
    int pos_heap; // position of node in heap
    edgenode *p;
    int dist;      //current min dist
    int minNode;    //curent node with min dist

    while(hp->heap_size>0){     // if min-heap is not empty, continue the loop
        //printf("current heapsize %d\n",hp->heap_size);
        //print_heap(hp);
        heap_extract_min(hp,&dist,&minNode);

        //print_heap(hp);
        processed[minNode]=true;

        //for each node adjascent to minNode, relax distance
        p = g->edges[minNode];
        while (p != NULL) {
            if (processed[p->y]!=true){   //if node p has not been processed
                pos_heap=hp->pos[p->y];   //pos_heap=-1 means node never appears in heap previously

                if (pos_heap!=-1){   //if node p is old to heap,  relax p's dist
                    if (hp->priorityQueue[pos_heap]->distance>dist+p->weight){
                        heap_decrease_key(hp, pos_heap,dist+p->weight);
                        //printf("update (node dist) %d %d\n",hp->priorityQueue[pos_heap]->index,hp->priorityQueue[pos_heap]->distance);
                        //print_heap(hp);
                    }
                }
                else{       //if node p is new to heap, insert this node to heap
                    min_heap_insert(hp, dist+p->weight, p->y);
                    //print_heap(hp);
                }

            }

            p = p->next;
        }


        list_dist[count]=dist;
        list_endNode[count]=minNode;

        count++;

    }
    free_heap(hp);
    int **top10=malloc(sizeof(int*)*2);
    top10[0]=malloc(sizeof(int)*10);  //top 10 dist
    top10[1]=malloc(sizeof(int)*10);   //corresponding endNode
    if (count>=10){   //from starting s, there are more than 10 points (including iyself) connect to it
        for (int j=0;j<10;j++){
            top10[0][j]=list_dist[count-10+j];
            top10[1][j]=list_endNode[count-10+j];
        }
    }
    else{
        for (int j=0;j<10-count;j++){
            top10[0][j]=0;
            top10[1][j]=-1;
        }
        for (int j=10-count;j<10;j++){
            top10[0][j]=list_dist[count-10+j];
            top10[1][j]=list_endNode[count-10+j];
        }
    }

    return top10;
}
