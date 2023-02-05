#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "shell.h"
#include "batcher.h"
#include "quick.h"
#include "heap.h"
#include "stats.h"

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

void printArray(uint32_t *arr, int printNum){
    for(int i = 0; i < printNum; i++){
        printf("%" PRIu32", ", arr[i]);  
    }
    printf("\n");
}


int main(int argc, char **argv) {
    uint32_t *array = calloc(10, sizeof(int));
    uint32_t val;

    uint32_t seed = time(0); /* Default (no options) is random based on time. */
    seed = 1; //predetermined seed for testing
    srandom(seed);
    for(int i = 0; i < 10; i++){
        val = (uint32_t)random() / 10000000;//values aren't larger than 10000
        array[i] = val; 
    }
    printf("initial array: ");
    printArray(array, 10);
    Stats stats;
    //shell_sort(&stats, array, 10);
    //heap_sort(&stats, array, 10);
    //quick_sort(&stats, array, 10);
    batcher_sort(&stats, array, 10); //segmentation
    printf("post sort: ");
    printArray(array, 10);
    free(array);

    int opt = 0;  
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
