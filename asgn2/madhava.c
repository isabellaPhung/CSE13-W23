#include <stdio.h>
#include "mathlib.h"

static int iterations = 0;

double pi_madhava(void){
    double total = 1;
    double numerator = -1;
    int denominator = 1;
    double factor = 0; 

    iteration++;
    for(factor < EPSILON; iterations++){
       numerator = numerator*(1.0/3.0);
       denominator += 2;
       factor = numerator/denominator;
       total += factor;
    }
    total = newton_sqrt(12) * total;
    return total;
}

int madhava_terms(void){
    return iterations;
}
