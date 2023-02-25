#include "ss.h"

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
void ss_make_pub(mpz_t p, mpz_t q, mpz_t n, uint64_t nbits, uint64_t iters){
    uint64_t pbits, qbits;
    uint64_t min, max;
    min = nbits/5;
    max = (2*nbits)/5;
    max = max-min;
    //random generates a number from 0 to the maximum random val
    //we'll start with generating a random num from 0 to (maximum-minimum)
    //then add munimum to that random number
    pbits = (uint64_t) random() % max;
    pbits = pbits + min;
    qbits = pbits * 2;
    
    //need to check that p is not a factor of q-1
    //and that q is not a factor of p-1
    make_prime(p, pbits, iters);
    do{
        make_prime(q, qbits, iters);
    }while(p == q || p%(q-1)==0 || q%(p-1)==0);

    mpz_mul(n, p, p);
    mpz_mul(n, n, q); // n = p*p*q

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
void ss_make_priv(mpz_t d, mpz_t pq, const mpz_t p, const mpz_t q){
//we need lcm(a, b) which is just (a*b)//gcd(a, b)
   mpz_t lambda, tempa, tempb;
   mpz_inits(lambda, tempa, tempb, 0);
   mpz_mul(pq, p, q); 
   mpz_sub(tempa, p, 1);
   mpz_sub(tempb, q, 1);
   lcm(lambda, tempa, tempb);
   mod_inverse(d, n, lambda);
}

//
// Export SS public key to output stream
//
// Requires:
//  n: public modulus/exponent
//  username: login name of keyholder ($USER)
//  pbfile: open and writable file stream
//
void ss_write_pub(const mpz_t n, const char username[], FILE *pbfile){
    mpz_out_str(pbfile, 16, n);
    fprintf(pbfile, "\n");
    fprintf(pbfile, username);
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
void ss_write_priv(const mpz_t pq, const mpz_t d, FILE *pvfile){
    mpz_out_str(pvfile, 16, pq);
    fprintf("\n");
    mpz_out_str(pvfile, 16, d);
    fprintf("\n");
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
void ss_read_pub(mpz_t n, char username[], FILE *pbfile){
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
void ss_read_priv(mpz_t pq, mpz_t d, FILE *pvfile){
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
void ss_encrypt(mpz_t c, const mpz_t m, const mpz_t n){
    pow_mod(c, m, n, n);
}

uint8_t* makeBlock(mpz_t blocksize){
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
void ss_encrypt_file(FILE *infile, FILE *outfile, const mpz_t n){
    mpz_t blocksize;
    mpz_init(blocksize, 0);
    mpz_sqrt(blocksize, n);
    mpz_sub_ui(blocksize, blocksize, 1);
    blocksize = mpz_sizeinbase(blocksize, 2);
    mpz_fdiv_ui_q(blocksize, blocksize, 8); //blocksize = floor(logbase2(sqrt(n)-1)/8)
    uint8_t *block = makeBlock(blocksize);
    uint8_t nextAddress = block + sizeof(char);
    mpz_t j, m, c;
    mpz_inits(j, m, c, 0);
    mpz_sub_ui(j, blocksize, 1);
    int argNum = 0;
    mpz_t x;
    mpz_init(x, 0);
    size_t bytes = 0;
    do{
        bytes = fread(nextAddress, sizeof(char), j, infile);//should start from block address +1
        mpz_import(m, bytes, 1, 1, 0, block);
        ss_encrypt(c, m, n);
        mpz_out_str(outfile, 16, c);
        fprintf(outfile, "\n");
    }while(bytes != 0);
    
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
void ss_decrypt(mpz_t m, const mpz_t c, const mpz_t d, const mpz_t pq){
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
void ss_decrypt_file(FILE *infile, FILE *outfile, const mpz_t d, const mpz_t pq){
    mpz_t blocksize;
    mpz_init(blocksize, 0);
    mpz_sqrt(blocksize, pq);
    mpz_sub_ui(blocksize, blocksize, 1);
    blocksize = mpz_sizeinbase(blocksize, 2);
    mpz_fdiv_ui_q(blocksize, blocksize, 8); //blocksize = floor(logbase2(sqrt(n)-1)/8)
    uint8_t *block = makeBlock(blocksize);
    uint8_t nextAddress = block + sizeof(char);
    mpz_t j, m, c;
    mpz_inits(j, m, c, 0);
    mpz_sub_ui(j, blocksize, 1);
    int argNum = 0;
    mpz_t x;
    mpz_init(x, 0);
    size_t bytes = 0;
    do{
        bytes = mpz_input_str(infile, 16, c); //scans hex string into c
        ss_decrypt(m, c, d, pq); 
        mpz_export(nextAddress, j, 1, 1, 0, m);//reads numbers from m into block starting from nextAddress.
        fprintf(outfile, "%s", block); 
        fprintf(outfile, "\n");
    }while(bytes != 0);
    

}
