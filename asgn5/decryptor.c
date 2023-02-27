//Written by Isabella Phung for CSE13S
#include "ss.h"
#include "numtheory.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "i:o:n:vh"

//prints instructions for use
void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSYS\n"
        "   Decrypts a file using the provided private key\n"
        "   using the Schmidt-Samoa algorithm.\n"
        "USAGE\n"
        "   %s [i:o:n:vh]\n"
        "\n"
        "OPTIONS\n"
        "   -i inputfile    Input file to decrypt. Default: stdin.\n"
        "   -o outputfile   Output file for decrypted text. Default: stdio.\n"
        "   -n publicKey    File containing private key. Defualt ss.priv.\n"
        "   -v              Displays verbose output.\n"
        "   -h              description/help\n",
        exec);
}

int main(int argc, char **argv) {
    //first runs through all arguments and
    //determines which ones have been called
    //before performing and outputing tests
    FILE *input = stdin;
    FILE *output = stdout;
    FILE *privkey;
    bool verbose = false;
    int opt = 0;
    int index = 0; //index used for keeping track of arguments
    char *inputfilename;
    char *keyfilename = "ss.priv";
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i':
            input = fopen(argv[index + 2], "r");
            inputfilename = argv[index + 2];
            index += 2;
            break; //input file
        case 'o':
            output = fopen(argv[index + 2], "w");
            index += 2;
            break; //output file
         case 'n':
            keyfilename = argv[index + 2];
            index += 2;
            break; //priv key file
        case 'v':
            verbose = true;
            index++;
            break; //verbose option
        
        default: usage(argv[0]); return EXIT_FAILURE;
        }
    }
    privkey = fopen(keyfilename, "r");// read priv key
    //if input file doesn't exist
    if (input == NULL) {
        printf("Error opening %s\n", inputfilename);
        return 0;
    }
    //if priv key file doesn't exist
    if (privkey == NULL) {
        printf("Error opening %s\n", keyfilename);
        return 0;
    }

    mpz_t pq, d;
    mpz_inits(pq, d, NULL);
    ss_read_priv(pq, d, privkey);// get priv key pq and d
    ss_decrypt_file(input, output, d, pq);
    if(verbose){
        printf("\n");
        gmp_printf("pq: %Zd\n", pq);
        gmp_printf("d: %Zd\n", d);
    }
    fclose(privkey);
    fclose(input);
    fclose(output);

    mpz_clears(pq, d, NULL);

    return 0;
}
