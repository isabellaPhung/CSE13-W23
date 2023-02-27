#include "numtheory.h"
#include "randstate.h"
gmp_randstate_t state;

//calculate gcd of a and b and stores the value
//in g. input: initialized gmp ints g, a, and b
void gcd(mpz_t g, const mpz_t a, const mpz_t b) {
    mpz_t tempa, tempb, temp;
    mpz_init_set(tempa, a);
    mpz_init_set(tempb, b);
    mpz_init_set(temp, b); //t = b
    //creating and setting values that I can modify
    //I don't want to modify the original values of a and b
    while (mpz_sgn(tempb) != 0) { // while b != 0
        mpz_set(temp, tempb); //t = b
        mpz_mod(tempb, tempa, tempb); //b = a mod b
        mpz_set(tempa, temp); //a = t
    }
    mpz_set(g, tempa);
    mpz_clears(tempa, tempb, temp, NULL); //clean up generated ints
    return;
}

// calculates the mod inverse of a and n and stores the value
//in o, if there doesn't exist a mod inverse, 0 will be stored
//in o.
//input: initialized gmp ints o, a, and n
void mod_inverse(mpz_t o, const mpz_t a, const mpz_t n) {
    mpz_t r, rprime, t, tprime, q, temp1, temp2;
    mpz_init_set(r, a); //r = value we're modding by
    mpz_init_set(rprime, n); // r' = value we're modding
    mpz_init(tprime); //t'/ = 0
    mpz_init_set_ui(t, 1); //t = 1
    mpz_inits(q, temp1, temp2, NULL);

    while (mpz_sgn(rprime) != 0) {
        mpz_fdiv_q(q, r, rprime); //q = floor(r/r')

        mpz_set(temp1, r); //(r,r') = (r', r-q*r')
        mpz_set(r, rprime);
        mpz_mul(temp2, q, rprime);
        mpz_sub(rprime, temp1, temp2);

        mpz_set(temp1, t); //(t,t') = (t', t-q*t')
        mpz_set(t, tprime);
        mpz_mul(temp2, q, tprime);
        mpz_sub(tprime, temp1, temp2);
    }
    if (mpz_cmp_ui(r, 1) > 0) { // if r> 1
        mpz_set_ui(o, 0); // return 0 aka no ivnerse
        return;
    }
    if (mpz_sgn(t) == -1) { // if t<0:
        mpz_add(t, t, n); // t = t+n
    }
    mpz_set(o, t); //return t
}

//calculates the power mod of a, d, and n and stores the value in o
//input: initialized gmp integers o, a, d, and n
void pow_mod(mpz_t o, const mpz_t a, const mpz_t d, const mpz_t n) {
    mpz_t v, p, tempd;
    mpz_init_set_ui(v, 1);
    mpz_init_set(p, a);
    mpz_init_set(tempd, d);
    while (mpz_sgn(tempd) == 1) { //while d>0
        if (mpz_odd_p(tempd) != 0) { // if d is odd
            mpz_mul(v, v, p); //v=(v*p)%n
            mpz_mod(v, v, n);
        }

        mpz_mul(p, p, p); //p = (p*p)%n
        mpz_mod(p, p, n);
        mpz_fdiv_q_ui(tempd, tempd, 2);
    }
    mpz_set(o, v);
}

//performs witness check for is_prime, where randval is a
//input: initialized gmp ints randval and n
//output: True if random value is euler's witness, false otherwise
bool witness(mpz_t randval, const mpz_t n) {
    //get d and r from randval and n
    mpz_t d, r;
    mpz_inits(d, r, NULL);
    mpz_sub_ui(d, n, 1); // d = n-1
    while (mpz_even_p(d) != 0) { // while d is even.
        mpz_fdiv_q_ui(d, d, 2); //d = floor(d/2);
        mpz_add_ui(r, r, 1); // r+=1;
    }
    //d and r values acquired, now to continue with witness

    mpz_t x, y, j, temp, tempn;
    mpz_inits(x, y, j, tempn, NULL);
    mpz_init_set_ui(temp, 2);
    mpz_sub_ui(tempn, n, 1);
    pow_mod(x, randval, d, n); // x = pow_mod(a, d, n)
    for (; mpz_cmp(j, r) < 0; mpz_add_ui(j, j, 1)) { //for(int j= 0; j<r; j++)
        pow_mod(y, x, temp, n); //y = powmod(x, 2, n)
        if (mpz_cmp_ui(y, 1) == 0 && mpz_cmp_ui(x, 1) != 0
            && mpz_cmp(x, tempn) != 0) { // if y==1 and x != 1 and x!= n-1
            return true;
        }
        mpz_set(x, y); //x = y
    }
    return mpz_cmp_ui(x, 1) != 0; // return x != 1
}

//checks if the given value is prime using the Miller-Rabin
//algorithm. More accurate w/ more iterations
//input: gmp int n, unsigned 64bit int iterations
//output: returns true if given value is prime
bool is_prime(const mpz_t n, uint64_t iters) {
    mpz_t tempvar, randomval;
    mpz_inits(tempvar, randomval, NULL);

    mpz_mod_ui(tempvar, n, 2); // temporary value stores n%2
    if (mpz_cmp_ui(n, 2) < 0
        || (mpz_cmp_ui(n, 2) != 0 && mpz_sgn(tempvar) == 0)) { //if n<2 or (n!=2 and n%2==0)
        return false;
    }
    if (mpz_cmp_ui(n, 2) == 0 || mpz_cmp_ui(n, 3) == 0) { //if n==2 or n ==3
        return true;
    }

    //urandomm generates random val from 0 to upper limit. in order to shift range up, upper limit has to be n-4 rather than n-2, then 2 will be added to the random number
    mpz_sub_ui(tempvar, n, 4); // temporary value set to n-4

    for (uint32_t i = 0; i < iters; i++) {
        mpz_urandomm(randomval, state, tempvar); // random val from [0,n-4]
        mpz_add_ui(randomval, randomval, 2); // add 2 to random val
        //witness check
        if (witness(randomval, n)) {
            return false;
        }
    }
    return true;
}

//produces a prime number with length of the given bits
//and stores it in p.
//input: initialized gmp int, unsigned ints bits and iters.
//more iterations increases likelihood that number is prime
void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {
    do {
        mpz_rrandomb(p, state, bits);
    } while (!is_prime(p, iters));
}
