#include <stdio.h>
#include "mathlib.h"

int static iterations;

int e(void){
    double factor;
    double total;
    
    total = 1;
    iterations = 1;
    denominator = 1;
    for(factor < EPSILON; iterations++){
        denominator = denominator * iterations;
        factor = 1/denominator;
        total += factor; 
    }
    return total;
}

int e_terms(void){
    return iterations;
}

int main(void){
    printf(e());
}
