//Written by Isabella Phung for CSE13S
#include "io.h"
#include "code.h"
#include "trie.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "vi:o:"
//uint64_t total_syms = 0;
//uint64_t total_bits = 0;

//prints instructions for use
void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSYS\n"
        "   This encodes a file using Lempel-Ziv 78 Lossless compression.\n"
        "USAGE\n"
        "   %s [-vi:o:]\n"
        "\n"
        "OPTIONS\n"
        "   -v              Prints compression statistics to stderr\n"
        "   -i input file   Input file to compress. Default: stdin\n"
        "   -o outputfile   Output file of compressed input. Default: stdout\n"
        "   -h              description/help\n",
        exec);
}

int bitlength(size_t num) {
    uint64_t count = 0;
    while (num / 2 != 0) {
        num = num / 2;
        count++;
    }
    return count;
}

void printStatistics(void) {
    float spacePercent = 100 * (1 - (total_bits / total_syms));
    printf("Compressed file size: %" PRIu64 " bytes\n", total_bits / 8);
    printf("Uncompressed file size: %" PRIu64 " bytes\n", total_bits);
    printf("Space saving: %.2f\n", spacePercent);
    return;
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
    int inputFileNum = fileno(input);
    int outputFileNum = fileno(output);

    TrieNode *root = trie_create();
    TrieNode *curr_node = root;
    TrieNode *prev_node = NULL;
    TrieNode *next_node = NULL;
    uint8_t curr_sym = 0;
    uint8_t prev_sym = 0;
    uint16_t next_code = START_CODE;
    while (read_sym(inputFileNum, &curr_sym) == true) {
        next_node = trie_step(curr_node, curr_sym);
        if (next_node != NULL) {
            prev_node = curr_node;
            curr_node = next_node;
        } else {
            write_pair(outputFileNum, curr_node->code, curr_sym, bitlength(next_code));
            curr_node->children[curr_sym] = trie_node_create(next_code);
            curr_node = root;
            next_code += 1;
        }
        if (next_code == MAX_CODE) {
            trie_reset(root);
            curr_node = root;
            next_code = START_CODE;
        }
        prev_sym = curr_sym;
    }
    if (curr_node != root) {
        write_pair(outputFileNum, prev_node->code, prev_sym, bitlength(next_code));
        next_code = (next_code + 1) % MAX_CODE;
    }
    write_pair(outputFileNum, STOP_CODE, 0, bitlength(next_code));
    //flush_pairs(outputFileNum);

    if (statistics) {
        printStatistics();
    }
    return 0;
}
