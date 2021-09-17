#include <stdlib.h>
#include "method1_3.h"
#include "timer.h"

#define k 68   /*# of arrays*/

int main() {
    int n=2;  /*number of search*/
    double *target=malloc(n*sizeof(double));
    generateRandomDouble(target,n,1e-10,12);
    char *filename="arrays.txt";
    double** input;
    int i,j;
    int *length_array=malloc(k*sizeof(int));
    input=malloc(k*sizeof(double*));
    readfile(filename, input,length_array);


    StartTimer();

    /*method 3*/

    double *augmentedArray[k];    /*data for k augmentedArray*/
    int *augPointer[2*k];       /*2 pointers for each augmentedArray*/
    int *length_augArray=malloc(k*sizeof(int));
    augmentedArray[k-1]=input[k-1];
    length_augArray[k-1]=length_array[k-1];

    augPointer[2*k-2]=malloc(length_array[k-1]*sizeof(int));
    augPointer[2*k-1]=malloc(length_array[k-1]*sizeof(int));
    for(i=0;i<length_array[k-1];i++){
        augPointer[2*k-2][i]=i;
        augPointer[2*k-1][i]=0;
    }

    for(i=k-2;i>=0;i--){
        length_augArray[i]=length_augArray[i+1]/2+length_array[i];
        augmentedArray[i]=malloc(length_augArray[i]*sizeof(double));
        augPointer[2*i]=malloc(length_augArray[i]*sizeof(int));
        augPointer[2*i+1]=malloc(length_augArray[i]*sizeof(int));

        /*i-th augmentedArray, two augPointers, i+1-th augmentedArray, i-th original array, length of i-th augmentedArray and originalArray*/
        insertAugment(augmentedArray[i],augPointer[2*i],augPointer[2*i+1],\
        augmentedArray[i+1],input[i],length_augArray[i+1],length_array[i]);
    }

    int p;  /*p is the position in augmentedArray*/

    int *pos3[n];
    int t;
    for(t=0;t<n;t++){
        pos3[t]=malloc(k*sizeof(int));
        p=binarySearch(augmentedArray[0],0,length_augArray[0]-1,target[t]);
        pos3[t][0]=augPointer[0][p];
        p=augPointer[1][p];
        for(j=1;j<k;j++){
            if(p==0){
                pos3[t][j]=augPointer[2*j][0];
                p=augPointer[2*j+1][0];
            }
            else{
                if(target[t]>augmentedArray[j][p-1]){
                    pos3[t][j]=augPointer[2*j][p];
                    p=augPointer[2*j+1][p];
                }

                else{
                    pos3[t][j]=augPointer[2*j][p-1];
                    p=augPointer[2*j+1][p-1];
                }
            }
        }
    }

    const double totalTime = GetTimer();
    double avgTime = totalTime / (double)n;

    printf("avgTime: %f ms  totTime: %f ms\n", avgTime, totalTime);
    /*printf("%d",pos3[1][15]);*/

    freeArray((void **)pos3,n);
    free(length_augArray);
    freeArray((void **)augmentedArray,k-1);
    freeArray((void **)augPointer,2*k);


    /*required for all three methods*/
    freeArray((void **)input,k);  /*free each pointer in input*/
    free(input);
    free(target);
    return 0;
}

