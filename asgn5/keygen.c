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
#include <sys/stat.h>

#define OPTIONS "b:i:n:d:s:vh"

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
        "   -b bits        Minimum bits for public key n. Default: 256\n"
        "   -i iterations  Iterations for Miller-Rabin Primaility testing.\n" 
        "                  Greater the number, higher likelihood the value will be prime. Default: 50.\n"
        "   -n publicKey   File name for public key. Default: ss.pub.\n"
        "   -d privateKey  File name for private key. Defualt ss.priv.\n"
        "   -s seed        Seed for random number generator. Default: seconds.\n" 
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
    uint64_t bits = 256;
    uint64_t iterations = 50;
    uint64_t seed = (uint64_t)time(NULL);
    int index = 0; //index used for keeping track of arguments
    char *pubkeyfilename = "ss.pub";
    char *privkeyfilename = "ss.priv";
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'b':
            bits = (uint64_t) strtoul(optarg, NULL, 10);
            if(bits<10){
                printf("Inputed bit number is too small to generate primes.\n");
                return 0;
            }
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
        case 'd':
            privkeyfilename = argv[index + 2];
            index += 2;
            break; //private key file
        case 's':
            seed = (uint64_t) strtoul(optarg, NULL, 10);
            index++;
            break; //seed
        case 'v':
            verbose = true;
            index++;
            break; //verbose option
        default: usage(argv[0]); return EXIT_FAILURE;
        }
    }
    pubkey = fopen(pubkeyfilename, "w");// write public key
    //if pub key file doesn't exist
    if (pubkey == NULL) {
        printf("Error opening %s\n", pubkeyfilename);
        return 0;
    }
    
    privkey = fopen(privkeyfilename, "w");// write priv key
    //if priv key file doesn't exist
    if (privkey == NULL) {
        printf("Error opening %s\n", privkeyfilename);
        return 0;
    }
    chmod(privkeyfilename, strtol("0600", 0, 8)); //make priv key only user accessible

    randstate_init(seed);

    mpz_t p, q, n;
    mpz_inits(p, q, n, NULL);
    ss_make_pub(p, q, n, bits, iterations); //makes p, q and n
    mpz_t d, pq;
    mpz_inits(d, pq, NULL);
    ss_make_priv(d, pq, p, q); //makes d and pq
    
    char *user = getenv("USER");
    ss_write_pub(n, user, pubkey); //writes n to file
    ss_write_priv(pq, d, privkey); // writes pq and d to file
    
    if(verbose){
        printf("user = %s\n", user);
        gmp_printf("p  (%d) = %Zd\n", mpz_sizeinbase(p, 2), p);
        gmp_printf("q  (%d) = %Zd\n", mpz_sizeinbase(q, 2), q);
        gmp_printf("n  (%d) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_printf("pq (%d) = %Zd\n", mpz_sizeinbase(pq, 2), pq);
        gmp_printf("d  (%d) = %Zd\n", mpz_sizeinbase(d, 2), d);
    }

    fclose(pubkey);
    fclose(privkey);
    randstate_clear();
    mpz_clears(p, q, n, d, pq, NULL);

    return 0;
}
