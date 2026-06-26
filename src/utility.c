#include "utility.h"

void swap(size_t* a, size_t* b) {
    size_t temp = *a;
    *a = *b;
    *b = temp;
}

size_t next_power_of_two(size_t n) {
    size_t m = 1;

    while (m < n) {
        m <<= 1;
    }

    return m;
}

size_t previous_power_of_two(size_t n) {
    if (n & (n - 1) == 0) {
        return n;
    }

    size_t upper = 2UL;
    size_t lower = 1UL;
    
    while (upper < n) {
        upper <<= 1;
        lower <<= 1;
    }
    
    return lower;
}

size_t is_power_of_two(size_t n) {
    return n & (n - 1) == 0;
}