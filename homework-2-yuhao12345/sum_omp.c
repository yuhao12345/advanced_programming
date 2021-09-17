#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<omp.h>
#define rn() (rand())/((double) RAND_MAX)

void times(int *a,int n);

int main(int argc, char **argv){
    int *a;
    int i,n, nt;
    int sum = 0;

    n  = atoi(argv[1]);
    nt = atoi(argv[2]);
    a = (int *) malloc(n*sizeof(int));

    srand(0);
    /* initial values that don't sum to too much */
    for (i=0;i<n;++i){
        if (rn() > .5)
            a[i] =  i % 10;
        else
            a[i] = -i % 10;
    }

    /* compute global sum of a */

    {

    times(a,n);

    }
    printf("sum: %d\n", a[3]);
}

void times(int *a,int n){
    int i,j;
#pragma omp parallel				\
  default(none) private(i,j) shared(a,n)		\
  num_threads(4)
#pragma omp for
    for (i=0;i<n;++i){
        for (j=0;j<2;j++){
            a[i] += 100;
        }

        printf("num of threads: %d\n",omp_get_num_threads());
    }
}