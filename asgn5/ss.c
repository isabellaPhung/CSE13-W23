//written by Isabella Phung for CSE 13s with comments provided
//by CSE13 instructors.
//Much of the code based off of python pseudocode
//written by CSE 13S instructors.
#include "ss.h"
#include "numtheory.h"
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>

//
// Generates the components for a new SS key.
//
// Provides:
//  p:  first prime
//  q: second prime
//  n: public modulus/exponent
//
// Requires:
//  nbits: minimum # of bits in n
//  iters: iterations of Miller-Rabin to use for primality check
//  all mpz_t arguments to be initialized
//
void ss_make_pub(mpz_t p, mpz_t q, mpz_t n, uint64_t nbits, uint64_t iters) {
    uint64_t pbits, qbits;
    uint64_t min, max;
    uint64_t seed = (uint64_t) time(NULL);
    srandom(seed);
    min = nbits
          / 5; // minimum and maximum bits as mentioned in the spec to create p and q with varying bits
    max = (2 * nbits) / 5;
    max = max - min;
    //random generates a number from 0 to the maximum random val
    //we'll start with generating a random num from 0 to (maximum-minimum)
    //then add munimum to that random number
    pbits = (uint64_t) random() % max;
    pbits = pbits + min;
    qbits = nbits - (pbits * 2);

    //need to check that p is not a factor of q-1
    //and that q is not a factor of p-1
    mpz_t temp1, temp2, temp3, temp4;
    mpz_inits(temp1, temp2, temp3, temp4, NULL);
    do { // constantly generate new primes until we get values that fit our criteria
        make_prime(p, pbits, iters);
        make_prime(q, qbits, iters);
        mpz_sub_ui(temp1, q, 1);
        mpz_sub_ui(temp2, p, 1);
        mpz_mod(temp3, temp1, p);
        mpz_mod(temp4, temp2, q);

    } while (mpz_cmp(p, q) == 0 || mpz_sgn(temp3) == 0 || mpz_sgn(temp4) == 0);

    mpz_mul(n, p, p);
    mpz_mul(n, n, q); // n = p*p*q
    mpz_clears(temp1, temp2, temp3, temp4, NULL);
}

//finds the lcm of two GMP integers, a and b
//and stores the value in l. Does not return a val.
//input: initilized gmp ints, l, a, and b
void lcm(mpz_t l, mpz_t a, mpz_t b) {
    //uses gcd to calculate (a*b)//gcd(a, b)
    mpz_t multiple, denominator;
    mpz_inits(multiple, denominator, NULL);
    mpz_mul(multiple, a, b);
    gcd(denominator, a, b);
    mpz_fdiv_q(l, multiple, denominator);
    mpz_clears(multiple, denominator, NULL);
}

//
// Generates components for a new SS private key.
//
// Provides:
//  d:  private exponent
//  pq: private modulus
//
// Requires:
//  p:  first prime number
//  q: second prime number
//  all mpz_t arguments to be initialized
//
void ss_make_priv(mpz_t d, mpz_t pq, const mpz_t p, const mpz_t q) {
    mpz_t lambda, tempa, tempb, n;
    mpz_inits(lambda, tempa, tempb, n, NULL);
    mpz_mul(pq, p, q); //pq = p*q
    mpz_sub_ui(tempa, p, 1);
    mpz_sub_ui(tempb, q, 1);
    lcm(lambda, tempa, tempb); //need lcm(p-1, q-1) = lambda
    mpz_mul(n, p, p);
    mpz_mul(n, n, q); // n = p*p*q
    mod_inverse(d, n, lambda); //d = modinverse(n, lambda)
    mpz_clears(lambda, tempa, tempb, n, NULL);
}

//
// Export SS public key to output stream
//
// Requires:
//  n: public modulus/exponent
//  username: login name of keyholder ($USER)
//  pbfile: open and writable file stream
//
void ss_write_pub(const mpz_t n, const char username[], FILE *pbfile) {
    mpz_out_str(pbfile, 16, n);
    fprintf(pbfile, "\n");
    fprintf(pbfile, "%s", username);
    fprintf(pbfile, "\n");
}

//
// Export SS private key to output stream
//
// Requires:
//  pq: private modulus
//  d:  private exponent
//  pvfile: open and writable file stream
//
void ss_write_priv(const mpz_t pq, const mpz_t d, FILE *pvfile) {
    mpz_out_str(pvfile, 16, pq);
    fprintf(pvfile, "\n");
    mpz_out_str(pvfile, 16, d);
    fprintf(pvfile, "\n");
}

//
// Import SS public key from input stream
//
// Provides:
//  n: public modulus
//  username: $USER of the pubkey creator
//
// Requires:
//  pbfile: open and readable file stream
//  username: requires sufficient space
//  all mpz_t arguments to be initialized
//
void ss_read_pub(mpz_t n, char username[], FILE *pbfile) {
    gmp_fscanf(pbfile, "%Zx", n);
    fscanf(pbfile, "%s", username);
}

