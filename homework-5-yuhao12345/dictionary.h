#ifndef HOMEWORK_5_YUHAO12345_DICTIONARY_H
#define HOMEWORK_5_YUHAO12345_DICTIONARY_H

#include<stdio.h>
#include<stdlib.h>

void print_dict(char **dict);

int convert_StringToInt(char *data,char **dict,int size_dict);

void save_compressedFile_ToText(int tmp,char *token,FILE **fp);

void save_dict_toText(char** dict,int size_dict,FILE **fp);

void decompress_toText(char* data,FILE **fp,char **dict);

#endif //HOMEWORK_5_YUHAO12345_DICTIONARY_H
