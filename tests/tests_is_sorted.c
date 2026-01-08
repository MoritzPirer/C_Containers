#include "../inc/darrayAlgs.h"


int is_sorted_asc_simple() {
    Darray d;
    darrayInit(&d, 0, sizeof(size_t));

    for (size_t i = 0; i < 10; i++) {
        darrayPushBack(&d, &i);
    }

    if (!darrayIsSortedAscending(d, darrayDefaultOrdering)) return 1;

    darrayDestroy(&d);
    return 0;
}

int is_sorted_empty() {
    Darray d;
    darrayInit(&d, 0, sizeof(size_t));


    if (!darrayIsSortedAscending(d, darrayDefaultOrdering)) return 1;

    darrayDestroy(&d);
    return 0;
}

int is_sorted_asc_all_same() {
    Darray d;
    darrayInit(&d, 0, sizeof(size_t));
    size_t val = 10;
    for (size_t i = 0; i < 10; i++) {
        darrayPushBack(&d, &val);
    }

    if (!darrayIsSortedAscending(d, darrayDefaultOrdering)) return 1;

    darrayDestroy(&d);
    return 0;
}

int is_sorted_asc_false() {
    Darray d;
    darrayInit(&d, 0, sizeof(size_t));

    for (size_t i = 20; i > 10; i--) {
        darrayPushBack(&d, &i);
    }

    if (darrayIsSortedAscending(d, darrayDefaultOrdering)) return 1;

    darrayDestroy(&d);

    return 0;
}





int is_sorted_desc_simple() {
    Darray d;
    darrayInit(&d, 0, sizeof(size_t));

    for (size_t i = 20; i > 10; i--) {
        darrayPushBack(&d, &i);
    }

    if (!darrayIsSortedDescending(d, darrayDefaultOrdering)) return 1;

    darrayDestroy(&d);
    return 0;
}

int is_sorted_desc_all_same() {
    Darray d;
    darrayInit(&d, 0, sizeof(size_t));
    size_t val = 10;
    for (size_t i = 0; i < 10; i++) {
        darrayPushBack(&d, &val);
    }

    if (!darrayIsSortedDescending(d, darrayDefaultOrdering)) return 1;

    darrayDestroy(&d);
    return 0;
}

int is_sorted_desc_false() {
    Darray d;
    darrayInit(&d, 0, sizeof(size_t));

    for (size_t i = 0; i < 10; i++) {
        darrayPushBack(&d, &i);
    }

    if (darrayIsSortedDescending(d, darrayDefaultOrdering)) return 1;

    darrayDestroy(&d);

    return 0;
}