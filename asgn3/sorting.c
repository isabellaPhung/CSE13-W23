#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "ahbsqr:n:p:H"

//prints instructions for use
void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSYS\n"
        "   Tests shell, heap, quick, and batcher sort\n"
        "   on a randomly generated integer array.\n"
        "USAGE\n"
        "   %s [-ahbsqr:n:p:H]\n"
        "\n"
        "OPTIONS\n"
        "   -a          Enables all sorting algorithms\n"
        "   -h          Enables Heap sorting\n"
        "   -b          Enables Batcher sorting\n"
        "   -s          Enables Shell sorting\n"
        "   -q          Enables Quick sorting\n"
        "   -r seed     Sets randomized seed to given int. Default 13371453\n"
        "   -n size     Sets array to specified size. Default 100\n"
        "   -p elements Prints out number of elements from the array\n"
        "   -H          description/help\n",
        exec);
}

int main(int argc, char **argv) {
    
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a': break;
        case 'h': break;
        case 'b': break;
        case 's': break;
        case 'q': break;
        case 'r': break;
        case 'n': break;
        case 'p': break;
        default: usage(argv[0]); return EXIT_FAILURE;
        }
    }
}


