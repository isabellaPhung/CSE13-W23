//Written by Isabella Phung for CSE13S
#include "io.h"
#include "code.h"
#include "word.h"

#include <stdio.h>
#include <unistd.h>

#define OPTIONS "vi:o:"

//prints instructions for use
void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSYS\n"
        "   This decodes a file that was compressed using Lempel-Ziv 78 Lossless compression.\n"
        "USAGE\n"
        "   %s [-vi:o:]\n"
        "\n"
        "OPTIONS\n"
        "   -v              Prints compression statistics to stderr\n"
        "   -i input file   Input file to decompress. Default: stdin\n"
        "   -o outputfile   Output file of decompressed input. Default: stdout\n"
        "   -h              description/help\n",
        exec);
}

int bitlength(size_t num){
    uint64_t count = 0;  
    while(num/2 != 0){
        num = num/2;
        count++;
    }
    return count;
}

int main(int argc, char **argv) {
    //first runs through all arguments and
    //determines which ones have been called
    //before performing and outputing tests
    bool statistics = false;
    FILE *input = stdin;
    FILE *output = stdout;
    int opt = 0;
    int index = 0; //index used for keeping track of arguments
    char *filename;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'v':
            statistics = true;
            index++;
            break; //compression statistics option
        case 'i':
            input = fopen(argv[index + 2], "r");
            filename = argv[index + 2];
            index += 2;
            break; //input file
        case 'o':
            output = fopen(argv[index + 2], "w");
            index += 2;
            break; //output file
        default: usage(argv[0]); return EXIT_FAILURE;
        }
    }

    //if input file doesn't exist
    if (input == NULL) {
        printf("Error opening %s\n", filename);
        return 0;
    }

    WordTable table = wt_create();
    uint8_t curr_sym = 0;
    uint16_t curr_code = 0;
    uint16_t next_code = START_CODE;
    while read_pair(input, &curr_code, &curr_sym, bit-length(next_code) == true){
        write_word(output, table[next_code]);
        next_code += 1;
        if(next_code == MAX_CODE){
            wt_reset(table);
            next_code = start_code;
        }
    }
    flush_words(output);
    return 0;
}
