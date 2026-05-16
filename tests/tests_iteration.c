#include "../inc/vec/vec_algs.h"

int reverse_basic() {
    vec_t vec;
    vec_range_to(&vec, 5);
    vec_reverse(&vec);

    size_t expected[] = {4, 3, 2, 1, 0};
    if (vec_size(&vec) != 5) {
        return 2;
    }

    for (size_t i = 0; i < 5; i++) {
        size_t value;
        if (vec_get(&vec, i, &value) != VEC_OK)
            return 3;
        if (value != expected[i])
            return 4;
    }

    return 0;
}