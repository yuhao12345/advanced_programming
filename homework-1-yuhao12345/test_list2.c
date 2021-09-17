#include "list.h"
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include<math.h>

#define N 20000
typedef struct Point_{
    int x;
    int y;
    int z;
} Point;

char* Point2str(void *data);  /* return string of pair*/
int Point_destroy(void *data); /* how to free a pair */
int list_destroy(void *data);
Point* newPoint(int x,int y,int z); /* create a new instance of pair */
int matchPoint(const void* data1,const void* data2);
void write_file(List* list, int n);
float distance(Point *p1,Point *p2);

int main(int argc, char **argv){
    int i,j;
    LE *e;
    Point *p;
    time_t start_t, end_t;
    double diff_t;
    float dist,tp;

    List *list=(List *)malloc(sizeof(List));

    /*create a list of array*/
    printf("---Initialize a list---\n");
    list_init(list,list_destroy,&matchPoint,Point2str);
    p=newPoint(1,1,1);
    list_ins_next(list,NULL,p);  /*insert at head*/
    printf("---create a list of size %d---\n",N);
    e=list->head;
    for (i=0;i<N;i++){
        p=newPoint(i/3,i%3,i*2);
        list_ins_next(list,e,p);

        e=e->next;
        /*list_print(list);*/
    }
    write_file(list, N);
    printf("save coordinates of points to data_points.txt\n");

    printf("---only print the first 10 points---\n",N);
    /*list_print(list);*/

    for (e=list->head,i=0;i<10;e=e->next,i++){
        printf("%s ",list->tostr(e->data));
    }
    printf("\n");


    list_rem_next(list,NULL);

    p=newPoint(-1,3,2);
    list_add(list,2,p);

    printf("---read the value at specfic position---\n");
    p=(Point*)list_element_at(list,3);
    printf("Value of element 3:%s\n",Point2str(p));


    /*search a pair*/
    printf("---search a value in the list---\n");
    Point *target;
    target=newPoint(2,1,14);
    int position=list_find_first(list,target);

    printf("The index of target [2,1,14] is %d\n",position);


    /*Performance comparison between list and array*/
    /*calculate average distance to other points*/
    printf("---Performance comparison between list and array---\n");
    printf("Operations: calculate average distance to other points for each point\n");
    printf("--1. time cost of list--\n");
    printf("calculate average distance\n",N);
    time(&start_t);
    LE *el1,*el2;
    float average_dist[N];
    el1=list->head;
    for (i=0;i<N;i++){
        dist=0.0;
        el2=list->head;
        for (j=0;j<N;j++){
            dist+=distance(el1->data,el2->data);
            el2=el2->next;
        }
        average_dist[i]=dist/N;
        el1=el1->next;
    }
    time(&end_t);
    diff_t = difftime(end_t, start_t);
    printf("List costs %8.1f s\n ",N, diff_t);
    FILE *file = fopen("data_averageDistance.txt", "w");
    for (i=0;i<N;i++){
        tp=average_dist[i];
        fprintf(file, "%f\n", tp);
    }

    fclose(file);
    printf("save average distance to data_averageDistance.txt\n");
    list->destroy(list);


    printf("--2. time cost of array--\n");
    Point* pointArray;
    pointArray=malloc(N*sizeof(Point));
    printf("create an array of size %d (not included in time count)\n",N);
    for (i=0;i<N;i++){
        pointArray[i].x=i/3;
        pointArray[i].y=i%3;
        pointArray[i].z=i*2;
    }
    /*calculate the average distance for array*/
    printf("calculate average distance\n",N);
    time(&start_t);
    for (i=0;i<N;i++){
        dist=0.0;
        /*el2=list->head;*/
        for (j=0;j<N;j++){
            dist+=distance(&pointArray[i],&pointArray[j]);

        }
        average_dist[i]=dist/N;
    }
    time(&end_t);
    diff_t = difftime(end_t, start_t);
    printf("Array costs %8.1f s\n ",N, diff_t);


    Point_destroy(target);
    free(pointArray);
    return 0;
}

char* Point2str(void *data){
    static char str[10];
    Point *p=(Point*)data;
    sprintf(str,"[%d,%d,%d]",p->x,p->y,p->z);
    return str;
}
int Point_destroy(void *data){
    Point *p=(Point *)data;
    free(p);
    return 0;
}
int list_destroy(void *data){
    List *list=(List *)data;
    LE *current,*next;

    if (list->head==NULL){
        free(list);
        return 1;
    }
    int i,n=list->size;
     current=list->head;

     for(i=0;i<n;i++){
         next=current->next;
         free(current->data);
         free(current);
         current=next;
     }
     free(list);

     return 1;
}
Point* newPoint(int x,int y,int z){
    Point *p=malloc(sizeof(Point));
    p->x=x;
    p->y=y;
    p->z=z;
    return p;
}
int matchPoint(const void* data1,const void* data2){
    Point* p1=(Point *)data1;
    Point* p2=(Point *)data2;
    if (p1->x==p2->x && p1->y==p2->y && p1->z==p2->z)
        return 1;
    return 0;
}
void write_file(List* list, int n){
    int i;
    Point* p;
    LE* curr=list->head;
    FILE *file = fopen("data_points.txt", "w");
    for (i=0;i<n;i++){
        p=curr->data;
        fprintf(file, "%d %d %d\n", p->x, p->y, p->z);
        curr=curr->next;
    }

    fclose(file);
}
float distance(Point *p1,Point *p2){
    return sqrt((p1->x-p2->x)*(p1->x-p2->x)+(p1->y-p2->y)*(p1->y-p2->y)+(p1->z-p2->z)*(p1->z-p2->z));
}

