#include "../inc/darrayAlgs.h"

int reverse_basic() {
    Darray d;
    darrayRangeTo(&d, 5);
    darrayReverse(&d);

    size_t expected[] = {4, 3, 2, 1, 0};
    if (darraySize(d) != 5) return 2;

    for (size_t i = 0; i < 5; i++) {
        size_t value;
        if (darrayGetAt(&d, i, &value) != DARRAY_OK) return 3;
        if (value != expected[i]) return 4;
    }

    return 0;
}