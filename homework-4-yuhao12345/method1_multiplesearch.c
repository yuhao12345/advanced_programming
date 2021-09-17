#include <stdlib.h>
#include "method1_3.h"
#include "timer.h"

#define k 68   /*# of arrays*/

int main() {
    int n=1000000;  /*number of search*/
    double *target=malloc(n*sizeof(double));
    generateRandomDouble(target,n,1e-10,12);
    char *filename="arrays.txt";
    double** input;
    int i;
    int *length_array=malloc(k*sizeof(int));
    input=malloc(k*sizeof(double*));
    readfile(filename, input,length_array);

    StartTimer();

    /*method 1*/
    int *pos1[n];
    int t;
    for(t=0;t<n;t++){
        pos1[t]=malloc(k*sizeof(int));
        for(i=0;i<k;i++){
            pos1[t][i]=binarySearch(input[i],0,length_array[i]-1,target[t]);
        }
    }


    const double totalTime = GetTimer() ;
    double avgTime = totalTime / (double)n;

    printf("avgTime: %f ms  totTime: %f ms\n", avgTime, totalTime);
    /*printf("%d",pos1[1][15]);*/

    freeArray((void **)pos1,n);

    /*required for all three methods*/
    freeArray((void **)input,k);  /*free each pointer in input*/
    free(input);
    free(target);
    return 0;
}

