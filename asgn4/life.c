//Written by Isabella Phung for CSE13S
#include "universe.h"

#include <inttypes.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "tsn:i:o:h"

uint32_t MAX_FILENAME_LENGTH = 255;
uint32_t DELAY = 50000;

//prints instructions for use
void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSYS\n"
        "   Recreates Conway's game of life. Can accept file\n"
        "   input or via console. Creates text interface to display states.\n"
        "USAGE\n"
        "   %s [-tsn:i:o:]\n"
        "\n"
        "OPTIONS\n"
        "   -t              Indicates toroidal/continuous world.\n"
        "   -s              Disables text interface.\n"
        "   -n generations  Number of generations to perform. Defualt 100.\n"
        "   -i inputfile    Input file for universe creation.\n"
        "   -o outputfile   Output file for final universe state.\n"
        "   -h              description/help\n",
        exec);
}

//accepts a universe and prints to existing ncurses page
void ncursorPrint(Universe *u) {
    erase();

    uint32_t width = uv_cols(u);
    uint32_t height = uv_rows(u);
    for (uint32_t row = 0; row < height; row++) {
        for (uint32_t col = 0; col < width; col++) {
            if (uv_get_cell(u, row, col)) {
                mvprintw(row, col, "o");
            }
        }
    }
    refresh();
    usleep(DELAY);
}

int main(int argc, char **argv) {
    //first runs through all arguments and
    //determines which ones have been called
    //before performing and outputing tests
    bool toroidal = false;
    bool ncursor = true;
    uint32_t generations = 100;
    uint32_t width = 0;
    uint32_t height = 0;
    FILE *input = stdin;
    FILE *output = stdout;
    int opt = 0;
    int index = 0; //index used for keeping track of arguments
    char *filename;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 't': toroidal = true; index++; break; //toroidal universe option
        case 's': ncursor = false; index++; break; //disable ncurspr
        case 'n': generations = (uint32_t) strtoul(optarg, NULL, 10); index+=2; break; //generation number option
        case 'i': input = fopen(argv[index+2], "r"); filename = argv[index+2]; index+=2; break; //input file
        case 'o': output = fopen(argv[index+2], "w"); index+=2; break; //output file
        default: usage(argv[0]); return EXIT_FAILURE;
        }
    }
    
    //if input file doesn't exist
    if(input == NULL){
        printf("Error opening %s\n", filename);
        return 0;
    }
    fscanf(input, "%" SCNd32, &width);
    fscanf(input, "%" SCNd32, &height);
    Universe *universeA = uv_create(width, height, toroidal);
    bool isPopulated = false;
    isPopulated = uv_populate(universeA, input);
    if (!isPopulated) { //prints Malformed input if recieves negative, non ints,
    // or more live cells than the universe can fit.
        printf("Malformed input.\n");
        return 0;
    }
    fclose(input);
    //uses two universes since state of new universe relient on previous generation
    //need to save state of previous generation while building new universe
    Universe *universeB = uv_create(width, height, toroidal);
    if (ncursor) { // sets ncursor screen and shows initial state of universe
        initscr();
        curs_set(FALSE);
        ncursorPrint(universeA);
    }

    uint32_t liveCount = 0;
    for (uint32_t i = 0; i < generations; i++) {
        for (uint32_t j = 0; j < width; j++) {
            for (uint32_t k = 0; k < height; k++) {
                liveCount = uv_census(universeA, j, k); //performs count
                //checks logic rules of Game of Life according to number of live neighboring cells.
                if (uv_get_cell(universeA, j, k) && (liveCount == 2 || liveCount == 3)) {
                    uv_live_cell(universeB, j, k);
                } else if (!uv_get_cell(universeA, j, k) && liveCount == 3) {
                    uv_live_cell(universeB, j, k);
                } else {
                    uv_dead_cell(universeB, j, k);
                }
            }
        }
        //swaps universes, so new one is displayed.
        Universe *t = universeA;
        universeA = universeB;
        universeB = t;
        if (ncursor) { //display new universe on ncursor screen.
            ncursorPrint(universeA);
        }
    }
    if (ncursor) {
        endwin();
    }
    uv_print(universeA, output);
    uv_delete(universeA); //clean up any allocated memory.
    uv_delete(universeB);

    return 0;
}
