#include "../inc/darrayAlgs.h"

int get_intersection_basic() {
    Darray a, b, out;
    darrayInit(&a, 0, sizeof(int));
    darrayInit(&b, 0, sizeof(int));

    int av[] = {1, 2, 3, 4, 5};
    int bv[] = {3, 4, 5, 6, 7};

    for (int i = 0; i < 5; i++) {
        darrayPushBack(&a, &av[i]);
        darrayPushBack(&b, &bv[i]);
    }

    if (darrayGetIntersection(&a, &b, darrayDefaultOrdering, &out) != DARRAY_OK)
        return 1;

    if (darraySize(out) != 3)
        return 2;

    int expected[] = {3, 4, 5};
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

int get_intersection_none() {
    Darray a, b, out;
    darrayInit(&a, 0, sizeof(int));
    darrayInit(&b, 0, sizeof(int));

    int av[] = {1, 2, 3};
    int bv[] = {4, 5, 6};

    for (int i = 0; i < 3; i++) {
        darrayPushBack(&a, &av[i]);
        darrayPushBack(&b, &bv[i]);
    }

    if (darrayGetIntersection(&a, &b, darrayDefaultOrdering, &out) != DARRAY_OK)
        return 1;

    if (!darrayIsEmpty(out))
        return 2;

    darrayDestroy(&a);
    darrayDestroy(&b);
    darrayDestroy(&out);
    return 0;
}

int get_intersection_left_empty() {
    Darray a, b, out;
    darrayInit(&a, 0, sizeof(int));
    darrayInit(&b, 0, sizeof(int));

    int v = 1;
    darrayPushBack(&b, &v);

    if (darrayGetIntersection(&a, &b, darrayDefaultOrdering, &out) != DARRAY_OK)
        return 1;

    if (!darrayIsEmpty(out))
        return 2;

    darrayDestroy(&a);
    darrayDestroy(&b);
    darrayDestroy(&out);
    return 0;
}

int get_intersection_both_empty() {
    Darray a, b, out;
    darrayInit(&a, 0, sizeof(int));
    darrayInit(&b, 0, sizeof(int));

    if (darrayGetIntersection(&a, &b, darrayDefaultOrdering, &out) != DARRAY_OK)
        return 1;

    if (!darrayIsEmpty(out))
        return 2;

    darrayDestroy(&a);
    darrayDestroy(&b);
    darrayDestroy(&out);
    return 0;
}

int get_intersection_with_duplicates() {
    Darray a, b, out;
    darrayInit(&a, 0, sizeof(int));
    darrayInit(&b, 0, sizeof(int));

    int av[] = {1, 2, 2, 3, 3, 3};
    int bv[] = {2, 2, 3, 4};

    for (int i = 0; i < 6; i++)
        darrayPushBack(&a, &av[i]);
    for (int i = 0; i < 4; i++)
        darrayPushBack(&b, &bv[i]);

    if (darrayGetIntersection(&a, &b, darrayDefaultOrdering, &out) != DARRAY_OK)
        return 1;

    if (darraySize(out) != 2)
        return 2;

    int e0, e1;
    darrayGetAt(&out, 0, &e0);
    darrayGetAt(&out, 1, &e1);

    if (e0 != 2 || e1 != 3)
        return 3;

    darrayDestroy(&a);
    darrayDestroy(&b);
    darrayDestroy(&out);
    return 0;
}

int get_intersection_identical() {
    Darray a, b, out;
    darrayInit(&a, 0, sizeof(int));
    darrayInit(&b, 0, sizeof(int));

    int v[] = {1, 2, 3};

    for (int i = 0; i < 3; i++) {
        darrayPushBack(&a, &v[i]);
        darrayPushBack(&b, &v[i]);
    }

    if (darrayGetIntersection(&a, &b, darrayDefaultOrdering, &out) != DARRAY_OK)
        return 1;

    if (darraySize(out) != 3)
        return 2;

    darrayDestroy(&a);
    darrayDestroy(&b);
    darrayDestroy(&out);
    return 0;
}

int get_intersection_null_args() {
    Darray a;
    darrayInit(&a, 0, sizeof(int));

    if (darrayGetIntersection(NULL, &a, darrayDefaultOrdering, &a) != DARRAY_ERROR_NULL)
        return 1;

    if (darrayGetIntersection(&a, NULL, darrayDefaultOrdering, &a) != DARRAY_ERROR_NULL)
        return 2;

    if (darrayGetIntersection(&a, &a, darrayDefaultOrdering, NULL) != DARRAY_ERROR_NULL)
        return 3;

    darrayDestroy(&a);
    return 0;
}
int get_intersection_unsorted_input() {
    Darray a, b, out;
    darrayInit(&a, 0, sizeof(int));
    darrayInit(&b, 0, sizeof(int));

    int av[] = {3, 1, 2};  // not sorted
    int bv[] = {1, 2, 3};

    for (int i = 0; i < 3; i++) {
        darrayPushBack(&a, &av[i]);
        darrayPushBack(&b, &bv[i]);
    }

    if (darrayGetIntersection(&a, &b, darrayDefaultOrdering, &out) != DARRAY_ERROR_INVALID)
        return 1;

    darrayDestroy(&a);
    darrayDestroy(&b);
    return 0;
}

int get_intersection_descending() {
    Darray left, right, out;
    darrayInit(&left, 0, sizeof(int));
    darrayInit(&right, 0, sizeof(int));

    int lv[] = {9, 7, 5, 3, 1};
    int rv[] = {8, 7, 6, 5, 4};

    for (int i = 0; i < 5; i++) {
        darrayPushBack(&left, &lv[i]);
        darrayPushBack(&right, &rv[i]);
    }

    if (darrayGetIntersection(&left, &right, darrayDefaultOrdering, &out) != DARRAY_OK)
        return 1;

    if (darraySize(out) != 2)
        return 2;

    int v0, v1;
    darrayGetAt(&out, 0, &v0);
    darrayGetAt(&out, 1, &v1);

    if (v0 != 7 || v1 != 5)
        return 3;

    darrayDestroy(&left);
    darrayDestroy(&right);
    darrayDestroy(&out);
    return 0;
}
