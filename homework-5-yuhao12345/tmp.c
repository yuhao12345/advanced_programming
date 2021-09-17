#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int main(){
    char *word=malloc(3*sizeof(char));
    int nbins=5;
    word[0]='d';
    word[1]='r';
    word[2]='g';
    unsigned int h = 0;
    int c;
    while(c = *word++){
        printf("c %d\n",c);
        h += c;

    }

    printf("%d\n",h % nbins) ;

}

