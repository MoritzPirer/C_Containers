#include "../inc/darrayAlgs.h"

int is_unique_simple() {
    Darray d;
    darrayInit(&d, 0, sizeof(size_t));

    for (size_t i = 0; i < 10; i++) {
        darrayPushBack(&d, &i);
    }

    if (!darrayIsUnique(d, darrayDefaultOrdering)) return 1;

    darrayDestroy(&d);
    return 0;
}

int is_unique_false() {

    Darray d;
    darrayInit(&d, 0, sizeof(size_t));

    for (size_t i = 0; i < 10; i++) {
        darrayPushBack(&d, &i);
    }
    size_t i = 9;
    darrayPushBack(&d, &i);

    if (darrayIsUnique(d, darrayDefaultOrdering)) return 1;

    darrayDestroy(&d);
    return 0;
}

int is_unique_empty() {
    Darray d;
    darrayInit(&d, 0, sizeof(size_t));


    if (!darrayIsUnique(d, darrayDefaultOrdering)) return 1;

    darrayDestroy(&d);
    return 0;
}

int is_unique_all_same() {
    Darray d;
    darrayInit(&d, 0, sizeof(int));

    int a = 10;
    for (int i = 0; i < 10; i++) {
        darrayPushBack(&d, &a);
    }

    if (darrayIsUnique(d, darrayDefaultOrdering)) return 1;

    darrayDestroy(&d);
    return 0;
}

int get_unique_simple() {
    Darray d;
    darrayInit(&d, 0, sizeof(int));

    for (int i = 0; i < 20; i++) {
        if (i % 2 == 1) i++;
        darrayPushBack(&d, &i);
    }

    Darray e;
    if (darrayGetUnique(&d, darrayDefaultOrdering, &e) != DARRAY_OK) return 1;

    if (!darrayIsUnique(e, darrayDefaultOrdering)) return 2; 

    darrayDestroy(&d);
    darrayDestroy(&e);
    return 0;
}

int get_unique_all_same() {
    Darray d;
    darrayInit(&d, 0, sizeof(int));

    int a = 10;
    for (int i = 0; i < 10; i++) {
        darrayPushBack(&d, &a);
    }

    Darray e;
    if (darrayGetUnique(&d, darrayDefaultOrdering, &e) != DARRAY_OK) return 1;

    if (!darrayIsUnique(e, darrayDefaultOrdering)) return 2; 

    darrayDestroy(&d);
    darrayDestroy(&e);
    return 0;
}

int get_unique_already_unique() {
    Darray d;
    darrayInit(&d, 0, sizeof(int));

    for (int i = 0; i < 10; i++) {
        darrayPushBack(&d, &i);
    }

    Darray e;
    if (darrayGetUnique(&d, darrayDefaultOrdering, &e) != DARRAY_OK) return 1;

    if (!darrayIsUnique(e, darrayDefaultOrdering)) return 2; 

    darrayDestroy(&d);
    darrayDestroy(&e);
    return 0;
}
