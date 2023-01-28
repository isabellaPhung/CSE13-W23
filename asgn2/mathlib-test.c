#include <stdio.h>
#include "mathlib.h"
#include <math.h>
#include <unistd.h>

#define OPTIONS "aebmrvn"

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
        "   -n  Runs Newton square root approximations",
        exec);
}

int main(int argc, char **argv){
    int opt = 0;

    while((opt = getopt(argc, argv, OPTIONS)) != -1){
        switch(opt){
            double pi;
            double e_value;
            double sqrt_value;
            case 'a':
                
                break; 
            case 'e':
                e_value = e();
                printf("e() = %6.15f, M_E = %6.15f Difference: %6.15f", e_value, M_E, M_E - e_value);
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
                    sqrt_value = sqrt_newton(i);
                    printf("sqrt_newton() = %6.15f, sqrt(%d) = %6.15f Difference: %6.15f", sqrt_value, i, sqrt(i), sqrt(i) - sqrt_value);
                }
                break;
        }
    return 0;
    } 
}
