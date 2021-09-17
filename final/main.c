#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "heap.h"
#include "encode_decode.h"
#include <assert.h>

void increase_count(int counter[],int c);
void print_counter(int counter[]);
void set_bit(char *buf, int bit, int val);

int main () {
    int c;
    char *command;
    char *file_name;
    heap *hp=NULL;    //min-Heap
    int *dict[128];   // dictionary for symbol. only dict[32:127] and dict[10,13] are used for visible char and LF, CR
    for (int i = 0; i < 128; i++) dict[i] = NULL;

    while(1){

        /* interactive interface */
        printf("Please enter command:\n");

        char line[100];
        const char *spaces = "\n\t ";
        fgets(line, sizeof(line), stdin);
        command = strtok(line, spaces);   // based on command, go to various sections
        file_name=strtok(NULL, spaces);



        /* Section 1:  build a code based on freq of char in input file */

        if(strcmp(command,"import")==0) {

            //counter is array of freq for all ASCII symbols,  counter is reset to 0 when reissuing command "$import file"
            int counter[128] = {0};
            FILE *fp;
            fp = fopen(file_name, "r");
            if (fp == NULL) {
                perror("Error in opening file");
                return (-1);
            }
            while (1) {
                c = fgetc(fp);
                if (feof(fp)) {
                    break;
                }
                increase_count(counter, c);  // scan through file and count freq of each symbol
            }
            fclose(fp);

            // Build min-heap based on counter

            if (hp!=NULL)    // if re-enter this section without quit the program, old heap should be freed first
                free_heap(hp);

            hp = malloc(sizeof(heap));
            initialize_heap(hp, counter);  // initialize heap based on counter
            build_min_heap(hp);    // re-order heap  so that it follow property of min-Heap
            convert_heap_to_HuffmanTree(hp);   // Follow algo in final.pdf

            //After conversion of heap, hp->A[0] is root of HuffmanTree, A[1:NC-1] point to NULL

            free_dict(dict);       //if re-enter this section without quit the program, dict should be freed first

            // extract Dictionary from the encoding tree
            //Traverse HuffmanTree and save the code of each leaf to dict
            extract_dict_from_EncodingTree(hp->A[0], dict);

            printf("Dictionary has been extracted from imported file %s\n",file_name);
        }



        /* Section 2: encode a input file based on dictionary */

        if(strcmp(command,"encode")==0) {

            FILE *fp_encode;
            fp_encode = fopen(file_name, "r");
            FILE *fp_encode_output, *fp_encode_output_bitwise;
            // Two output file:
            // encode_output.txt store 0/1 as int,
            // encode_output_bitwise.txt store 0/1 as bits in char
            fp_encode_output = fopen("encode_output.txt", "w");
            fp_encode_output_bitwise = fopen("encode_output_bitwise.txt", "w");
            if (fp_encode == NULL) {
                perror("Error in opening file");
                return (-1);
            }

            printf("Below is encoded stream:\n");
            int length = 0;
            int bit_position=0;
            char char_bitwise;

            while (1) {
                c = fgetc(fp_encode);

                if (c<31 && c!=10 && c!=13 && c!=-1){    // we only focus on visible symbol and LF/CR/EOF
                    printf("\n");
                    printf("The input contains symbol not in my dictionary with ASCII # %d.\n",c);
                    break;
                }

                if (feof(fp_encode)) {
                    printf("\n");
                    printf("Number of bits in encode stream: %d\n", length);

                    break;
                }
                assert(dict[c]!=NULL);
                length += dict[c][0];  // count the # of bits needed for each symbol;  dict[c][0] stores length of dict[c]-1

                print_dict_element(dict[c]);   // print the encoded stream to stdout

                for (int j = 1; j <= dict[c][0]; j++){
                    fprintf(fp_encode_output, "%d", dict[c][j]);  // save 0/1 as int to file
                    set_bit(&char_bitwise, bit_position, dict[c][j]);  // save 0/1 as bit to char_bitwise
                    bit_position++;
                    if (bit_position>0 && bit_position%8==0)   // when 8 bits are saved, put the corresponding char to file
                        fputc(c,fp_encode_output_bitwise);     //may miss 1-7 bits at the end, just to test compression ratio
                }

            }
            fclose(fp_encode);
            fclose(fp_encode_output);
            fclose(fp_encode_output_bitwise);
        }



        /* Section 3: decode the input file using encoding tree */

        if(strcmp(command,"decode")==0) {
            FILE *fp_decode;
            fp_decode = fopen(file_name, "r");   // the file to be decode
            if (fp_decode == NULL) {
                perror("Error in opening file");
                return (-1);
            }

            Node *current = hp->A[0];   //current pointer in Huffman Tree, this pointer will traverse tree based on input of 0/1
            printf("Below is decoded ASCII stream:\n");
            while (1) {
                c = fgetc(fp_decode);
                if (feof(fp_decode)) {   //reach end of file
                    printf("\n");
                    if (current != hp->A[0])   //If the pointer has not go back to the root, the file is not complete
                        printf("\nError:The end of file is not complete, the last several 0/1 has not been decoded\n");
                    break;
                }
                if (c == 48) {   //input is 0 (ascii=48)
                    current = current->left;
                } else if (c == 49) {  //input is 1 (ascii=49)
                    current = current->right;
                } else {
                    printf("Input error\n");
                }
                if (current->ascii != -1) {    //reach a leaf, print out the symbol
                    printf("%c", current->ascii);
                    current = hp->A[0];    // pointer has reach the leaf, go back to root
                }
            }
            fclose(fp_decode);
        }


        /* Section 4: dump the dictionary */

        if(strcmp(command,"dump")==0) {
            printf("Below is list of dictionary:\n");
            print_dict(dict);
        }


        /* Section 5: quit */
        if(strcmp(command,"quit")==0){
            if (hp!=NULL)
                free_heap(hp);
            printf("Free heap;\n");
            free_dict(dict);
            printf("Free dictionary;\n");
            break;
        }
    }
    printf("Program has ended\n");
    return 0;
}

void increase_count(int counter[],int c){
    if (c>=0 && c<=127)
        counter[c]++;
}

void print_counter(int counter[]){  //print freq of symbols in ASCII[32~127]
    for (int i=32;i<=127;i++){
        if (counter[i]>0)
            printf("%c : %d\n",i,counter[i]);
    }
}


// This function is copied from
// https://stackoverflow.com/questions/30007665/how-can-i-store-value-in-bit-in-c-language
//It is used to  generate a file store bits by char
void set_bit(char *buf, int bit, int val)
{
    char mask = 1 << (bit % 8);
    if (val)
        *buf |= mask;
    else
        *buf &= ~mask;
}