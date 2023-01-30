//Written by Isabella Phung for CSE13S
#include "mathlib.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define OPTIONS "aebmrvnsh"

//prints instructions for use
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
    int is_e = 0;
    int is_bbp = 0;
    int is_madhava = 0;
    int is_euler = 0;
    int is_viete = 0;
    int is_newton = 0;
    int terms = 0;
    //first runs through all arguments first and
    //determines which ones have been called
    //before performing and outputing tests
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {    
        switch (opt) {
        case 'a': 
            is_e = 1;
            is_bbp = 1;
            is_madhava = 1;
            is_euler = 1;
            is_viete = 1;
            is_newton = 1;
            break;
        case 'e':
            is_e = 1;
            break;
        case 'b':
            is_bbp = 1;
            break;
        case 'm':
            is_madhava = 1; 
            break;
        case 'r':
            is_euler = 1; 
            break;
        case 'v':
            is_viete = 1; 
            break;
        case 'n':
            is_newton = 1;
            break;
        case 's':
            terms = 1;
            break;
        default:
            usage(argv[0]);
            return EXIT_FAILURE;
        }
    }

    if(is_e > 0){
        e_test();
        if(terms > 0){
            printf("e terms = %d\n", e_terms());
        }
    }
    if(is_bbp > 0){
        bbp_test();

        if(terms > 0){
            printf("pi_bbp terms = %d\n", pi_bbp_terms());
        }
    }
    if(is_madhava > 0){
        madhava_test();

        if(terms > 0){
            printf("pi_madhava terms = %d\n", pi_madhava_terms());
        }
    }
    if(is_euler > 0){
        euler_test();

        if(terms > 0){
            printf("pi_euler terms = %d\n", pi_euler_terms());
        }
    }
    if(is_viete > 0){
        viete_test();

        if(terms > 0){
            printf("pi_viete terms = %d\n", pi_viete_factors());
        }
    }
    if(is_newton > 0){
        newton_test();

        if(terms > 0){
            printf("newton terms = %d\n", sqrt_newton_iters());
        }
    }


    return 0;
}
