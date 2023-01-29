#include "mathlib.h"

#include <stdio.h>

static int iterations = 0;

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
        //printf("%f\n", factor);
    }
    return total;
}

int pi_bbp_terms(void) {
    return iterations;
}
