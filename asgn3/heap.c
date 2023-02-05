//Written by Isabella Phung for CSE13S
#include "stats.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

//sorts array from lowest to highest value using heap sorting
//accepts stats structure, array of unsigned 32-bit ints, and
//a unsigned 32-bit int for the array size.
//code heavily based on python code provided by CSE13s instructors.

//helper function, returns largest child node of parent
uint32_t max_child(Stats *stats, uint32_t *arr, uint32_t cursor, uint32_t last) {
    uint32_t left = 2 * cursor;
    uint32_t right = 2 * cursor + 1;
    if (right <= last && cmp(stats, arr[right - 1], arr[left - 1]) == 1) {
        return right;
    }
    return left;
}

//helper function, ensures all arrays are in heap format
void fix_heap(Stats *stats, uint32_t *arr, uint32_t cursor, uint32_t last) {
    bool placeFound = false;
    uint32_t parent = cursor;
    uint32_t bigChild = max_child(stats, arr, parent, last);
    while (parent <= last / 2 && !placeFound) {
        if (cmp(stats, arr[parent - 1], arr[bigChild - 1]) == -1) {
            swap(stats, &arr[parent - 1], &arr[bigChild - 1]);
            parent = bigChild;
            bigChild = max_child(stats, arr, parent, last);
        } else {
            placeFound = true;
        }
    }
}

//builds a heap out of any array
void build_heap(Stats *stats, uint32_t *arr, uint32_t first, uint32_t last) {
    for (uint32_t i = last / 2; i > first - 1; i--) {
        fix_heap(stats, arr, i, last);
    }
}

//assuming n is array length
void heap_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t first = 1;
    build_heap(stats, A, first, n);
    for (uint32_t i = n; i > first; i--) {
        swap(stats, &A[0], &A[i - 1]);
        fix_heap(stats, A, first, i - 1);
    }
}
