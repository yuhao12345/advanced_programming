#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<ctype.h>

void print_dict(char **dict){
    int i=0;
    while(dict[i]!=NULL){
        printf("%s\n",dict[i]);
        i++;
    }
}

int convert_StringToInt(char *data,char **dict,int size_dict){  //by default,data_compress=data
    assert(data!=NULL);
    assert(size_dict>0);
    for (int i=0;i<size_dict;i++){
        if (strcasecmp(dict[i],data)==0)
            return i;
    }
    return -1;   //data is not found in dict
}

void decompress_toText(char* data,FILE **fp,char **dict){
    if (data==NULL) return;
    int index;
    if (isdigit(data[0])){
        index=atoi(data);
        fprintf(*fp,"%s",dict[index]);
    }
    else
        fprintf(*fp,"%s",data);
}

void save_compressedFile_ToText(int tmp,char *token,FILE **fp){    //save dictionary to txt
    if (tmp==-1)
        fprintf(*fp,"%s",token);
    else
        fprintf(*fp,"%d",tmp);
}


//1st line is size of dictionary
void save_dict_toText(char** dict,int size_dict,FILE **fp){
    fprintf(*fp,"%d\n",size_dict);
    for (int i=0;i<size_dict;i++)
        fprintf(*fp,"%s\n",dict[i]);
}

