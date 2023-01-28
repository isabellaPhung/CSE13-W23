#include <stdio.h>
#include "mathlib.h"

static int iterations = 0;

double pi_viete(void){
    double numerator = newton_sqrt(2);
    int denominator = 2;
    double factor = 0;

    for(factor<EPSILON; factor++){
        numerator = newton_sqrt(2+numerator);
        factor = numerator/denominator;
        total += factor;
    }
    total = total/2;
    total = 1/total;
    return total;
}

int viete_terms(void){
    return iterations;
}
