#include "batcher.h"
#include "heap.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

void printArray(uint32_t *arr, uint32_t arraySize, uint32_t printNum) {
    uint32_t printVal = printNum;
    if (printNum > arraySize) {
        printVal = arraySize;
    }
    for (uint32_t i = 0; i < printVal; i++) {
        printf("%13" PRIu32, arr[i]);
        if ((i + 1) % 5 == 0 && i != 0) {
            printf("\n");
        }
    }
    printf("\n");
}

int main(int argc, char **argv) {
    uint32_t seed = 13371453; //predetermined seed for testing
    srandom(seed);

    int opt = 0;
    Set options = 0;
    uint32_t arraySize = 100;
    uint32_t printElements = 100;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            for (int i = 2; i <= 5; i++) {
                options = set_insert(options, i);
            }
            break;
        case 's': options = set_insert(options, 5); break;
        case 'b': options = set_insert(options, 4); break;
        case 'h': options = set_insert(options, 3); break;
        case 'q': options = set_insert(options, 2); break;
        case 'r':
            seed = (uint32_t) strtoul(optarg, NULL, 10); /* Deterministic seed */
            srandom(seed);
            break;
        case 'n': arraySize = (uint32_t) strtoul(optarg, NULL, 10); break;
        case 'p': printElements = (uint32_t) strtoul(optarg, NULL, 10); break;
        case 'H': set_insert(options, 1);
        default: usage(argv[0]); return EXIT_FAILURE;
        }
    }

    uint32_t *initialArray = calloc(arraySize, sizeof(int));
    uint32_t val;

    for (uint32_t i = 0; i < arraySize; i++) {
        val = (uint32_t) random();
        initialArray[i] = val;
    }
    //printf("initial array: ");
    //printArray(initialArray, arraySize, printElements);

    Stats stats;

    if (options == 0) {
        options = set_insert(options, 1);
        printf("Select at least one sort to perform.\n");
    }
    if (set_member(options, 1)) {
        usage(argv[0]);
    } else {
        if (set_member(options, 5)) { // shell sort
            uint32_t *arrayCopy = calloc(arraySize, sizeof(int));
            for (uint32_t i = 0; i < arraySize; i++) {
                arrayCopy[i] = initialArray[i];
            }
            shell_sort(&stats, arrayCopy, arraySize);
            printf("Shell Sort, %" PRIu32 " elements, %" PRIu64 " moves, %" PRIu64 " compares\n",
                arraySize, stats.moves, stats.compares);
            printArray(arrayCopy, arraySize, printElements);
            free(arrayCopy);
        }
        if (set_member(options, 4)) { // batcher sort
            uint32_t *arrayCopy = calloc(arraySize, sizeof(int));
            for (uint32_t i = 0; i < arraySize; i++) {
                arrayCopy[i] = initialArray[i];
            }
            batcher_sort(&stats, arrayCopy, arraySize);
            printf("Batcher Sort, %" PRIu32 " elements, %" PRIu64 " moves, %" PRIu64 " compares\n",
                arraySize, stats.moves, stats.compares);
            printArray(arrayCopy, arraySize, printElements);
            free(arrayCopy);
        }
        if (set_member(options, 3)) { // heap sort
            uint32_t *arrayCopy = calloc(arraySize, sizeof(int));
            for (uint32_t i = 0; i < arraySize; i++) {
                arrayCopy[i] = initialArray[i];
            }
            heap_sort(&stats, arrayCopy, arraySize);
            printf("Heap Sort, %" PRIu32 " elements, %" PRIu64 " moves, %" PRIu64 " compares\n",
                arraySize, stats.moves, stats.compares);
            printArray(arrayCopy, arraySize, printElements);
            free(arrayCopy);
        }
        if (set_member(options, 2)) { // quick sort
            uint32_t *arrayCopy = calloc(arraySize, sizeof(int));
            for (uint32_t i = 0; i < arraySize; i++) {
                arrayCopy[i] = initialArray[i];
            }
            quick_sort(&stats, arrayCopy, arraySize);
            printf("Quick Sort, %" PRIu32 " elements, %" PRIu64 " moves, %" PRIu64 " compares\n",
                arraySize, stats.moves, stats.compares);
            printArray(arrayCopy, arraySize, printElements);
            free(arrayCopy);
        }
    }
    //shell_sort(&stats, arrayCop, arraySize);
    //heap_sort(&stats, arrayCopy, arraySize);
    //quick_sort(&stats, arrayCopy, arraySize);
    //batcher_sort(&stats, arrayCopy, arraySize); //segmentation
    //printf("post sort: ");
    //printArray(array, arraySize, printElements);
    free(initialArray);
}
