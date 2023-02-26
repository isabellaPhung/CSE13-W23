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
        "   Encrypts a file using the provided public key\n"
        "   using the Schmidt-Samoa algorithm.\n"
        "USAGE\n"
        "   %s [i:o:n:vh]\n"
        "\n"
        "OPTIONS\n"
        "   -i inputfile    Input file to encrypt. Default: stdin.\n"
        "   -o outputfile   Output file for encrypted text. Default: stdio.\n"
        "   -n publicKey    File containing public key. Defualt ss.pub.\n"
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
    FILE *pubkey;
    bool verbose = false;
    int opt = 0;
    int index = 0; //index used for keeping track of arguments
    char *inputfilename;
    char *keyfilename = "ss.pub";
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
            break; //pub key file
        case 'v':
            verbose = true;
            index++;
            break; //verbose option
        
        default: usage(argv[0]); return EXIT_FAILURE;
        }
    }
    pubkey = fopen(keyfilename, "r");// read public key
    //if input file doesn't exist
    if (input == NULL) {
        printf("Error opening %s\n", inputfilename);
        return 0;
    }
    //if pub key file doesn't exist
    if (pubkey == NULL) {
        printf("Error opening %s\n", keyfilename);
        return 0;
    }

    mpz_t n;
    char username[LOGIN_NAME_MAX];
    mpz_init(n);
    ss_read_pub(n, char username[], pubkey);// get pub key n
    //maybe check that n has a value
    ss_encrypt_file(input, output, n);
    fclose(pubkey, input, output);
    if(verbose){
        printf("user: %s\n", username);
        gmp_printf("n: %Zd\n", n); 
    }
    mpz_clear(n);
    //TODO get rid of mpz integers

    return 0;
}
