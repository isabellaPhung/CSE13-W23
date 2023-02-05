#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint32_t Set;

Set set_empty(void){
    Set s = 0;
    return s;
}

Set set_universal(void){
    Set s = 4294967295;
    return s;
}

Set set_insert(Set s, uint8_t x){
    int one = 1;
    int shift = one << x;
    s = s | shift;
    return s;
}

Set set_remove(Set s, uint8_t x){
    int zero = 0;
    int shift = zero << x;
    s = s | shift;
    return s;
}

bool set_member(Set s, uint8_t x){
    int one = 1;
    int shift = one << x;
    int checkVal = 0;
    checkVal = s & shift;
    if(checkVal != 0){
        return true;
    }
    return false;
}

Set set_union(Set s, Set t){
    Set newSet = s | t;
    return newSet;
}

Set set_intersect(Set s, Set t){
    Set newSet = s & t;
    return newSet;

}

Set set_difference(Set s, Set t){
    return s & ~t;
}

Set set_complement(Set s){
    return ~s;
}
