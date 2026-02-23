#include "../inc/darrayAlgs.h"

int get_union_basic() {
    Darray a, b, out;
    darrayInit(&a, 0, sizeof(int));
    darrayInit(&b, 0, sizeof(int));

    int av[] = {1, 2, 3, 4, 5};
    int bv[] = {3, 4, 5, 6, 7};

    for (int i = 0; i < 5; i++) {
        darrayPushBack(&a, &av[i]);
        darrayPushBack(&b, &bv[i]);
    }

    if (darrayGetUnion(&a, &b, darrayDefaultOrdering, &out) != DARRAY_OK)
        return 1;

    if (darraySize(out) != 7)
        return 2;

    int expected[] = {1, 2, 3, 4, 5, 6, 7};
    for (int i = 0; i < 7; i++) {
        int v;
        darrayGetAt(&out, i, &v);
        if (v != expected[i]) return 3;
    }

    darrayDestroy(&a);
    darrayDestroy(&b);
    darrayDestroy(&out);
    return 0;
}

int get_union_left_empty() {
    Darray a, b, out;
    darrayInit(&a, 0, sizeof(int));
    darrayInit(&b, 0, sizeof(int));

    int v = 1;
    darrayPushBack(&b, &v);

    if (darrayGetUnion(&a, &b, darrayDefaultOrdering, &out) != DARRAY_OK)
        return 1;

    if (darrayIsEmpty(out))
        return 2;

    v = 0;
    darrayGetAt(&out, 0, &v);
    if (v != 1) return 3;

    darrayDestroy(&a);
    darrayDestroy(&b);
    darrayDestroy(&out);
    return 0;
}

int get_union_both_empty() {
    Darray a, b, out;
    darrayInit(&a, 0, sizeof(int));
    darrayInit(&b, 0, sizeof(int));

    if (darrayGetUnion(&a, &b, darrayDefaultOrdering, &out) != DARRAY_OK)
        return 1;

    if (!darrayIsEmpty(out))
        return 2;

    darrayDestroy(&a);
    darrayDestroy(&b);
    darrayDestroy(&out);
    return 0;
}

int get_union_with_duplicates() {
    Darray a, b, out;
    darrayInit(&a, 0, sizeof(int));
    darrayInit(&b, 0, sizeof(int));

    int av[] = {1, 2, 2, 3, 3, 3};
    int bv[] = {2, 2, 3, 4};

    for (int i = 0; i < 6; i++)
        darrayPushBack(&a, &av[i]);
    for (int i = 0; i < 4; i++)
        darrayPushBack(&b, &bv[i]);

    if (darrayGetUnion(&a, &b, darrayDefaultOrdering, &out) != DARRAY_OK)
        return 1;

    if (darraySize(out) != 4) {
        // show(out);   
        return 2;
    }

    int expected[] = {1, 2, 3, 4};
    for (int i = 0; i < 4; i++) {
        int v;
        darrayGetAt(&out, i, &v);
        if (v != expected[i]) return 3;
    }
    darrayDestroy(&a);
    darrayDestroy(&b);
    darrayDestroy(&out);
    return 0;
}

int get_union_identical() {
    Darray a, b, out;
    darrayInit(&a, 0, sizeof(int));
    darrayInit(&b, 0, sizeof(int));

    int v[] = {1, 2, 3};

    for (int i = 0; i < 3; i++) {
        darrayPushBack(&a, &v[i]);
        darrayPushBack(&b, &v[i]);
    }

    if (darrayGetUnion(&a, &b, darrayDefaultOrdering, &out) != DARRAY_OK)
        return 1;

    if (darraySize(out) != 3)
        return 2;
        
    int expected[] = {1, 2, 3};
    for (int i = 0; i < 3; i++) {
        int v;
        darrayGetAt(&out, i, &v);
        if (v != expected[i]) return 3;
    }

    darrayDestroy(&a);
    darrayDestroy(&b);
    darrayDestroy(&out);
    return 0;
}

int get_union_null_args() {
    Darray a;
    darrayInit(&a, 0, sizeof(int));

    if (darrayGetUnion(NULL, &a, darrayDefaultOrdering, &a) != DARRAY_ERROR_NULL)
        return 1;

    if (darrayGetUnion(&a, NULL, darrayDefaultOrdering, &a) != DARRAY_ERROR_NULL)
        return 2;

    if (darrayGetUnion(&a, &a, darrayDefaultOrdering, NULL) != DARRAY_ERROR_NULL)
        return 3;

    darrayDestroy(&a);
    return 0;
}
int get_union_unsorted_input() {
    Darray a, b, out;
    darrayInit(&a, 0, sizeof(int));
    darrayInit(&b, 0, sizeof(int));

    int av[] = {3, 1, 2};  // not sorted
    int bv[] = {1, 2, 3};

    for (int i = 0; i < 3; i++) {
        darrayPushBack(&a, &av[i]);
        darrayPushBack(&b, &bv[i]);
    }

    if (darrayGetUnion(&a, &b, darrayDefaultOrdering, &out) != DARRAY_ERROR_INVALID)
        return 1;

    darrayDestroy(&a);
    darrayDestroy(&b);
    return 0;
}

int get_union_descending() {
    Darray left, right, out;
    darrayInit(&left, 0, sizeof(int));
    darrayInit(&right, 0, sizeof(int));

    int lv[] = {9, 7, 5, 3, 1};
    int rv[] = {8, 7, 6, 5, 4};

    for (int i = 0; i < 5; i++) {
        darrayPushBack(&left, &lv[i]);
        darrayPushBack(&right, &rv[i]);
    }

    if (darrayGetUnion(&left, &right, darrayDefaultOrdering, &out) != DARRAY_OK)
        return 1;

    if (darraySize(out) != 8)
        return 2;
        
    int expected[] = {9, 8, 7, 6, 5, 4, 3, 1};

    for (int i = 0; i < 8; i++) {
        int v;
        darrayGetAt(&out, i, &v);
        if (v != expected[i]) return 3;
    }

    darrayDestroy(&left);
    darrayDestroy(&right);
    darrayDestroy(&out);
    return 0;
}
