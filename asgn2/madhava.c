#include "mathlib.h"

#include <stdio.h>

static int iterations = 0;

double pi_madhava(void) {
    double total = 1;
    double numerator = 1;
    double denominator = 1;
    double factor = 1;

    iterations++;
    do{
        numerator = numerator * (-1.0 / 3.0);
        denominator += 2;
        factor = numerator / denominator; 
        total += factor; 
        //printf("%f\n",total);
        iterations++;
    }while(absolute(factor) > EPSILON);
    
    total = sqrt_newton(12) * total;
    return total;
}

int madhava_terms(void) {
    return iterations;
}
