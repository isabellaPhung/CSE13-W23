#include "mathlib.h"

#include <stdio.h>

int static iterations;

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
        //printf("%f\n", factor);
        total += factor;
    }
    return total;
}

int e_terms(void) {
    return iterations;
}
