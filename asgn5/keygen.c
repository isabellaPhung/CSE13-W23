//Written by Isabella Phung for CSE13S
#include "ss.h"
#include "numtheory.h"
#include "randstate.h" 

#include <inttypes.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define OPTIONS "b:i:n:d:s:vh"
//gmp_randstate_t state;

//prints instructions for use
void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSYS\n"
        "   Generates public and private keys for the user\n"
        "   using the Schmidt-Samoa algorithm.\n"
        "USAGE\n"
        "   %s [b:i:n:d:s:vh]\n"
        "\n"
        "OPTIONS\n"
        "   -b bits        Minimum bits for public key n.\n"
        "   -i iterations  Iterations for Miller-Rabin Primaility testing.\n" 
                            "Greater the number, higher likelihood the value will be prime. Default: 50.\n"
        "   -n publicKey   File name for public key. Default: ss.pub.\n"
        "   -d privateKey  File name for private key. Defualt ss.priv.\n"
        "   -s seed        Seed for random number generator. Default: seconds." 
        "   -v             Displays verbose output.\n"
        "   -h             description/help\n",
        exec);
}

int main(int argc, char **argv) {
    //first runs through all arguments and
    //determines which ones have been called
    //before performing and outputing tests
    FILE *pubkey;
    FILE *privkey;
    bool verbose = false;
    int opt = 0;
    uint64_t bits = 0;
    uint64_t iterations = 0;
    uint64_t seed = time();
    int index = 0; //index used for keeping track of arguments
    char *pubkeyfilename = "ss.pub";
    char *privkeyfilename = "ss.priv"
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'b':
            bits = (uint64_t) strtoul(optarg, NULL, 10);
            index += 2;
            break;
        case 'i':
            iterations = (uint64_t) strtoul(optarg, NULL, 10);
            index += 2;
            break;
        case 'n':
            pubkeyfilename = argv[index + 2];
            index += 2;
            break; //public key file
        case 'o':
            privkeyfilename = argv[index + 2];
            index += 2;
            break; //private key file
        case 's':
            seed = (uint64_t) strtoul(oparg, NULL, 10);
            index++;
            break; //seed

        case 'v':
            verbose = true;
            index++;
            break; //verbose option
        
        default: usage(argv[0]); return EXIT_FAILURE;
        }
    }
    pubkey = fopen(pubkeyfilename, "r");// read public key
    //if pub key file doesn't exist
    if (pubkey == NULL) {
        printf("Error opening %s\n", pubkeyfilename);
        return 0;
    }
    
    privkey = fopen(privkeyfilename, "r");// read priv key
    //if priv key file doesn't exist
    if (privkey == NULL) {
        printf("Error opening %s\n", privkeyfilename);
        return 0;
    }

    fchmod(privkey, 0600);

    randstate_init(seed);

    mpz_t p, q, n;
    mpz_inits(p, q, n, NULL);
    ss_make_pub(p, q, n, bits, iterations);
    mpz_t d, pq;
    mpz_inits(d, pq, NULL);
    ss_make_priv(d, pq, p, q);
    
    char user[] = getenv("USER");
    ss_write_pub(n, user, pubkey);
    ss_write_priv(pq, d, privkey);
    if(verbose){
        printf("user = %s", user);
        gmp_printf("p  (%Zd) = %Zd\n", gmp_sizeinbase(p, 2), p);
        gmp_printf("q  (%Zd) = %Zd\n", gmp_sizeinbase(q, 2), q);
        gmp_printf("n  (%Zd) = %Zd\n", gmp_sizeinbase(n, 2), n);
        gmp_printf("pq (%Zd) = %Zd\n", gmp_sizeinbase(pq, 2), pq);
        gmp_printf("d  (%Zd) = %Zd\n", gmp_sizeinbase(d, 2), d);
    }

    pubkey.close();
    privkey.close();
    randstate_clear();
    mpz_clears(p, q, n, d, pq);
    //TODO get rid of mpz integers

    return 0;
}
