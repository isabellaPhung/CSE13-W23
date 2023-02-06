//Written by Isabella Phung for CSE13S
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

//Series of set functions for manipulating a bit vector.
//A bit vector is considered a set with 32 items in it
//this file used to handle user inputs for sorting.

typedef uint32_t Set;

//creates and returns an empty set
Set set_empty(void) {
    Set s = 0;
    return s;
}

//creates and returns a set filled with 1s
Set set_universal(void) {
    Set s = 4294967295;
    return s;
}

//inserts a 1 at the specified index of the set
Set set_insert(Set s, uint8_t x) {
    uint32_t shift = 1 << x;
    s = s | shift;
    return s;
}

//inserts a 0 at the specified index of the set
Set set_remove(Set s, uint8_t x) {
    int zero = 0;
    int shift = zero << x;
    s = s | shift;
    return s;
}

//checks if the set contains a 1 at the indicated index
bool set_member(Set s, uint8_t x) {
    int one = 1;
    int shift = one << x;
    int checkVal = 0;
    checkVal = s & shift;
    if (checkVal != 0) {
        return true;
    }
    return false;
}

//performs a set union on two sets
Set set_union(Set s, Set t) {
    Set newSet = s | t;
    return newSet;
}

//performs a set intersection on two sets
Set set_intersect(Set s, Set t) {
    Set newSet = s & t;
    return newSet;
}

//performs set difference on two sets
Set set_difference(Set s, Set t) {
    return s & ~t;
}

//returns complement of a set
Set set_complement(Set s) {
    return ~s;
}
