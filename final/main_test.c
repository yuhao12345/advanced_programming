#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "heap.h"
#include "encode_decode.h"
#include <assert.h>

void increase_count(int counter[],int c);
void print_counter(int counter[]);
void set_bit(char *buf, int bit, int val);
int get_bit(char buf, int bit);

int main () {

    int c;
    char *command;
    char *file_name;
    heap *hp=NULL;


    int *dict[128];   // only dict[32:127] and dict[10,13] are used for visible char and LF, CR
    for (int i = 0; i < 128; i++) dict[i] = NULL;



        /* interactive interface */
/*
        printf("Please enter command:\n");

        char line[100];
        const char *spaces = "\n\t ";
        fgets(line, sizeof(line), stdin);
        command = strtok(line, spaces);   // based on command, go to various sections
        file_name=strtok(NULL, spaces);
*/



        /* Section 1:  build a code based on freq of char in input file */


            //record freq of char, counter is reset to 0 everytime
            int counter[128] = {0};
            FILE *fp;
            fp = fopen("sample_text.txt", "r");
            if (fp == NULL) {
                perror("Error in opening file");
                return (-1);
            }
            while (1) {
                c = fgetc(fp);
                if (feof(fp)) {
                    break;
                }
                increase_count(counter, c);
            }
            fclose(fp);
            //print_counter(counter);

            if (hp!=NULL)    // if re-enter this section without quit the program, old heap should be freed first
                free_heap(hp);

            hp = malloc(sizeof(heap));
            initialize_heap(hp, counter);  //initialize heap based on counter
            build_min_heap(hp);
            convert_heap_to_HuffmanTree(hp);

            //print_heap(hp);
            //check_Tree(hp->A[0]);     //check all node with symbol is on leaf after conversion


            //After conversion of heap, hp->A[0] is root of HuffmanTree, A[1:NC-1] point to NULL

            // extract Dictionary from the encoding tree

            free_dict(dict);       //if re-enter this section without quit the program, dict should be freed first


            extract_dict_from_EncodingTree(hp->A[0], dict);

    free_dict(dict);

    extract_dict_from_EncodingTree(hp->A[0], dict);

    printf("Dictionary has been extracted from imported file\n");




        /* Section 2: encode a input file based on dictionary */


    char char_bitwise;


            FILE *fp_encode;
            fp_encode = fopen("sample_text.txt", "r");
            FILE *fp_encode_output,* fp_encode_output_bitwise;
            fp_encode_output = fopen("encode_output.txt", "w");
            fp_encode_output_bitwise = fopen("encode_output_bitwise.txt", "w");
            if (fp_encode == NULL) {
                perror("Error in opening file");
                return (-1);
            }

            printf("Below is encoded stream:\n");
            int length = 0;
            int bit_position=0;
            while (1) {
                c = fgetc(fp_encode);

                if (feof(fp_encode)) {
                    printf("\n");
                    printf("Number of bits in encode stream: %d\n", length);

                    break;
                }
                assert(dict[c]!=NULL);
                length += dict[c][0];

                print_dict_element(dict[c]);

                for (int j = 1; j <= dict[c][0]; j++){
                    set_bit(&char_bitwise, bit_position, dict[c][j]);
                    bit_position++;
                    if (bit_position>0 && bit_position%8==0)
                        fputc(c,fp_encode_output_bitwise);
                    fprintf(fp_encode_output, "%d", dict[c][j]);
                }

            }
            fclose(fp_encode);
            fclose(fp_encode_output);
            fclose(fp_encode_output_bitwise);





        /* Section 3: decode the input file using encoding tree */


            FILE *fp_decode_bitwise;
            fp_decode_bitwise = fopen("encode_output_bitwise.txt", "r");   // the file to be decode
            if (fp_decode_bitwise == NULL) {
                perror("Error in opening file");
                return (-1);
            }

            Node *current = hp->A[0];   //current pointer in Huffman Tree, this pointer will traverse tree based on input of 0/1
            printf("Below is decoded ASCII stream:\n");
            while (1) {
                c = fgetc(fp_decode_bitwise);
                if (feof(fp_decode_bitwise)) {
                    printf("\n");
                    if (current != hp->A[0])   //If the pointer has not go back to the root, the file is not complete
                        printf("\nError:The end of file is not complete, the last several 0/1 has not been decoded\n");
                    break;
                }
                for (int i=0;i<8;i++) {
                    if ((c >> i & 0x01) == 0) {
                        printf("0");
                        current = current->left;
                    }
                    else{
                        printf("1");
                        current = current->right;
                    }


/*                if (c == 48) {   //input is 0 (ascii=48)
                    current = current->left;
                } else if (c == 49) {  //input is 1 (ascii=49)
                    current = current->right;
                } else {
                    printf("Input error\n");
                }*/
                    if (current->ascii != -1) {
                        //printf("%c", current->ascii);
                        current = hp->A[0];    // pointer has reach the leaf, go back to root
                    }
                }
            }
            fclose(fp_decode_bitwise);



        /* Section 4: dump the dictionary */


            printf("Below is list of dictionary:\n");
            //print_dict(dict);



        /* Section 5: quit */

            free_heap(hp);
            printf("Free heap;\n");
            free_dict(dict);
            printf("Free dictionary;\n");



    printf("Program is ended\n");
    return 0;
}

void increase_count(int counter[],int c){
    if (c>=0 && c<=127)
        counter[c]++;
}

void print_counter(int counter[]){
    for (int i=32;i<=127;i++){
        if (counter[i]>0)
            printf("%c : %d\n",i,counter[i]);
    }
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