//Written by Isabella Phung for CSE13S
#include "mathlib.h"
#include <stdio.h>

//for terms function
int static iterations;

//estimates e via Taylor Series
//summation from 0 to n of 1/(k!)
//Approximates until within 10^-14 of
//the accepted value of e from math.h library
double e(void) {
    double factor = 1;
    double total = 0;
    double denominator = 0;

    total = 1;
    iterations = 1;
    denominator = 1;
    for (; factor > EPSILON; iterations++) {
        denominator = denominator * iterations; 
        factor = 1.0 / denominator;
        total += factor;
    }
    return total;
}

//returns total number of terms required to get within EPSILON
// of the accepted value of e
int e_terms(void) {
    return iterations;
}
