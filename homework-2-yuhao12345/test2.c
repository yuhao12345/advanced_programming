#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

#define NT 4
typedef struct params{
    int    tid;
    long   ng;
    int    nl;
    int    strt;
    double  *arr;
    double lsum;
} Params;

void *work(void *arg);

/*double *arr;*/

int main(int argc, char **argv){
    long i,n;
    void *status;
    Params p[NT];
    pthread_t t[NT];
    double gsum = 0;
    double *arr;

    n = atol(argv[1]);
    arr = (double *) malloc(n*sizeof(double));

    /* initialize array */
    for (i=0;i<n;++i)
        arr[i] = i % 2;

    for (i=0;i<NT;++i){
        p[i].arr  = arr;
        p[i].tid  = i;
        p[i].ng   = n;
        p[i].nl   = n/NT; /* assume equally divisible */
        p[i].strt = p[i].nl*i;
        p[i].lsum = 0.0;
        pthread_create(&t[i], NULL, work,(void*) &p[i]);
    }

    for(i=0;i<NT;i++) {
        pthread_join(t[i], &status);
        /*gsum += p[i].lsum;*/
    }
    printf("%f\n", arr[3]);
    pthread_exit(NULL);
}

void *work(void* args){
    int i;
    Params *p = (Params *)args;
    int strt = p->strt;
    int end = strt + p->nl - 1;
    for (i=strt;i<=end;++i)
        p->arr[i] += 2;
    return NULL;
}

