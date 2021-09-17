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
    int i,j;
    int *length_array=malloc(k*sizeof(int));
    input=malloc(k*sizeof(double*));
    readfile(filename, input,length_array);

    StartTimer();


    /*method 2*/

    int sum_length=0;
    for (i=0;i<k;i++)
        sum_length+=length_array[i];
    double* unionArray=malloc(sum_length*sizeof(double));
    int *pointer[k];     /*//pointer for each element in unionArray*/
    Union_Array(input,length_array,unionArray,pointer,sum_length);

    int *pos2[n];
    int t;
    for(t=0;t<n;t++){
        pos2[t]=malloc(k*sizeof(int));
        j=binarySearch(unionArray,0,sum_length-1, target[t]);
        for (i=0;i<k;i++){
            pos2[t][i]=pointer[i][j];
        }
    }

    const double totalTime = GetTimer();
    double avgTime = totalTime / (double)n;

    printf("avgTime: %f ms  totTime: %f ms\n", avgTime, totalTime);
    /*printf("%d",pos2[1][15]);*/

    freeArray((void **)pos2,n);
    free(unionArray);
    freeArray((void **)pointer,k);

    /*required for all three methods*/
    freeArray((void **)input,k);  /*free each pointer in input*/
    free(input);
    free(target);
    return 0;
}
