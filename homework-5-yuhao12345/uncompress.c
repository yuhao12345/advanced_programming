#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "dictionary.h"
#include "timer.h"

int main(){
    FILE *fp_dict=fopen("test_dict.txt","r");
    FILE *fp=fopen("test_compressed.txt","r");
    FILE *fp_decompressed=fopen("test_decompressed.txt","w");

    char line[800000];
    const char *spaces = "!,.\n\t\r ";
    char *token;
    char *saveptr1;  //used in strtok_r, pointer to the 2nd splitted string


    int size_dict;
    char **dict;

    StartTimer();

    fgets(line, sizeof(line), fp_dict);
    token = strtok(line, spaces);
    size_dict=atoi(token);
    dict=malloc(size_dict*sizeof(char*));

    int i=0;
    while(fgets(line, sizeof(line), fp_dict)!=NULL)
    {
        if(line[0]!='\r'){     //get rid of new empty line '\r'
            token = strtok(line, spaces);
            dict[i]=malloc(strlen(token)*sizeof(char)+1);
            strcpy(dict[i],token);
            i++;
        }
    }
    fclose(fp_dict);

    //print_dict(dict);

    char *line_copy=malloc(800000*sizeof(char));

    while(fgets(line, sizeof(line), fp)!=NULL){
        if (line[0]=='\r' || line[0]=='\n'){
            fprintf(fp_decompressed,"\n");
        }
        else{
            strcpy(line_copy,line);  //to get punctuation, save a copy of current line
            token = strtok_r(line, spaces, &saveptr1);  //first token in this line
            if(token!=NULL){
                decompress_toText(token,&fp_decompressed,dict);
                fprintf(fp_decompressed,"%c",line_copy[saveptr1-line-1]);
            }

            token = strtok_r(NULL, spaces, &saveptr1);
            while(token!=NULL) {
                decompress_toText(token,&fp_decompressed,dict);
                fprintf(fp_decompressed,"%c",line_copy[saveptr1-line-1]);
                token = strtok_r(NULL, spaces, &saveptr1);
            }
        }
    }
    fclose(fp_decompressed);
    fclose(fp);

    const double totalTime = GetTimer() ;
    printf("Time cost to uncompress file: %f ms\n", totalTime);

    free(line_copy);

    for(i=0;i<size_dict;i++)
        free(dict[i]);
    free(dict);
}

