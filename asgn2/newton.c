#include "mathlib.h"

#include <assert.h>
#include <stdio.h>

static int iterations = 0;

double sqrt_newton(double x) {
    assert(x >= 0);
    double f = 1.0, // Scaling factor
        y = 1.0; // Initial guess
    while (x > 4) { // Normalize to [0, 4) by reducing the exponent in IEEE 754
        x /= 4.0; // Every 4 going in results in 2 going out since √4 = 2
        f *= 2.0;
        iterations++;
    }
    for (double guess = 0.0; absolute(y - guess) > EPSILON; y = (y + x / y) / 2.0) {
        guess = y;
    }
    return f * y; // Rescale back to the original range
}

int sqrt_newton_iters(void) {
    return iterations;
}
