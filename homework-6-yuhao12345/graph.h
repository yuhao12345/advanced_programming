#ifndef HOMEWORK_6_YUHAO12345_GRAPH_H
#define HOMEWORK_6_YUHAO12345_GRAPH_H

#define MAXV 265214 /* maximum number of vertices */

typedef struct edgenode_{
    int y;  // vertext index
    int weight;
    struct edgenode_ *next;
} edgenode;

typedef struct graph_{
    edgenode *edges[MAXV];
    int degree[MAXV];
    int nvertices;
    int nedges;
    bool directed;
} graph;


void read_graph(graph *g, FILE *fp);

void print_graph(graph *g);

void free_graph(graph *g);




#endif //HOMEWORK_6_YUHAO12345_GRAPH_H
