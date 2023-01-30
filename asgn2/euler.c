//Written by Isabella Phung for CSE13S
#include "mathlib.h"
#include <stdint.h>
#include <stdio.h>

//for terms function
static int iterations = 0;

//estimates pi via Euler's Solution
//summation from 1 to n of 
//16^(-k)*(k(120k+151)+47)/k(k(k(512k+1024)+712)+194)+15
//Approximates until 10000 iterations have
//been reached or within 10^-14 of
//the accepted value of pi from math.h library
double pi_euler(void) {
    double total = 0;
    double factor = 1;
    int denominator;

    iterations++;
    //tried to figure out how to get higher accuracy using
    //larger size integers, but despite being able to be
    //more accurate the program would take significantly longer
    //to run.
    //uint32_t denominator = UINT32_C(50000*50000);
    //double factor = 1.0/denominator;
    //printf("%5.16f\n", factor );
    
    for (;  absolute(factor) > EPSILON && iterations < 10000; iterations++) {
        denominator = iterations * iterations;
        factor = 1.0 / denominator;
        total += factor;
    }
    total = 6 * total;
    total = sqrt_newton(total);
    return total;
}

//returns total number of terms program performed
//for estimation
int pi_euler_terms(void) {
    return iterations;
}
