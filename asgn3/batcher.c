//Written by Isabella Phung for CSE13S
#include "stats.h"

#include <stdint.h>
#include <stdio.h>

//sorts array from lowest to highest value using Batcher sorting
//accepts stats structure, array of unsigned 32-bit ints, and
//a unsigned 32-bit int for the array size.
//code heavily based on python code provided by CSE13s instructors.
void batcher_sort(Stats *stats, uint32_t *A, uint32_t n) {
    if (n == 0) {
        return;
    }
    uint32_t t = 4;
    uint32_t p = 1 << (t - 1);
    uint32_t q;
    uint32_t r = 0;
    uint32_t d;
    while (p > 0) {
        q = 1 << (t - 1);

        r = 0;
        d = p;

        while (d > 0) {
            uint32_t temp = n - d;
            for (uint32_t i = 0; i < temp; i++) {
                if ((i & p) == r) {
                    if (cmp(stats, A[i], A[i + d]) == 1) {
                        swap(stats, &A[i], &A[i + d]);
                    }
                }
            }
            d = (q - p);
            q >>= 1;
            r = p;
        }
        p >>= 1;
    }
}
