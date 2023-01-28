#include <stdio.h>
#include "mathlib.h"
#include <math.h>

void usage(char *exec){
    fprintf(stderr,
        "SYNOPSYS\n"
        "   Approximates the value of pi using a" 
        "   variety of different approximation methods."
        "USAGE\n"
        "   %s [-aebmrvnsh]\n"
        "\n"
        "OPTIONS\n"
        "   -a  Runs all tests"
        "   -e  Runs e approimation"
        "   -b  Runs Bailey-Borwein-Plouffe pi approximation"
        "   -m  Runs Madhava pi approximation"
        "   -r  Runs Euler sequence pi approximation"
        "   -v  Runs Viete pi approximation"
        "   -n  Runs Newton square root approximations"
        exec);
}

int main(int argc, char **argv){
    int opt = 0;

    while((opt = getopt(argc, argv, OPTIONS)) != -1){
        switch(opt){
            double pi;
            case 'a':
                
                
            case 'e':
                double e = e();
                printf("e() = %6.15f, M_E = %6.15f Difference: %6.15f", e, M_E, M_E - e);
                break;
            case 'b':
                pi = pi_bbp();
                printf("pi_bbp() = %6.15f, M_PI = %6.15f Difference: %6.15f", pi, M_PI, M_PI - pi);
                break;
            case 'm':
                pi = pi_madhava();
                printf("pi_madhava() = %6.15f, M_PI = %6.15f Difference: %6.15f", pi, M_PI, M_PI - pi);
                break;
            case 'r':
                pi = pi_euler();
                printf("pi_euler() = %6.15f, M_PI = %6.15f Difference: %6.15f", pi, M_PI, M_PI - pi);
                break;
            case 'v':
                pi = pi_viete();
                printf("pi_viete() = %6.15f, M_PI = %6.15f Difference: %6.15f", pi, M_PI, M_PI - pi);
                break;
            case 'n':
                for(int i = 0; i < 10; i++){
                    sqrt = sqrt_newton(i);
                printf("sqrt_newton() = %6.15f, sqrt(%f) = %6.15f Difference: %6.15f", sqrt, sqrt(i), i, sqrt(i) - sqrt);
                }
                break;
        }
    return 0;
}