//
// Import SS private key from input stream
//
// Provides:
//  pq: private modulus
//  d:  private exponent
//
// Requires:
//  pvfile: open and readable file stream
//  all mpz_t arguments to be initialized
//
void ss_read_priv(mpz_t pq, mpz_t d, FILE *pvfile) {
    gmp_fscanf(pvfile, "%Zx", pq);
    gmp_fscanf(pvfile, "%Zx", d);
}

//
// Encrypt number m into number c
//
// Provides:
//  c: encrypted integer
//
// Requires:
//  m: original integer
//  n: public exponent/modulus
//  all mpz_t arguments to be initialized
//
void ss_encrypt(mpz_t c, const mpz_t m, const mpz_t n) {
    pow_mod(c, m, n, n);
}

//allocates memory for block of given size
//input: usigned 64 bit int size of block
//output: pointer for block
uint8_t *makeBlock(uint64_t blocksize) {
    uint8_t *block = (uint8_t *) calloc(blocksize, sizeof(char));
    return block;
}

//
// Encrypt an arbitrary file
//
// Provides:
//  fills outfile with the encrypted contents of infile
//
// Requires:
//  infile: open and readable file stream
//  outfile: open and writable file stream
//  n: public exponent and modulus
//
void ss_encrypt_file(FILE *infile, FILE *outfile, const mpz_t n) {
    mpz_t blocksize;
    mpz_init(blocksize);
    mpz_sqrt(blocksize, n);
    mpz_sub_ui(blocksize, blocksize, 1);
    uint64_t intBlockSize = mpz_sizeinbase(blocksize, 2);
    intBlockSize /= 8; //blocksize = floor(logbase2(sqrt(n)-1)/8)

    uint8_t *block = makeBlock(intBlockSize);
    uint8_t *nextAddress = block + sizeof(char);
    mpz_t m, c; // initiallizes vars for plaintext and ciphertext
    mpz_inits(m, c, NULL);
    size_t bytes = 0;
    bytes = fread(nextAddress, sizeof(char), intBlockSize, infile); //starts from block address + 1

    while (bytes != 0) {
        block[0] = 0xff; //inserts a 0 at start of block
        mpz_import(m, bytes + 1, 1, sizeof(char), 0, 0, block);
        ss_encrypt(c, m, n);
        mpz_out_str(outfile, 16, c);
        fprintf(outfile, "\n");
        bytes = fread(
            nextAddress, sizeof(char), intBlockSize, infile); //should start from block address +1
    }
    free(block);
    block = NULL;
    mpz_clears(blocksize, m, c, NULL);
}

//
// Decrypt number c into number m
//
// Provides:
//  m: decrypted/original integer
//
// Requires:
//  c: encrypted integer
//  d: private exponent
//  pq: private modulus
//  all mpz_t arguments to be initialized
//
void ss_decrypt(mpz_t m, const mpz_t c, const mpz_t d, const mpz_t pq) {
    pow_mod(m, c, d, pq);
}

//
// Decrypt a file back into its original form.
//
// Provides:
//  fills outfile with the unencrypted data from infile
//
// Requires:
//  infile: open and readable file stream to encrypted data
//  outfile: open and writable file stream
//  d: private exponent
//  pq: private modulus
//
void ss_decrypt_file(FILE *infile, FILE *outfile, const mpz_t d, const mpz_t pq) {
    mpz_t blocksize;
    mpz_init(blocksize);
    mpz_sqrt(blocksize, pq);
    mpz_sub_ui(blocksize, blocksize, 1);
    uint64_t intBlockSize = mpz_sizeinbase(blocksize, 2);
    intBlockSize /= 8; //blocksize = floor(logbase2(sqrt(n)-1)/8)

    uint8_t *block = makeBlock(intBlockSize);
    uint8_t *nextAddress = block + sizeof(char);
    mpz_t m, c;
    mpz_inits(m, c, NULL); //initializes vars for cipher and plaintext
    size_t bytes = 0;
    bytes = mpz_inp_str(c, infile, 16); //scans hex string into c
    while (bytes != 0) {
        block[0] = 0xff; //places 0 at start of block
        ss_decrypt(m, c, d, pq);
        int test
            = mpz_sizeinbase(m, 2)
              / 8; //if the final line is shorter than the previous line, fprintf prints extra characters, this forces fprintf to only print the exact number of characters
        mpz_export(nextAddress, NULL, 1, sizeof(char), 1, 0,
            m); //reads numbers from m into block starting from nextAddress.
        fprintf(outfile, "%.*s", test - 1, nextAddress + sizeof(char));

        bytes = mpz_inp_str(c, infile, 16); //scans hex string into c
    }
    fprintf(outfile, "\n");
    free(block);
    block = NULL;
    mpz_clears(blocksize, m, c, NULL);
}
