#include "numtheory.h"
#include "randstate.h"

void gcd(mpz_t g, mpz_t a, mpz_t b){
    mpz_t tempa, tempb, temp;
    mpz_init(temp, tempa, tempb, NULL);
    mpz_init_set(tempa, a);
    mpz_init_set(tempb, b);
    mpz_init_set(temp, b);//t = b
    //creating and setting values that I can modify
    //I don't want to modify the original values of a and b
    while(mpz_sgn(tempb) != 0){// while b != 0
        mpz_set(temp, tempb);//t = b
        mpz_set(tempb, mpz_mod(tempa, tempb));//b = a mod b
        mpz_set(tempa, temp) //a = t
    }
    mpz_set(g, tempa);
    mpz_clears(tempa, tempb, temp);//clean up generated ints
    return;
}

void mod_inverse(mpz_t o, mpz_t a, mpz_t n){
    mpz_t r, rprime, t, tprime, q, temp1, temp2;
    mpz_init_set(r, n);
    mpz_init_set(rprime, a);
    mpz_init_set(t, 0);
    mpz_init_set(tprime, 1);
    mpz_inits(q, temp1, temp2 NULL);

    while(mpz_sign(rprime) != 0){
        mpz_fdiv_q(q, r, rprime); //q = floor(r/r')
        
        mpz_set(temp1, r); //(r,r') = (r', r-1*r')
        mpz_set(r, rprime);
        mpz_sub(temp2, temp1, q);
        mpz_mul(rprime, temp2, rprime);

        mpz_set(temp1, t);//(t,t') = (t', t-1*t')
        mpz_set(t, tprime);
        mpz_sub(temp2, temp1, q);
        mpz_mul(tprime, temp2, tprime); 
    }
    if(mpz_cmp(r, 1)>0){// if r> 1
        mpz_set(o, 0);// return 0 aka no ivnerse
    }
    if(mpz_sign(t) == -1){// if t<0:
        mpx_add(t, t, n); // t = t+n
    }
    mpz_set(o, t); //return t
}

void pow_mod(mpz_t o, mpz_t a, mpz_t d, mpz_t n){
    mpz_t v, p, tempd;
    mpz_init_set(v, 1);
    mpz_init_set(p, a);
    mpz_init_set(tempd, d);
    while(mpz_sign(tempd) == 1){ //while d>0
        if(mpz_odd_p(tempd)!=0){// if d is odd
            mpz_mul(v, v, p);//v=(v*p)%n
            mpz_mod(v, v, n);
        }
    }
    mpz_mul(p, p, p);//p = (p*p)%n
    mpz_mod(p, p, n);
    mpz_fdiv_q_ui(d, d, 2);
    mpz_set(o, v);
}

bool witness(mpz_t randval, mpz_t n){
    //get d and r from randval and n
    mpz_t d, r;
    mpz_init_set(d, 0); 
    mpz_sub_ui(d, n, 1);// d = n-1
    mpz_init_set(r, 0); // r = 0;
    while(mpz_even_p(d)!=0){ // while d is even.
        mpz_fdiv_q_ui(d, d, 2); //d = floor(d/2);
        mpz_add_ui(r, r, 1); // r+=1;
    }
    //d and r values acquired, now to continue with witness

    mpz_t x, y, j;
    mpz_inits(x, y, j, 0);
    pow_mod(x, randval, d, n); // x = pow_mod(a, d, n)
    for(; mpz_cmp(j, r)<0; mpz_add_ui(j, j, 1)){ //for(int j= 0; j<r; j++)
        pow_mod(y, x, 2, n); //y = powmod(x, 2, n)
        if(mpz_cmp_ui(y, 1) == 0 && mpz_cmp_ui(x, 1) != 0 && mpz_cmp(x, tempn) != 0){// if y==1 and x != 1 and x!= n-1
            return true; 
        }
        mpz_set(x, y); //x = y
    }
    return mpz_cmp_ui(x, 1) != 0; // return x != 1
}

bool is_prime(mpz_t n, uint64_t iters){
    mpz_t tempvar, randomval; 
    mpz_inits(tempvar, randomval, NULL);

    mpz_mod_ui(tempvar, n, 2); // temporary value stores n%2
    if(mpz_cmp_ui(n, 2)<0 || (mpz_cmp_ui(n, 2) != 0 &&  mpz_sign(tempvar) == 0)){ //if n<2 or (n!=2 and n%2==0)
        return false;
    }
    if(mpz_cmp_ui(n, 2) == 0 || mpz_cmp_ui(n, 3)){ //if n==2 or n ==3
        return true;
    }

    //urandomm generates random val from 0 to upper limit. in order to shift range up, upper limit has to be n-4 rather than n-2, then 2 will be added to the random number
    mpz_sub_ui(tempv, n, 4); // temporary value set to n-4
    
    for(uint32_t i = 0; i<iters; i++){j
        mpz_urandomm(randomval, state, tempn);// random val from [2,n-2]
        mpz_add_ui(randomval, randomval, 2); // add 2 to random val
        //witness check
        if (witness(randomval, n)){
            return false;
        }
    }
    return true;
}

void make_prime(mpz_t p, uint64_t bits, uint64_t iters){
    gmp_randstate_t state;
    
    do{
        mpz_rrandomb(p, state, bits); 

    } while(!is_prime(p, iters));

}
