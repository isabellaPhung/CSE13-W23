//Written by Isabella Phung for CSE13S
#include "stats.h"
#include <stdint.h>
#include <stdio.h>

//sorts array from lowest to highest value using quick sorting
//accepts stats structure, array of unsigned 32-bit ints, and
//a unsigned 32-bit int for the array size.
//code heavily based on python code provided by CSE13s instructors.

//helper function, returns partition index
uint32_t partition(Stats *stats, uint32_t *arr, uint32_t low, uint32_t high) {
    uint32_t i = low;
    for (uint32_t j = low; j < high - 1; j++) {
        if (cmp(stats, arr[j], arr[high - 1]) == -1) {
            i++;
            swap(stats, &arr[i - 1], &arr[j]);
        }
    }
    swap(stats, &arr[i], &arr[high - 1]);
    return i;
}

//recursive helper function, to sort partitioned array
void quick_sorter(Stats *stats, uint32_t *arr, uint32_t low, uint32_t high) {
    uint32_t p;
    if (low < high) {
        p = partition(stats, arr, low, high);
        quick_sorter(stats, arr, low, p);
        quick_sorter(stats, arr, p + 1, high);
    }
}

void quick_sort(Stats *stats, uint32_t *A, uint32_t n) {
    quick_sorter(stats, A, 0, n);
}
