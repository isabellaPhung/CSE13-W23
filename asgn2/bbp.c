//Written by Isabella Phung for CSE13S
#include "mathlib.h"

#include <stdio.h>

//for terms function
static int iterations = 0;

//estimates pi via Biley-Borwein-Plouffe Formula
//summation from 0 to n of
//16^(-k)*(k(120k+151)+47)/k(k(k(512k+1024)+712)+194)+15
//Approximates until within 10^-14 of
//the accepted value of pi from math.h library
double pi_bbp(void) {
    double numerator = 0;
    double denominator = 0;
    double total = 0;
    double sixteenFactor = 1;
    double factor = 1;

    for (; factor > EPSILON; iterations++) {
        numerator = iterations * (120 * iterations + 151) + 47;
        denominator
            = iterations * (iterations * (iterations * (512 * iterations + 1024) + 712) + 194) + 15;
        factor = sixteenFactor * (numerator / denominator);
        total += factor;
        sixteenFactor = sixteenFactor * (1.0 / 16.0);
    }
    return total;
}

//returns total number of terms required to get within EPSILON
// of the accepted value of pi
int pi_bbp_terms(void) {
    return iterations;
}
