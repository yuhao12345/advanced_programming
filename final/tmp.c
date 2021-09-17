#include <stdlib.h>
#include<stdio.h>

void set_bit(char *buf, int bit, int val);
int get_bit(char buf, int bit);

void main(){
    char c;
    set_bit(&c,0,1);
    set_bit(&c,1,1);
    set_bit(&c,2,0);
    set_bit(&c,3,1);
    set_bit(&c,4,0);
    set_bit(&c,5,0);
    set_bit(&c,6,0);
    set_bit(&c,7,1);

    set_bit(&c,0,1);
    set_bit(&c,1,0);
    set_bit(&c,2,0);
    set_bit(&c,3,1);
    set_bit(&c,4,0);
    set_bit(&c,5,1);
    set_bit(&c,6,0);
    set_bit(&c,7,1);

    printf("%d\n",get_bit(c, 5));
    printf("%02x\n",c);
    printf("%02x\n", (unsigned int) c);

    FILE *fp;
    fp = fopen("tmp.txt", "w");
    fputc(c,fp);
    fclose(fp);

    fp = fopen("tmp.txt", "r");
    int cc = fgetc(fp);
    printf("%c\n",(char)cc);
    for (int i=0;i<8;i++){
        printf("%d", cc >> i & 0x01);
        //printf("%d ",get_bit((char)cc, i));
    }
    fclose(fp);
}

void set_bit(char *buf, int bit, int val)
{
    int byte = bit / 8;
    char mask = 1 << (bit % 8);
    if (val)
        *buf |= mask;
    else
        *buf &= ~mask;
}

int get_bit(char buf, int bit)
{
    int byte = bit / 8;
    char mask = 1 << (bit % 8);
    return buf & mask ? 1 : 0;
}