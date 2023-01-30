//Written by Isabella Phung for CSE13S
#include "mathlib.h"

#include <stdio.h>

//for terms function
static int iterations = 0;

//estimates pi via the Mahava Series
//summation from 0 to n of
//((-3)^(-k))/(2k+1)
//Approximates until within 10^-14 of
//the accepted value of pi from math.h library
double pi_madhava(void) {
    double total = 1; //starts from 1 since (-3)^(0) is 1
    double numerator = 1;
    double denominator = 1;
    double factor = 1;

    iterations++;
    do {
        numerator = numerator * (-1.0 / 3.0);
        denominator += 2;
        factor = numerator / denominator;
        total += factor;
        iterations++;
    } while (absolute(factor) > EPSILON);

    total = sqrt_newton(12) * total;
    return total;
}

//returns total number of terms required to get within EPSILON
// of the accepted value of pi
int pi_madhava_terms(void) {
    return iterations;
}
