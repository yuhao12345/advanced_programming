#include <stdlib.h>
#include "method1_3.h"

#define k 68   /*# of arrays*/

int main() {
    double target=1.08e-1;
    char *filename="arrays.txt";
    double** input;
    int i;
    int *length_array=malloc(k*sizeof(int));
    input=malloc(k*sizeof(double*));
    readfile(filename, input,length_array);

    /*method 1*/
    int *pos1=malloc(k*sizeof(int));
    for(i=0;i<k;i++){
        pos1[i]=binarySearch(input[i],0,length_array[i]-1,target);
    }
    printPos(pos1);
    free(pos1);

    /*required for all three methods*/
    freeArray((void **)input,k);  /*free each pointer in input*/
    free(input);
    return 0;
}

