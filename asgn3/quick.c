#include <stdio.h>
#include <stdint.h>
#include "stats.h"
#include <inttypes.h>

/*
void printArrayy(uint32_t *arr, int length){
    for(int i = 0; i<length; i++){
        printf("%" PRIu32 ", ", arr[i]);
    }
    printf("\n");
}*/

uint32_t partition(Stats *stats, uint32_t *arr, uint32_t low, uint32_t high){
    uint32_t i = low;
    for(uint32_t j = low; j < high - 1; j++){
        //printf("j: %" PRIu32 "\n", j);
        if (cmp(stats, arr[j], arr[high-1]) == -1){
            //printf("%"PRIu32"<%"PRIu32"\n", arr[j], arr[high-1]);
        //if arr[j] < arr[high-1]{
            i++;
            //printArrayy(arr, 10); 
            //printf("i: %"PRIu32"\n", i);
            //printf("swap: %"PRIu32" %"PRIu32"\n", arr[i-1], arr[j]);
            //printf("address: %p\n", (void*)&arr[j]);
            swap(stats, &arr[i-1], &arr[j]);
        }
        
    }
    swap(stats, &arr[i], &arr[high-1]);
    //printf("second swap: %"PRIu32" %"PRIu32"\n", arr[i], arr[high-1]);
    return i;
}


void quick_sorter(Stats *stats, uint32_t *arr, uint32_t low, uint32_t high){
    uint32_t p; 
    if(low < high){
        p = partition(stats, arr, low, high);
        //printf("partition: %"PRIu32"\n", p);
        //printArrayy(arr, 10);
        //printf("\n");
        quick_sorter(stats, arr, low, p);
        quick_sorter(stats, arr, p+1, high);
    }
}

void quick_sort(Stats *stats, uint32_t *A, uint32_t n){
    quick_sorter(stats, A, 0, n);
}
