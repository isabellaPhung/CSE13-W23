#include "mathlib.h"

#include <stdio.h>

static int iterations = 0;

double pi_viete(void) {
    double numerator = sqrt_newton(2);
    double denominator = 2;
    double factor = 0;
    double total = 1;

    do{
        factor = numerator / denominator;
        //printf("%f\n", 1-factor);
        total = total*factor;
        numerator = sqrt_newton(2 + numerator);
        iterations++;
    } while (1 - factor > EPSILON);
    total = 2/total;
    return total;
}

int pi_viete_factors(void) {
    return iterations;
}
