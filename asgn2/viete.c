#include "mathlib.h"

#include <stdio.h>

static int iterations = 0;

double pi_viete(void) {
    double numerator = sqrt_newton(2);
    int denominator = 2;
    double factor = 0;
    double total = 0;

    for (; factor < EPSILON; factor++) {
        numerator = sqrt_newton(2 + numerator);
        factor = numerator / denominator;
        total += factor;
    }
    total = total / 2;
    total = 1 / total;
    return total;
}

int viete_terms(void) {
    return iterations;
}
