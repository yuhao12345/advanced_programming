#include <stdlib.h>
#include "method1_3.h"

#define k 68   /*# of arrays*/

int main() {
    double target=1.08e-1;
    char *filename="arrays.txt";
    double** input;
    int i,j;
    int *length_array=malloc(k*sizeof(int));
    input=malloc(k*sizeof(double*));
    readfile(filename, input,length_array);

    /*method 2*/
    int *pos2=malloc(k*sizeof(int));
    int sum_length=0;
    for (i=0;i<k;i++)
        sum_length+=length_array[i];
    double* unionArray=malloc(sum_length*sizeof(double));
    int *pointer[k];     /*//pointer for each element in unionArray*/
    Union_Array(input,length_array,unionArray,pointer,sum_length);
    j=binarySearch(unionArray,0,sum_length-1, target);
    for (i=0;i<k;i++){
        pos2[i]=pointer[i][j];
    }
    printPos(pos2);
    free(pos2);
    free(unionArray);
    freeArray((void **)pointer,k);

    /*required for all three methods*/
    freeArray((void **)input,k);  /*free each pointer in input*/
    free(input);
    return 0;
}
