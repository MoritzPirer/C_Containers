#include "../inc/darrayAlgs.h"

int sort_empty() {
    Darray d;
    darrayInit(&d, 0, sizeof(int));

    if (darraySort(&d, darrayDefaultOrdering) != DARRAY_OK) return 1;
    if (!darrayIsSortedAscending(d, darrayDefaultOrdering)) return 2;

    darrayDestroy(&d);
    return 0;
}

int sort_single() {
    Darray d;
    darrayInit(&d, 0, sizeof(int));

    int x = 42;
    darrayPushBack(&d, &x);

    if (darraySort(&d, darrayDefaultOrdering) != DARRAY_OK) return 1;
    if (!darrayIsSortedAscending(d, darrayDefaultOrdering)) return 2;

    darrayDestroy(&d);
    return 0;
}

int sort_already_sorted() {
    Darray d;
    darrayInit(&d, 0, sizeof(int));

    for (int i = 0; i < 10; i++) {
        darrayPushBack(&d, &i);
    }

    if (darraySort(&d, darrayDefaultOrdering) != DARRAY_OK) return 1;
    if (!darrayIsSortedAscending(d, darrayDefaultOrdering)) return 2;

    darrayDestroy(&d);
    return 0;
}

int sort_reverse() {
    Darray d;
    darrayInit(&d, 0, sizeof(int));

    for (int i = 9; i >= 0; i--) {
        darrayPushBack(&d, &i);
    }

    if (darraySort(&d, darrayDefaultOrdering) != DARRAY_OK) return 1;
    if (!darrayIsSortedAscending(d, darrayDefaultOrdering)) return 2;

    darrayDestroy(&d);
    return 0;
}

int sort_with_duplicates() {
    Darray d;
    darrayInit(&d, 0, sizeof(int));

    int values[] = {3, 1, 2, 3, 2, 1, 3};
    for (size_t i = 0; i < sizeof(values)/sizeof(values[0]); i++) {
        darrayPushBack(&d, &values[i]);
    }

    if (darraySort(&d, darrayDefaultOrdering) != DARRAY_OK) return 1;
    if (!darrayIsSortedAscending(d, darrayDefaultOrdering)) return 2;

    darrayDestroy(&d);
    return 0;
}

int sort_random_small() {
    Darray d;
    darrayInit(&d, 0, sizeof(int));

    int values[] = {4, 2, 9, 1, 5};
    for (size_t i = 0; i < sizeof(values)/sizeof(values[0]); i++) {
        darrayPushBack(&d, &values[i]);
    }

    if (darraySort(&d, darrayDefaultOrdering) != DARRAY_OK) return 1;
    if (!darrayIsSortedAscending(d, darrayDefaultOrdering)) return 2;

    darrayDestroy(&d);
    return 0;
}

int sort_all_equal() {
    Darray d;
    darrayInit(&d, 0, sizeof(int));

    int x = 7;
    for (int i = 0; i < 10; i++) {
        darrayPushBack(&d, &x);
    }

    if (darraySort(&d, darrayDefaultOrdering) != DARRAY_OK) return 1;
    if (!darrayIsSortedAscending(d, darrayDefaultOrdering)) return 2;

    darrayDestroy(&d);
    return 0;
}

