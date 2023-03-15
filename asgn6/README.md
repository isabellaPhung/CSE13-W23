Isabella Phung 1702285
Winter 2023
Lab 5: Lmpl-Ziv Cmpresn
____________
Description:
Program contains encode.c, decode.c, trie.c, trie.h, word.c, word.h, io.c, io.h, endian.h, code.h, and a Makefile. 
The following library implements Lempel-Ziv Compression. It is not functioning right now.
This library contains 2 executable programs, encode and decode, which can all be tested by compiling the corresponding c files using the provided makefile. 
Further details regarding design and pseudocode can be found in the DESIGN.pdf file and further a description of the learning process can be found in WRITEUP.pdf.
_____________
Files:
encode.c - main program. Compresses an input or file. Can be opened in any C editor or compiled using clang with the provided Makefile. Accepts the following arguments:
           -v            Verbose output. Prints statistics of compression. Default: off
           -i inputfile  Name of file with contents to encrypt (Default: stdin) 
           -o outputfile Name of file to print encrypted message (Default: stdout)
           -h          description/help
decode.c - main program. Decompresses a file compressed with Lempel-Ziv. Can be opened in any C editor or compiled using clang with the provided Makefile. Accepts the following arguments:
           -i inputfile  Name of file with contents to encrypt (Default: stdin) 
           -o outputfile Name of file to print encrypted message (Default: stdout)
           -v            Verbose output. Prints statistics of decompression. Default: off
           -h          description/help 
trie.c - creates a trie data structure for compressing the file.
word.c - creates a word and wordtable data structure from decompression.
io.c - performs bit wise operations for reading and outputting bit information. 
makefile - compiles encode.c and decode.c with the additional c files. Use via "make" command. The individual programs can also be compiled using "make decode", and "make encode". Can also perform "make clean" which will remove any object files in the folder and "make format" which will format the .c files according to CSE13S programming spec.

Run code by entering directory and typing "make" command. This will compile all three encryption files which can be run with ./[decode/encode] [options].
DESIGN.pdf - describes design process of program
WRITEUP.pdf - contains graphs, programming process, and resources used while creating this library of files.

