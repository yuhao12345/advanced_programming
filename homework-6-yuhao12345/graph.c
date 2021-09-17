#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "graph.h"

void initialize_graph(graph *g){
    int i;
    g -> nvertices = 0;
    g -> nedges = 0;
    g -> directed = true;
    for (i=0; i<MAXV; i++)
        g->degree[i] = 0;
    for (i=0; i<MAXV; i++)
        g->edges[i] = NULL;
}

void insert_edge(graph *g, int x, int y, int weight){
    edgenode *p;
    p = malloc(sizeof(edgenode));

    p->weight = weight;
    p->y = y;
    p->next = g->edges[x];
    g->edges[x] = p;
    g->degree[x] ++;
    g->nedges ++;
}

void read_graph(graph *g, FILE *fp){
    int i;
    int nedges;
    int x, y, weight;
    initialize_graph(g);

    fscanf(fp,"%d %d",&(g->nvertices),&nedges);
    //printf("|V|=%d, |E|=%d\n",g->nvertices,nedges);

    for (i=1; i<=nedges; i++) {
        fscanf(fp,"%d %d %d",&x,&y,&weight);
        insert_edge(g,x,y,weight);
    }
    assert(nedges==g->nedges);
}


void print_graph(graph *g){
    int i;
    edgenode *p;

    for (i=0; i<=3; i++) {
        printf("%d: ",i);
        p = g->edges[i];
        while (p != NULL) {
            printf(" %d",p->y);
            p = p->next;
        }
        printf("\n");
    }
}


void free_graph(graph *g){
    edgenode *tmp, *p;
    for (int i=0;i<g->nvertices;i++){
        p=g->edges[i];
        while (p != NULL){
            tmp=p->next;
            free(p);
            p=tmp;
        }
    }

    free(g);
}
