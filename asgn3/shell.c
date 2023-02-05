//Written by Isabella Phung for CSE13S
#include "gaps.h"
#include "stats.h"
#include <stdint.h>
#include <stdio.h>

//sorts array from lowest to highest value using shell sorting
//accepts stats structure, array of unsigned 32-bit ints, and
//a unsigned 32-bit int for the array size.
//code heavily based on python code provided by CSE13s instructors.
void shell_sort(Stats *stats, uint32_t *arr, uint32_t length) {
    int32_t k;
    int32_t value;
    int32_t gap;
    for (uint32_t i = 0; i < GAPS; i++) {
        gap = gaps[i];
        for (uint32_t j = gap; j < length; j++) { //only uses gap values below array length
            k = j; //this value will be changed, but it starts at gap index
            value = move(stats, arr[j]);
            while ((cmp(stats, k, gap) == 1 || cmp(stats, k, gap) == 0)
                   && cmp(stats, value, arr[k - gap]) == -1) {
                // while(k >= gaps[i] && value < arr[k-gaps[i]]){ //k >= gaps ensures not going to exceed array length. compares value to value towards beginning of array that is gap distance away. If value needs to be swapped, proceeds with this loop.
                arr[k] = move(stats, arr[k - gap]);
                //arr[k] = arr[k-gaps[i]]; //assigns far value into current spot if swap needed
                k -= gap;
            }
            arr[k] = move(stats, value); //not 100% sure if this is considered a move
            //arr[k] = value;
        }
    }
}
