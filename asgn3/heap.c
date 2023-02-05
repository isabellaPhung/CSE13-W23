#include <stdio.h>
#include <stdint.h>
#include "stats.h"
#include <stdbool.h>
#include <inttypes.h>

/*
void printArrayy(uint32_t *arr, int length){
    for(int i = 0; i<length; i++){
        printf("%" PRIu32 ", ", arr[i]);
    }
    printf("\n");
}*/

uint32_t max_child(Stats *stats, uint32_t *arr, uint32_t cursor, uint32_t last){
    uint32_t left = 2 * cursor;
    uint32_t right = 2 * cursor + 1; 
    //printf("right: %"PRIu32"\n", right);
    //printf("left: %"PRIu32"\n", left);
    //printf("%"PRIu32">%"PRIu32"\n", arr[right-1], arr[left-1]);
    if (right <= last && cmp(stats, arr[right-1], arr[left-1])==1){
        return right;
    }
    return left;
}

void fix_heap(Stats *stats, uint32_t *arr, uint32_t cursor, uint32_t last){
    bool placeFound = false;
    uint32_t parent = cursor;
    //printf("mother: %"PRIu32"\n", parent);
    uint32_t bigChild = max_child(stats, arr, parent, last);
    //printf("bigChild: %"PRIu32"\n", bigChild);
    while (parent <= last / 2 && !placeFound){
        //printf("%"PRIu32"<%"PRIu32"\n", arr[parent-1], arr[bigChild-1]);
        if (cmp(stats, arr[parent - 1], arr[bigChild - 1]) == -1){ 
            swap(stats, &arr[parent - 1], &arr[bigChild - 1]);
            //printArrayy(arr, 10);
            parent = bigChild;
            bigChild = max_child(stats, arr, parent, last);
        }else{
            //printf("yes");
            placeFound = true;
        }
    }
}

void build_heap(Stats *stats, uint32_t *arr, uint32_t first, uint32_t last){
    for(uint32_t i = last / 2; i > first-1; i--){
        //printf("%"PRIu32"\n", i);
        fix_heap(stats, arr, i, last);
    }
    //printf("heap built\n");
    //printArrayy(arr, 10);
}
//assuming n is length
void heap_sort(Stats *stats, uint32_t *A, uint32_t n){
    uint32_t first = 1;
    build_heap(stats, A, first, n);
    //printf("\nbegin sorting\n");
    //printArrayy(A,10);
    for(uint32_t i = n; i > first; i--){
        //printf("i: %"PRIu32"\n", i);
        swap(stats, &A[0], &A[i-1]);
        fix_heap(stats, A, first, i-1);
    }
}
