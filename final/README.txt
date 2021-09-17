1. Start program:


gcc -o final main.c heap.c encode_decode.c
./final


OR


make
./final



2. Input commands:

import sample_text.txt

encode sample_text.txt

decode encode_output.txt

dump

quit



3. Some Notes:


1)

In "encoding" part:

I output two files: 

encode_output.txt    :  0/1 are stored as int in text file
and    
encode_output_bitwise.txt  :  0/1 are saved as bit and stored as char in text file.
 
The latter one is just used to calculate the compression ratio. I do not decode it in the latter section.


In "decoding" part:

I use encode_output.txt to recover the original text.



2) I choose the option to add all ASCII symbols with 0 frequency into the code.

And all visible ASCII symbols are listed "dump" the dictionary.


3) The number of bits in the encoding stream for "sample_text.txt" is 14488, which ~ 1.8 kb.

This is consistent with the size of encode_output_bitwise.txt", which store 0/1 as bits.

The original file is 3.27kb, with compression rate 55%.







