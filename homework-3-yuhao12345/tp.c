#include <stdio.h>
#include <stdlib.h>


void foo(int *a){
    a[0]=0;
    a[1]=2;
}

void main(){
    int a[2];
    foo(a);
    printf("%d\n",a[1]);
}

