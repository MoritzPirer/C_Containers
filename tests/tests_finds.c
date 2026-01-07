#include "../inc/darrayAlgs.h"

bool condition(const void* element, const void* data) {
    return (*(size_t*) element == *(size_t*) data);
}

int ordering(const void* a, const void* b) {
    return (*(size_t*) a - *(size_t*) b);
}

int find_first_one_option() {
    Darray d;
    darrayInit(&d, 0, sizeof(size_t));

    for (size_t i = 0; i < 10; i++) {
        darrayPushBack(&d, &i);
    }
    size_t temp;
    size_t target = 2;
    DarrayStatus res = darrayFindFirst(&d, condition, &temp, &target);
    if (res != DARRAY_OK) return 1;
    if (temp != 2) return 2;

    darrayDestroy(&d);
    return 0;
}

int find_first_two_options() {
    Darray d;
    darrayInit(&d, 0, sizeof(size_t));

    for (size_t i = 0; i < 10; i++) {
        darrayPushBack(&d, &i);
    }
    size_t temp = 2;
    darrayPushBack(&d, &temp);

    size_t target = 2;
    DarrayStatus res = darrayFindFirst(&d, condition, &temp, &target);
    if (res != DARRAY_OK) return 1;
    if (temp != 2) return 2;

    darrayDestroy(&d);
    return 0;
}

int find_first_no_option() {
    Darray d;
    darrayInit(&d, 0, sizeof(size_t));

    for (size_t i = 0; i < 10; i++) {
        darrayPushBack(&d, &i);
    }
    size_t temp;

    size_t target = 15;
    DarrayStatus res = darrayFindFirst(&d, condition, &temp, &target);
    if (res != DARRAY_NOT_FOUND) return 1;

    darrayDestroy(&d);
    return 0;
}

int find_last_one_option() {
    Darray d;
    darrayInit(&d, 0, sizeof(size_t));

    for (size_t i = 0; i < 10; i++) {
        darrayPushBack(&d, &i);
    }
    size_t temp;
    size_t target = 2;
    DarrayStatus res = darrayFindLast(&d, condition, &temp, &target);
    if (res != DARRAY_OK) return 1;
    if (temp != 2) return 2;

    darrayDestroy(&d);
    return 0;
}

int find_last_two_options() {
    Darray d;
    darrayInit(&d, 0, sizeof(size_t));

    for (size_t i = 0; i < 10; i++) {
        darrayPushBack(&d, &i);
    }
    size_t temp = 2;
    darrayPushBack(&d, &temp);

    size_t target = 2;
    DarrayStatus res = darrayFindLast(&d, condition, &temp, &target);
    if (res != DARRAY_OK) return 1;
    if (temp != 10) return 2;

    darrayDestroy(&d);
    return 0;
}

int find_last_no_option() {
    Darray d;
    darrayInit(&d, 0, sizeof(size_t));

    for (size_t i = 0; i < 10; i++) {
        darrayPushBack(&d, &i);
    }
    size_t temp;

    size_t target = 15;
    DarrayStatus res = darrayFindLast(&d, condition, &temp, &target);
    if (res != DARRAY_NOT_FOUND) return 1;

    darrayDestroy(&d);
    return 0;
}

int find_first_last_empty() {
    Darray d;
    darrayInit(&d, 0, sizeof(size_t));
    size_t temp = 1;
    if (darrayFindFirst(&d, condition, &temp, &temp) != DARRAY_NOT_FOUND) return 1;
    if (darrayFindLast(&d, condition, &temp, &temp) != DARRAY_NOT_FOUND) return 2;

    return 0;
}

int binary_search_simple() {
    Darray d;
    darrayInit(&d, 0, sizeof(size_t));

    for (size_t i = 0; i < 10; i++) {
        darrayPushBack(&d, &i);
    }
    size_t temp;
    size_t target = 2;
    DarrayStatus res = darrayBinarySearch(&d, ordering, &temp, &target);
    if (res != DARRAY_OK) return 1;
    if (temp != 2) return 2;

    darrayDestroy(&d);
    return 0;
}

int binary_search_empty() {
    Darray d;
    darrayInit(&d, 0, sizeof(size_t));

    size_t temp;
    size_t target = 2;
    DarrayStatus res = darrayBinarySearch(&d, ordering, &temp, &target);
    if (res != DARRAY_NOT_FOUND) return 1;

    darrayDestroy(&d);
    return 0;
}

int binary_search_small() {
    Darray d;
    darrayInit(&d, 0, sizeof(size_t));

    for (size_t i = 0; i < 3; i++) {
        darrayPushBack(&d, &i);
    }

    size_t temp;
    size_t target = 2;
    DarrayStatus res = darrayBinarySearch(&d, ordering, &temp, &target);
    if (res != DARRAY_OK) return 1;
    if (temp != 2) return 2;

    darrayDestroy(&d);
    return 0;
}