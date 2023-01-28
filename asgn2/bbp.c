#include <stdio.h>
#include "mathlib.h"

static int iterations = 0;

double pi_bbp(void){
    double numerator = 0;
    double denominator = 0;
    double total = 0;
    double sixteenFactor = 1;
    double factor = 0;

    for(factor < EPSILON; iterations++){
        numerator = iterations*(120*iterations+151)+47;
        denominator = iterations*(iterations*(iterations*(512*i+1024)+712)+194)+15;
        factor = sixteenFactor * (numerator/denominator);
        total += factor;
        sixteenFactor = sixteenFactor * (1/16);
    }
    return total;
}

int bbp_terms(void){
    return iterations;
}
