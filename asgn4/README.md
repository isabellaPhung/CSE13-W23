Isabella Phung 1702285
Winter 2023
Lab 4: Life in True and False 
____________
Description:
Program contains life.c, universe.c, and universe.h. 
The Game of Life by Conway is a well known concept that serves as a simple but effective example of simulations. While it may seem deceptively simple at first, this and many more celular simulations can be used to represent the behavior of single celled organisms and their gradual evolution. One might initially envision a bunch of random cells but the reality is that, thanks to the simple rules provided, Conway's Game of Life produces complex patterns thanks to the cells interacting with one another.
This small library recreates Conway's Game of Life in text format. It can accept and output files of the final universes and these universes can be flat or toroid. It can be tested by compiling the life.c file using the provided makefile. 
Further details and resources regarding design and pseudocode can be found in the DESIGN.pdf file and additional analysis regarding the efficiency of these algorithms can be found in WRITEUP.pdf.
_____________
Files:
life.c - main program. Can be opened in any C editor or compiled using clang with the provided Makefile. Accepts the following arguments:
           -t               Specifies universe is toroidal (aka continuous)
           -s               Prevents text visual of game from appearing
           -i input         Enter input file for populating universe.
                            Format specified below. Defaults to console input.
           -n generations   Indicate number of gernations universe goes through.
                            Defualts to 100 generations.
           -o output        Specify name of output file for final universe.
                            Defaults to printing to console.
           -H               description/help 
universe.c - contains necessary functions to create and simulate Conways' Game of Life. Detail regarding each functions purpose and behavior can be found in DESIGN.pdf. 
makefile - compiles life.c with additional c files. Use via "make" command. Can also perform "make clean" which will remove any object files in the folder and "make format" which will format the .c files according to CSE13S programming spec.
Run code by entering directory and typing "make" command. This will compile life, which can be run with ./life [options].
DESIGN.pdf - describes design process of program
WRITEUP.pdf - contains graphs, programming process, and resources used while creating this library of files.
Input file format:
Input files must have the following format, where the first row indicates the size of the universe and all consecutive rows indicate live cells at the indicated coordinates.
[rows] [columns]
[row] [column]
[row] [column]
...
...


