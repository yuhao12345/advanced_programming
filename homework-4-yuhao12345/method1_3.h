#include <string.h>
#include <assert.h>
#include <stdio.h>

#define k 68   /*# of arrays*/

/* for method3*/
void insertAugment(double *augmentedArray,int *augPointer1,int *augPointer2,double *augmentedArray_next,\
double *originArray,int length_augArray_next,int length_array_current){
    int length=length_array_current+length_augArray_next/2;

    int i;
    int currentPos1=0,currentPos2=1;   /*current min of originArray,  augmentedArray_next*/
    for(i=0;i<length;i++){
        if(currentPos1>=length_array_current){
            augmentedArray[i]=augmentedArray_next[currentPos2];
            augPointer2[i]=currentPos2;
            augPointer1[i]=currentPos1;
            currentPos2+=2;
        }
        else if(currentPos2>=length_augArray_next){
            augmentedArray[i]=originArray[currentPos1];
            augPointer1[i]=currentPos1;
            augPointer2[i]=currentPos2;
            currentPos1++;
        }
        else if(originArray[currentPos1]<augmentedArray_next[currentPos2]){
            augmentedArray[i]=originArray[currentPos1];
            augPointer1[i]=currentPos1;
            augPointer2[i]=currentPos2;
            currentPos1++;
        }
        else{
            augmentedArray[i]=augmentedArray_next[currentPos2];
            augPointer2[i]=currentPos2;
            augPointer1[i]=currentPos1;
            currentPos2+=2;
        }
    }
}

/*for method2*/
void Union_Array(double** input,int *length_array,double* unionArray,int *pointer[],int sum_length){
    int currentPos[k]= {0};  /*pointer to current minimum for k arrays*/
    int i,j,min_pos;
    double min;
    for(j=0;j<k;j++)
        pointer[j]=malloc(sum_length*sizeof(int));
    for(i=0;i<sum_length;i++){
        min=10000.0;
        min_pos=-1;
        for(j=0;j<k;j++){
            if (currentPos[j]<=length_array[j]-1)   /*there is still element left in array j*/
                if(input[j][currentPos[j]]<min){
                    min=input[j][currentPos[j]];
                    min_pos=j;
                }
        }
        unionArray[i]=min;

        for(j=0;j<k;j++){
            pointer[j][i]=currentPos[j];
        }
        currentPos[min_pos]++;  /*move min-pointer to next element*/
    }
}

int binarySearch(double *array,int i,int j, double target){
    assert(i<=j);
    int mid=(i+j)/2;
    if(i==j){
        if (array[i]<target) return i+1;
        return i;
    }
    if(array[mid]==target)
        return mid;
    if(array[mid]<target)
        return binarySearch(array,mid+1,j,target);
    else
        return binarySearch(array,i,mid,target);
}

int readfile(char *filename, double** input, int *length_array){
    FILE *fp=fopen(filename,"r");

    char line[8000000];
    const char *spaces = "\n\t ";
    char *token;
    int length,i,j;
    double tmp;


    if (NULL == fp)
    {
        perror("opening database");
        return (-1);
    }

    i = 0;
    while(fgets(line, sizeof(line), fp))
    {
        token = strtok(line, spaces);
        length=atoi(token);    /*length for each array*/
        length_array[i]=length;
        input[i]=malloc(length*sizeof(double));
        token = strtok(NULL, spaces);

        for(j=0;j<length;j++)
        {
            tmp = atof(token);
            input[i][j] = tmp;
            token = strtok(NULL, spaces);  /*next token*/
        }
        i++;
    }
    fclose(fp);
}

int freeArray(void** input,int n){
    for (int i=0;i<n;i++)
        free(input[i]);
    return 0;
}

void printPos(int *pos){
    int i;
    for(i=0;i<k;i++)
        printf("%d ",pos[i]);
    printf("\n");
}

void generateRandomDouble(double *target,int n,double min,double max){
    int i;
    for(i=0;i<n;i++)
        target[i]=(double)rand()/RAND_MAX*(max-min)+min;
}