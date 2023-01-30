Isabella Phung 1702285
Winter 2023
Lab 2: Approximating Mathematical Real Number Constants in C
_____________
Description:
Program contains mathlib-test.c, madhava.c, bbp.c, newton.c, e.c, euler.c, and viete.c. While computers may seem capable of manipulating endless decimals in all kinds of mathematical acrobatics, the truth is that computers are only capable of approximating most decimal values. Binary numbers fundamentally are limited when encoding decimal values. This program demonstrates a variety of techniques that can be used to estimate irrational constants such as pi and e. Further details regarding the algorithms can be found in DESIGN.pdf and the process of writing this library can be found in WRITEUP.pdf.
_____________
Files:
mathlib-test.c - main program. Can be opened in any C editor or compiled using clang with makefile. Accepts the following arguments:
           -a  Runs all tests
           -e  Runs e approimation
           -b  Runs Bailey-Borwein-Plouffe pi approximation
           -m  Runs Madhava pi approximation
           -r  Runs Euler sequence pi approximation
           -v  Runs Viete pi approximation
           -n  Runs Newton square root approximations
           -s  Prints statistics to see terms and factors computed
           -h  description/help
madhava.c - estimates pi via the madhava series within an error of 10^-14.
bbp.c - estimates pi via the Bailey-Borwein-Plouffe Formula within an error of 10^-14.
newton.c - estimates square root within an error of 10^-14. Written by the CSE13S instructors. It was indicated by the TAs it was acceptable to use the provided code.
e.c - estimates e using a Taylor series within an error of 10^-14.
viete.c - estimates pi via Viete's Formula within an error of 10^-14
euler.c - estimates pi using Euler's solution up to 10000 iterations.
makefile - compiles mathlib-test.c with additional c files. Use via "make" command. Can also perform "make clean" which will remove any object files in the folder and "make format" which will format the .c files according to CSE13S programming spec.
Run code by entering directory and typing "make" command. This will compile mathlib-test which can be run with ./mathlib-test [options].
DESIGN.pdf - describes design process of program
WRITEUP.pdf - contains graphs, programming process, and resources used while creating this library of files.
