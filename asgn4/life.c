#include <stdio.h>
#include <ncurses.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <unistd.h>
#include <inttypes.h>

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
    char filename[MAX_FILENAME_LENGTH]
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
            filename = [];
            scanf(%s, filename);
            input = fopen(filename, "r"); 
            break;
        case 'o': 
            filename = [];
            scanf(%s, filename);
            ouput = fopen(filename, "r"); 
            break;
        default: usage(argv[0]); return EXIT_FAILURE;
        }
    }
    
    scanf(input, "%" SCNd32, width); 
    scanf(input, "%" SCNd32, height);
    Universe *universe = uv_create(width, height, toroidal);
    uv_populate(universe, input);
    uint32_t liveCount = 0;
    for(uint32_t i = 0; i<generations; i++){
        for(uint32_t j = 0; j<width; j++){
            for(uint32_t k = 0; k<height; k++){
                liveCount = uv_census(universe, j, k);
                if(uv_get_cell(universe, j, k) && (liveCount == 2 || liveCount == 3)){
                    uv_live_cell(universe, j, k);                
                }else if(!uv_get_cell(universe, j, k && liveCount == 3)){
                    uv_live_cell(universe, j, k);
                }else{
                    uv_dead_cell(universe, j, k);
                }
            }
        }
    }
    uv_print(universe, output);
    uv_delete(universe);

    
    
