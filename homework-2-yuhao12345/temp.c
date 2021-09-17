#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(){
/*    int i;
#pragma omp parallel
    {
        printf("i'm great  %d\n",omp_get_thread_num());
    }*/

    int x = 5;
#pragma omp parallel private(x)
    {
        x = x+1; // dangerous
        printf("private: x is %d\n",x);
    }
    printf("after: x is %d\n",x); // also dangerous
}

