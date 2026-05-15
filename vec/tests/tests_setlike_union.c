#include "../inc/vec_algs.h"

int get_union_basic()
{
    vec_t a, b, out;
    vec_init(&a, 0, sizeof(int));
    vec_init(&b, 0, sizeof(int));

    int av[] = {1, 2, 3, 4, 5};
    int bv[] = {3, 4, 5, 6, 7};

    for (int i = 0; i < 5; i++)
    {
        vec_push_back(&a, &av[i]);
        vec_push_back(&b, &bv[i]);
    }

    if (vec_get_union(&a, &b, vec_default_ordering, &out) != VEC_OK)
        return 1;

    if (vec_size(out) != 7)
        return 2;

    int expected[] = {1, 2, 3, 4, 5, 6, 7};
    for (int i = 0; i < 7; i++)
    {
        int v;
        vec_get(&out, i, &v);
        if (v != expected[i])
            return 3;
    }

    vec_destroy(&a);
    vec_destroy(&b);
    vec_destroy(&out);
    return 0;
}

int get_union_left_empty()
{
    vec_t a, b, out;
    vec_init(&a, 0, sizeof(int));
    vec_init(&b, 0, sizeof(int));

    int v = 1;
    vec_push_back(&b, &v);

    if (vec_get_union(&a, &b, vec_default_ordering, &out) != VEC_OK)
        return 1;

    if (vec_is_empty(out))
        return 2;

    v = 0;
    vec_get(&out, 0, &v);
    if (v != 1)
        return 3;

    vec_destroy(&a);
    vec_destroy(&b);
    vec_destroy(&out);
    return 0;
}

int get_union_both_empty()
{
    vec_t a, b, out;
    vec_init(&a, 0, sizeof(int));
    vec_init(&b, 0, sizeof(int));

    if (vec_get_union(&a, &b, vec_default_ordering, &out) != VEC_OK)
        return 1;

    if (!vec_is_empty(out))
        return 2;

    vec_destroy(&a);
    vec_destroy(&b);
    vec_destroy(&out);
    return 0;
}

int get_union_with_duplicates()
{
    vec_t a, b, out;
    vec_init(&a, 0, sizeof(int));
    vec_init(&b, 0, sizeof(int));

    int av[] = {1, 2, 2, 3, 3, 3};
    int bv[] = {2, 2, 3, 4};

    for (int i = 0; i < 6; i++)
        vec_push_back(&a, &av[i]);
    for (int i = 0; i < 4; i++)
        vec_push_back(&b, &bv[i]);

    if (vec_get_union(&a, &b, vec_default_ordering, &out) != VEC_OK)
        return 1;

    if (vec_size(out) != 4)
    {
        // show(out);
        return 2;
    }

    int expected[] = {1, 2, 3, 4};
    for (int i = 0; i < 4; i++)
    {
        int v;
        vec_get(&out, i, &v);
        if (v != expected[i])
            return 3;
    }
    vec_destroy(&a);
    vec_destroy(&b);
    vec_destroy(&out);
    return 0;
}

int get_union_identical()
{
    vec_t a, b, out;
    vec_init(&a, 0, sizeof(int));
    vec_init(&b, 0, sizeof(int));

    int v[] = {1, 2, 3};

    for (int i = 0; i < 3; i++)
    {
        vec_push_back(&a, &v[i]);
        vec_push_back(&b, &v[i]);
    }

    if (vec_get_union(&a, &b, vec_default_ordering, &out) != VEC_OK)
        return 1;

    if (vec_size(out) != 3)
        return 2;

    int expected[] = {1, 2, 3};
    for (int i = 0; i < 3; i++)
    {
        int v;
        vec_get(&out, i, &v);
        if (v != expected[i])
            return 3;
    }

    vec_destroy(&a);
    vec_destroy(&b);
    vec_destroy(&out);
    return 0;
}

int get_union_null_args()
{
    vec_t a;
    vec_init(&a, 0, sizeof(int));

    if (vec_get_union(NULL, &a, vec_default_ordering, &a) != VEC_ERROR_NULL)
        return 1;

    if (vec_get_union(&a, NULL, vec_default_ordering, &a) != VEC_ERROR_NULL)
        return 2;

    if (vec_get_union(&a, &a, vec_default_ordering, NULL) != VEC_ERROR_NULL)
        return 3;

    vec_destroy(&a);
    return 0;
}
int get_union_unsorted_input()
{
    vec_t a, b, out;
    vec_init(&a, 0, sizeof(int));
    vec_init(&b, 0, sizeof(int));

    int av[] = {3, 1, 2}; // not sorted
    int bv[] = {1, 2, 3};

    for (int i = 0; i < 3; i++)
    {
        vec_push_back(&a, &av[i]);
        vec_push_back(&b, &bv[i]);
    }

    if (vec_get_union(&a, &b, vec_default_ordering, &out) != VEC_ERROR_INVALID)
        return 1;

    vec_destroy(&a);
    vec_destroy(&b);
    return 0;
}

int get_union_descending()
{
    vec_t left, right, out;
    vec_init(&left, 0, sizeof(int));
    vec_init(&right, 0, sizeof(int));

    int lv[] = {9, 7, 5, 3, 1};
    int rv[] = {8, 7, 6, 5, 4};

    for (int i = 0; i < 5; i++)
    {
        vec_push_back(&left, &lv[i]);
        vec_push_back(&right, &rv[i]);
    }

    if (vec_get_union(&left, &right, vec_default_ordering, &out) != VEC_OK)
        return 1;

    if (vec_size(out) != 8)
        return 2;

    int expected[] = {9, 8, 7, 6, 5, 4, 3, 1};

    for (int i = 0; i < 8; i++)
    {
        int v;
        vec_get(&out, i, &v);
        if (v != expected[i])
            return 3;
    }

    vec_destroy(&left);
    vec_destroy(&right);
    vec_destroy(&out);
    return 0;
}
