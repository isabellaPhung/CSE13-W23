//Written by Isabella Phung for CSE13S
#include "mathlib.h"
#include <stdio.h>

//for terms function
static int iterations = 0;

//estimates pi via Viete's Formula
//pi product from 1 to k of 
//(2/pi) = sqrt(2+a_(k-1))/2 where a_1 = sqrt(2)
//Approximates until within 10^-14 of
//the accepted value of pi from math.h library
double pi_viete(void) {
    double numerator = sqrt_newton(2);
    double denominator = 2;
    double factor = 0;
    double total = 1;

    do{
        factor = numerator / denominator;
        total = total * factor;
        numerator = sqrt_newton(2 + numerator);
        iterations++;
    } while (1 - factor > EPSILON);
    total = 2 / total;
    return total;
}

//returns total number of terms required to get within EPSILON
// of the accepted value of pi
int pi_viete_factors(void) {
    return iterations;
}
