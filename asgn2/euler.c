#include <stdio.h>
#include "mathlib.h"

static int iterations = 0;
double pi_euler(void){
    double total = 0;
    double factor = 0;

    for(factor < EPSILON; iterations++){
        factor = 1/(iterations*iterations);
        total += factor;
    }
    total = 6*total;
    total = newton_sqrt(total);
    return total;
}

int euler_terms(void){
    return iterations;
}
