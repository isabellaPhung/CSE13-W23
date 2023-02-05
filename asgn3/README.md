Isabella Phung 1702285
Winter 2023
Lab 3: Sorting out some Sorting Algorithms
____________
Description:
Program contains sorting.c, a makefile, batcher.c, quick.c, gaps.h, set.h, set.c, heap.c, heap.h, batcher.h, quick.h, stats.h, stats.c, shell.c, and shell.h. 
Computer science is a key component of data analysis. It becomes near impossible to work with large data sets without sorting them first. Countless algorithms run faster or rely on a data set being sorted, so the question of how to sort and the fastest sort is a reoccurring topic that can span courses, papers, and textbooks.
This library contains 4 sorting algorithms, Quick sort, Batcher sort, Shell sort, and Heap sort, which can all be tested by compiling the sorting.c file using the makefile. 
Further details regarding design and pseudocode can be found in the DESIGN.pdf file and further analysis regarding the efficiency of these algorithms can be found in WRITEUP.pdf.
_____________
Files:
sorting.c - main program. Can be opened in any C editor or compiled using clang with the provided Makefile. Accepts the following arguments:
           -a          Enables all sorting algorithms
           -h          Enables Heap sorting
           -b          Enables Batcher sorting
           -s          Enables Shell sorting
           -q          Enables Quick sorting
           -r seed     Sets randomized seed to given int. Default 13371453
           -n size     Sets array to specified size. Default 100
           -p elements Prints out number of elements from the array
           -H          description/help, 
heap.c - sorts a given array using heap sorting.
quick.c - sorts a given array using quick sorting.
shell.c - sorts a given array using shell sorting.
batcher.c - sorts a given array using batcher sorting.
set.c - used for user input. Defines a set as a bit vector and can manipulate these sets using set operations.
stats.c - Written by CSE13S instructors, used to manage statistics surrounding each sorting algorithm. 
makefile - compiles sorting.c with additional c files. Use via "make" command. Can also perform "make clean" which will remove any object files in the folder and "make format" which will format the .c files according to CSE13S programming spec.
Run code by entering directory and typing "make" command. This will compile sorting which can be run with ./sorting [options].
DESIGN.pdf - describes design process of program
WRITEUP.pdf - contains graphs, programming process, and resources used while creating this library of files.

