#include "../inc/darrayAlgs.h"
int range_simple_forward() {
    Darray d;
    darrayInit(&d, 0, sizeof(size_t));

    if (darrayRangeFromToStep(&d, 0, 5, 1) != DARRAY_OK) return 1;

    size_t expected[] = {0, 1, 2, 3, 4};
    if (darraySize(d) != 5) return 2;

    for (size_t i = 0; i < 5; i++) {
        size_t value;
        if (darrayGetAt(&d, i, &value) != DARRAY_OK) return 3;
        if (value != expected[i]) return 4;
    }

    darrayDestroy(&d);
    return 0;
}

int range_forward_step_two() {
    Darray d;
    darrayInit(&d, 0, sizeof(size_t));

    if (darrayRangeFromToStep(&d, 0, 10, 2) != DARRAY_OK) return 1;

    size_t expected[] = {0, 2, 4, 6, 8};
    if (darraySize(d) != 5) return 2;

    for (size_t i = 0; i < 5; i++) {
        size_t value;
        if (darrayGetAt(&d, i, &value) != DARRAY_OK) return 3;
        if (value != expected[i]) return 4;
    }

    darrayDestroy(&d);
    return 0;
}

int range_backward() {
    Darray d;
    darrayInit(&d, 0, sizeof(size_t));

    if (darrayRangeFromToStep(&d, 5, 0, -1) != DARRAY_OK) return 1;

    size_t expected[] = {5, 4, 3, 2, 1};
    if (darraySize(d) != 5) return 2;

    for (size_t i = 0; i < 5; i++) {
        size_t value;
        if (darrayGetAt(&d, i, &value) != DARRAY_OK) return 3;
        if (value != expected[i]) return 4;
    }

    darrayDestroy(&d);
    return 0;
}

int range_backward_step_two() {
    Darray d;
    darrayInit(&d, 0, sizeof(size_t));

    if (darrayRangeFromToStep(&d, 10, 0, -2) != DARRAY_OK) return 1;

    size_t expected[] = {10, 8, 6, 4, 2};
    if (darraySize(d) != 5) return 2;

    for (size_t i = 0; i < 5; i++) {
        size_t value;
        if (darrayGetAt(&d, i, &value) != DARRAY_OK) return 3;
        if (value != expected[i]) return 4;
    }

    darrayDestroy(&d);
    return 0;
}

int range_empty() {
    Darray d;
    darrayInit(&d, 0, sizeof(size_t));

    if (darrayRangeFromToStep(&d, 3, 3, 1) != DARRAY_OK) return 1;
    if (darraySize(d) != 0) return 2;

    darrayDestroy(&d);
    return 0;
}

int range_zero_step() {
    Darray d;
    darrayInit(&d, 0, sizeof(size_t));

    if (darrayRangeFromToStep(&d, 0, 5, 0) != DARRAY_ERROR_INVALID) return 1;

    darrayDestroy(&d);
    return 0;
}

int range_invalid_negative_step_forward() {
    Darray d;
    darrayInit(&d, 0, sizeof(size_t));

    if (darrayRangeFromToStep(&d, 0, 5, -1) != DARRAY_ERROR_INVALID) return 1;

    darrayDestroy(&d);
    return 0;
}

int range_invalid_positive_step_backward() {
    Darray d;
    darrayInit(&d, 0, sizeof(size_t));

    if (darrayRangeFromToStep(&d, 5, 0, 1) != DARRAY_ERROR_INVALID) return 1;

    darrayDestroy(&d);
    return 0;
}

int range_stop_exclusive() {
    Darray d;
    darrayInit(&d, 0, sizeof(size_t));

    if (darrayRangeFromToStep(&d, 0, 5, 3) != DARRAY_OK) return 1;

    size_t expected[] = {0, 3};
    if (darraySize(d) != 2) return 2;

    for (size_t i = 0; i < 2; i++) {
        size_t value;
        if (darrayGetAt(&d, i, &value) != DARRAY_OK) return 3;
        if (value != expected[i]) return 4;
    }

    darrayDestroy(&d);
    return 0;
}

int range_null_self() {
    if (darrayRangeFromToStep(NULL, 0, 5, 1) != DARRAY_ERROR_NULL) return 1;
    return 0;
}
