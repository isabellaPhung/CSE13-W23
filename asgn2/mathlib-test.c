#include "mathlib.h"

#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define OPTIONS "aebmrvnsh"

void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSYS\n"
        "   Approximates the value of pi using a\n"
        "   variety of different approximation methods.\n"
        "USAGE\n"
        "   %s [-aebmrvnsh]\n"
        "\n"
        "OPTIONS\n"
        "   -a  Runs all tests\n"
        "   -e  Runs e approimation\n"
        "   -b  Runs Bailey-Borwein-Plouffe pi approximation\n"
        "   -m  Runs Madhava pi approximation\n"
        "   -r  Runs Euler sequence pi approximation\n"
        "   -v  Runs Viete pi approximation\n"
        "   -n  Runs Newton square root approximations\n"
        "   -s  Prints statistics to see terms and factors computed\n"
        "   -h  description/help\n",
        exec);
}

void e_test(void){ 
    double e_value = e();
    printf("e() = %6.15f, M_E = %6.15f Difference: %6.15f\n", e_value, M_E, M_E - e_value);
}

void bbp_test(void){ 
     double pi = pi_bbp();
     printf("pi_bbp() = %6.15f, M_PI = %6.15f Difference: %6.15f\n", pi, M_PI, M_PI - pi);
}

void madhava_test(void){
    double pi = pi_madhava();
    printf("pi_madhava() = %6.15f, M_PI = %6.15f Difference: %6.15f\n" , pi, M_PI, M_PI - pi);
}

void euler_test(void){
    double pi = pi_euler();
    printf("pi_euler() = %6.15f, M_PI = %6.15f Difference: %6.15f\n", pi, M_PI, M_PI - pi);
}

void viete_test(void){
    double pi = pi_viete();
    printf("pi_viete() = %6.15f, M_PI = %6.15f Difference: %6.15f\n", pi, M_PI, M_PI - pi);
}

void newton_test(void){
    double MI_sqrt;
    double sqrt_value;
    for (int i = 1; i <= 10; i++) {
        sqrt_value = sqrt_newton(i);
        MI_sqrt = sqrt(i);
        printf("sqrt_newton(%d) = %6.15f, sqrt(%d) = %6.15f Difference: %6.15f\n", i, sqrt_value, i, MI_sqrt, MI_sqrt - sqrt_value);
    }
}

int main(int argc, char **argv) {
    int opt = 0;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a': 
            e_test();
            bbp_test();
            madhava_test();
            euler_test();
            viete_test();
            newton_test();
            break;
        case 'e':
            e_test();
            break;
        case 'b':
            bbp_test();
            break;
        case 'm':
            madhava_test(); 
            break;
        case 'r':
            euler_test();  
            break;
        case 'v':
            viete_test();  
            break;
        case 'n':
            newton_test();
            break;
        default:
            usage(argv[0]);
            return EXIT_FAILURE;
        }
        return 0;
    }
}
