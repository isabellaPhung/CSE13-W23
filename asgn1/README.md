Isabella Phung 1702285
Winter 2023
Lab 1: Monte Carlo: Estimating Pi using Coconuts
_____________
Description:
Program contains monte_carlo.c, Makefile, plot.sh. On an abandoned island with nothing but a coconut tree, how do you estimate pi? You can draw a square with the coconut tree in the center, then inscribe a circle inside. Continually drop coconuts and you should be able to estimate the value of pi. monte_carlo.c will output x and y values of said randomly falling coconuts. plot.sh analyses the output from monte_carlo.c and assembles the data into graphs. Further detail regarding the monte carlo algorithm elaborated upon in WRITEUP.pdf.
_____________
Files:
monte_carlo.c - main program. Can be opened in any C editor or compiled using clang with Makefile. Accepts -r <int number> to indicate a predetermined seed and -n <int number> to indicate the number of iterations to perform.
Makefile - compiles monte_carlo.c. Use via "make" command
plot.sh - run after compiling monte_carlo.c. Will generate two plots. One that shows the random points in and outside of the circle. And another that shows the error of the monte_carlo program relative to an accepted value of pi over multiple iterations.
Run code by entering directory and typing "make" command. This will compile monte_carlo.c. plot.sh can then be run with chmod +x plot.sh, after that you can type ./plot.sh to run to produce the described plots in pdf form.
DESIGN.pdf - describes design process of program
WRITEUP.pdf - contains graphs and summary of monte_carlo program