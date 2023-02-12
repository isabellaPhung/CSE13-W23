#include <stdio.h>
#include <ncurses.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdlib.h>
#include "universe.h"
#include <unistd.h>

#define OPTIONS "tsn:i:o:h"

uint32_t MAX_FILENAME_LENGTH = 255;

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

void ncursorPrint(Universe *u){
    erase(); 
    
    uint32_t width = uv_cols(u);
    uint32_t height = uv_rows(u);
    for(uint32_t row = 0; row < height; row ++){
        for(uint32_t col = 0; col < width; col++){
            if(uv_get_cell(u, row, col)){
                mvprintw(row, col, "o");
            }
        }
    }
    refresh();
    usleep(50000);
}

int main(int argc, char **argv) {
    //first runs through all arguments first and
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
    int index = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 't':
            toroidal = true;
            break;
        case 's':
            ncursor = false;
            break;
        case 'n':
            generations = (uint32_t) strtoul(optarg, NULL, 10);
            break;
        case 'i':
            input = fopen(argv[index*2+2], "r"); 
            break;
        case 'o': 
            output = fopen(argv[index*2+2], "w"); 
            break;
        default: usage(argv[0]); return EXIT_FAILURE;
        }
        index++;
    }
    fscanf(input, "%" SCNd32, &width); 
    fscanf(input, "%" SCNd32, &height);
    Universe *universeA = uv_create(width, height, toroidal);
    bool isPopulated = false;
    isPopulated = uv_populate(universeA, input);
    if(!isPopulated){
        printf("Malformed input.\n");
        return 0;
    }
    fclose(input);
    Universe *universeB = uv_create(width, height, toroidal); 
    if(ncursor){
        initscr();
        curs_set(FALSE);
    }
        
    uint32_t liveCount = 0;
    for(uint32_t i = 0; i<generations; i++){
        for(uint32_t j = 0; j<width; j++){
            for(uint32_t k = 0; k<height; k++){
                liveCount = uv_census(universeA, j, k);
                if(uv_get_cell(universeA, j, k) && (liveCount == 2 || liveCount == 3)){
                    uv_live_cell(universeB, j, k); 
                }else if(!uv_get_cell(universeA, j, k) && liveCount == 3){
                    uv_live_cell(universeB, j, k);
                }else{
                    uv_dead_cell(universeB, j, k);
                }
            }
        }
        Universe *t = universeA;
        universeA = universeB;
        universeB = t;
        if(ncursor){
            ncursorPrint(universeA); 
        }
        
    }
    if(ncursor){
        endwin();
    }
    uv_print(universeA, output);
    uv_delete(universeA);
    uv_delete(universeB);

    return 0;
} 
