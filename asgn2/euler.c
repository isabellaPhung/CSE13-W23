#include "mathlib.h"
#include <stdint.h>
#include <stdio.h>

static int iterations = 0;
double pi_euler(void) {
    double total = 0;
    double factor = 1;
    int denominator;

    iterations++;
    //uint32_t denominator = UINT32_C(50000*50000);
    //double factor = 1.0/denominator;
    //printf("%5.16f\n", factor );
    
    for (;  absolute(factor) > EPSILON && iterations < 10000; iterations++) {
        denominator = iterations * iterations;
        factor = 1.0 / denominator;
        total += factor;
        //printf("%d\n", iterations); 
       // printf("%5.16f\n", factor);
        //printf("%i\n", denominator);
    }
    total = 6 * total;
    total = sqrt_newton(total);
    return total;
}

int pi_euler_terms(void) {
    return iterations;
}
