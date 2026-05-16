#include "../inc/vec/vec_algs.h"

int is_unique_simple()
{
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    for (size_t i = 0; i < 10; i++)
    {
        vec_push_back(&d, &i);
    }

    if (!vec_is_unique(d, vec_default_ordering))
        return 1;

    vec_destroy(&d);
    return 0;
}

int is_unique_false()
{

    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    for (size_t i = 0; i < 10; i++)
    {
        vec_push_back(&d, &i);
    }
    size_t i = 9;
    vec_push_back(&d, &i);

    if (vec_is_unique(d, vec_default_ordering))
        return 1;

    vec_destroy(&d);
    return 0;
}

int is_unique_empty()
{
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    if (!vec_is_unique(d, vec_default_ordering))
        return 1;

    vec_destroy(&d);
    return 0;
}

int is_unique_all_same()
{
    vec_t d;
    vec_init(&d, 0, sizeof(int));

    int a = 10;
    for (int i = 0; i < 10; i++)
    {
        vec_push_back(&d, &a);
    }

    if (vec_is_unique(d, vec_default_ordering))
        return 1;

    vec_destroy(&d);
    return 0;
}

int get_unique_simple()
{
    vec_t d;
    vec_init(&d, 0, sizeof(int));

    for (int i = 0; i < 20; i++)
    {
        if (i % 2 == 1)
            i++;
        vec_push_back(&d, &i);
    }

    vec_t e;
    if (vec_get_unique(&d, vec_default_ordering, &e) != VEC_OK)
        return 1;

    if (!vec_is_unique(e, vec_default_ordering))
        return 2;

    vec_destroy(&d);
    vec_destroy(&e);
    return 0;
}

int get_unique_all_same()
{
    vec_t d;
    vec_init(&d, 0, sizeof(int));

    int a = 10;
    for (int i = 0; i < 10; i++)
    {
        vec_push_back(&d, &a);
    }

    vec_t e;
    if (vec_get_unique(&d, vec_default_ordering, &e) != VEC_OK)
        return 1;

    if (!vec_is_unique(e, vec_default_ordering))
        return 2;

    vec_destroy(&d);
    vec_destroy(&e);
    return 0;
}

int get_unique_already_unique()
{
    vec_t d;
    vec_init(&d, 0, sizeof(int));

    for (int i = 0; i < 10; i++)
    {
        vec_push_back(&d, &i);
    }

    vec_t e;
    if (vec_get_unique(&d, vec_default_ordering, &e) != VEC_OK)
        return 1;

    if (!vec_is_unique(e, vec_default_ordering))
        return 2;

    vec_destroy(&d);
    vec_destroy(&e);
    return 0;
}
