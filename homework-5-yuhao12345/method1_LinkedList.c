#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "LinkedList.h"
#include "timer.h"
#include "dictionary.h"

int main(int argc, char *argv[]) {
    int length_threshold=atoi(argv[1]);
    int freq_threshold=atoi(argv[2]);

    FILE *fp=fopen("test1.txt","r");
    if (NULL == fp){
        perror("opening database");
    }

    char line[800000];
    const char *spaces = "!,.\n\t ";
    char *token;
    char *saveptr1;  //used in strtok_r, pointer to the 2nd splitted string

    StartTimer();

    //initialize linkedlist and insert all words into the list
    List *list=malloc(sizeof(List));
    list_init(list);

    while(fgets(line, sizeof(line), fp)!=NULL)
    {
        if(line[0]!='\r'){     //get rid of new empty line '\r'
            //printf("%s\n",line);
            token = strtok(line, spaces);  //first token in this line
            list_append_check_duplicate(list,token);
            while(token!=NULL) {
                token = strtok(NULL, spaces);
                list_append_check_duplicate(list,token);
            }
        }
    }
    //print_list(list);

    //extract dictionary from list and save it to string array char** dict
    char** dict;
    int size_dict;
    dict=extract_dict(list, length_threshold, freq_threshold,&size_dict);

    //printf("size of dict: %d\n",size_dict);
    //print_dict(dict);

    free_list(list);

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
