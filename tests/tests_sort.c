#include "../inc/vec/vec_algs.h"

int sort_empty()
{
    vec_t d;
    vec_init(&d, 0, sizeof(int));

    if (vec_sort(&d, vec_default_ordering) != VEC_OK)
        return 1;
    if (!vec_is_sorted_asc(d, vec_default_ordering))
        return 2;

    vec_destroy(&d);
    return 0;
}

int sort_single()
{
    vec_t d;
    vec_init(&d, 0, sizeof(int));

    int x = 42;
    vec_push_back(&d, &x);

    if (vec_sort(&d, vec_default_ordering) != VEC_OK)
        return 1;
    if (!vec_is_sorted_asc(d, vec_default_ordering))
        return 2;

    vec_destroy(&d);
    return 0;
}

int sort_already_sorted()
{
    vec_t d;
    vec_init(&d, 0, sizeof(int));

    for (int i = 0; i < 10; i++)
    {
        vec_push_back(&d, &i);
    }

    if (vec_sort(&d, vec_default_ordering) != VEC_OK)
        return 1;
    if (!vec_is_sorted_asc(d, vec_default_ordering))
        return 2;

    vec_destroy(&d);
    return 0;
}

int sort_reverse()
{
    vec_t d;
    vec_init(&d, 0, sizeof(int));

    for (int i = 9; i >= 0; i--)
    {
        vec_push_back(&d, &i);
    }

    if (vec_sort(&d, vec_default_ordering) != VEC_OK)
        return 1;
    if (!vec_is_sorted_asc(d, vec_default_ordering))
        return 2;

    vec_destroy(&d);
    return 0;
}

int sort_with_duplicates()
{
    vec_t d;
    vec_init(&d, 0, sizeof(int));

    int values[] = {3, 1, 2, 3, 2, 1, 3};
    for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); i++)
    {
        vec_push_back(&d, &values[i]);
    }

    if (vec_sort(&d, vec_default_ordering) != VEC_OK)
        return 1;
    if (!vec_is_sorted_asc(d, vec_default_ordering))
        return 2;

    vec_destroy(&d);
    return 0;
}

int sort_random_small()
{
    vec_t d;
    vec_init(&d, 0, sizeof(int));

    int values[] = {4, 2, 9, 1, 5};
    for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); i++)
    {
        vec_push_back(&d, &values[i]);
    }

    if (vec_sort(&d, vec_default_ordering) != VEC_OK)
        return 1;
    if (!vec_is_sorted_asc(d, vec_default_ordering))
        return 2;

    vec_destroy(&d);
    return 0;
}

int sort_all_equal()
{
    vec_t d;
    vec_init(&d, 0, sizeof(int));

    int x = 7;
    for (int i = 0; i < 10; i++)
    {
        vec_push_back(&d, &x);
    }

    if (vec_sort(&d, vec_default_ordering) != VEC_OK)
        return 1;
    if (!vec_is_sorted_asc(d, vec_default_ordering))
        return 2;

    vec_destroy(&d);
    return 0;
}
