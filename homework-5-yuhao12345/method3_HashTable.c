#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "HashTable.h"
#include "timer.h"
#include "dictionary.h"

int main(int argc, char *argv[]) {
    int length_threshold=atoi(argv[1]);
    int freq_threshold=atoi(argv[2]);

    FILE *fp=fopen("test_document.txt","r");
    if (NULL == fp){
        perror("opening database");
    }

    char line[800000];
    const char *spaces = "!,.\n\t\r ";
    char *token;
    char *saveptr1;  //used in strtok_r, pointer to the 2nd splitted string

    StartTimer();


    //method 3
    // scan txt and get number of words nbins
    int nbins=0;
    while(fgets(line, sizeof(line), fp)!=NULL)
    {
        if(line[0]!='\r'){     //get rid of new empty line '\r'
            token = strtok(line, spaces);  //first token in this line
            if (token!=NULL){
                nbins++;
            }
            token = strtok(NULL, spaces);
            while(token!=NULL) {
                nbins++;
                token = strtok(NULL, spaces);
            }
        }
    }
    //printf("%d\n",nbins);

    List* hashTable=hashTable_init(nbins);

    rewind(fp);   //fp points to the beginning of file again
    while(fgets(line, sizeof(line), fp)!=NULL)
    {
        if(line[0]!='\r'){     //get rid of new empty line '\r'
            token = strtok(line, spaces);  //first token in this line
            hash_insert_check_duplicate(&hashTable,token, nbins);
            while(token!=NULL) {
                token = strtok(NULL, spaces);
                hash_insert_check_duplicate(&hashTable,token, nbins);
            }
        }
    }
    //print_HashTable(hashTable,nbins);

    char **dict=malloc(500*sizeof(char *));
    int size_dict;
    extract_dict_from_HashTable(hashTable, nbins, length_threshold, freq_threshold, dict, &size_dict);

    //print_dict(dict);

    free_HashTable(hashTable,nbins);


    //scan original file again and convert word to Int based on dictionary
    //write compressed file to txt file
    FILE* fp_compressed=fopen("test_compressed.txt","w");
    rewind(fp);   //fp points to the beginning of file again

    int tmp;
    char *line_copy=malloc(800000*sizeof(char));
    while(fgets(line, sizeof(line), fp)!=NULL)
    {
        if (line[0]=='\r' || line[0]=='\n'){
            fprintf(fp_compressed,"\n");
        }
        else{
            strcpy(line_copy,line);  //to get punctuation
            token = strtok_r(line, spaces, &saveptr1);  //first token in this line
            if(token!=NULL){      //don't know why token can be null in the first position, anyway, add this to git rid of error
                tmp=convert_StringToInt(token,dict,size_dict);
                save_compressedFile_ToText(tmp,token,&fp_compressed);  //fprintf string or Int based on if tmp==-1
                fprintf(fp_compressed,"%c",line_copy[saveptr1-line-1]);
                token = strtok_r(NULL, spaces, &saveptr1);
                while(token!=NULL) {
                    tmp=convert_StringToInt(token,dict,size_dict);
                    save_compressedFile_ToText(tmp,token,&fp_compressed);
                    fprintf(fp_compressed,"%c",line_copy[saveptr1-line-1]);
                    token = strtok_r(NULL, spaces, &saveptr1);
                }
            }
            //fprintf(fp_compressed,"a\n");
        }
    }

    fclose(fp_compressed);
    fclose(fp);
    free(line_copy);

    const double totalTime = GetTimer() ;
    printf("Time cost to compress file: %f ms\n", totalTime);


    //save dict to TXT
    FILE* fp_dict=fopen("test_dict.txt","w");
    save_dict_toText(dict,size_dict,&fp_dict);
    fclose(fp_dict);

    for(int i=0;i<size_dict;i++)
        free(dict[i]);
    free(dict);

    return 0;
}

