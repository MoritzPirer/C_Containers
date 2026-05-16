#include "../inc/vec/vec_algs.h"


int find_first_one_option()
{
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    for (size_t i = 0; i < 10; i++)
    {
        vec_push_back(&d, &i);
    }
    size_t temp;
    size_t target = 2;
    vec_status_t res = vec_find_first(&d, vec_default_condition, &temp, &target);
    if (res != VEC_OK)
        return 1;
    if (temp != 2)
        return 2;

    vec_destroy(&d);
    return 0;
}

int find_first_two_options()
{
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    for (size_t i = 0; i < 10; i++)
    {
        vec_push_back(&d, &i);
    }
    size_t temp = 2;
    vec_push_back(&d, &temp);

    size_t target = 2;
    vec_status_t res = vec_find_first(&d, vec_default_condition, &temp, &target);
    if (res != VEC_OK)
        return 1;
    if (temp != 2)
        return 2;

    vec_destroy(&d);
    return 0;
}

int find_first_no_option()
{
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    for (size_t i = 0; i < 10; i++)
    {
        vec_push_back(&d, &i);
    }
    size_t temp;

    size_t target = 15;
    vec_status_t res = vec_find_first(&d, vec_default_condition, &temp, &target);
    if (res != VEC_NOT_FOUND)
        return 1;

    vec_destroy(&d);
    return 0;
}

int find_last_one_option()
{
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    for (size_t i = 0; i < 10; i++)
    {
        vec_push_back(&d, &i);
    }
    size_t temp;
    size_t target = 2;
    vec_status_t res = vec_find_last(&d, vec_default_condition, &temp, &target);
    if (res != VEC_OK)
        return 1;
    if (temp != 2)
        return 2;

    vec_destroy(&d);
    return 0;
}

int find_last_two_options()
{
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    for (size_t i = 0; i < 10; i++)
    {
        vec_push_back(&d, &i);
    }
    size_t temp = 2;
    vec_push_back(&d, &temp);

    size_t target = 2;
    vec_status_t res = vec_find_last(&d, vec_default_condition, &temp, &target);
    if (res != VEC_OK)
        return 1;
    if (temp != 10)
        return 2;

    vec_destroy(&d);
    return 0;
}

int find_last_no_option()
{
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    for (size_t i = 0; i < 10; i++)
    {
        vec_push_back(&d, &i);
    }
    size_t temp;

    size_t target = 15;
    vec_status_t res = vec_find_last(&d, vec_default_condition, &temp, &target);
    if (res != VEC_NOT_FOUND)
        return 1;

    vec_destroy(&d);
    return 0;
}

int find_first_last_empty()
{
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));
    size_t temp = 1;
    if (vec_find_first(&d, vec_default_condition, &temp, &temp) != VEC_NOT_FOUND)
        return 1;
    if (vec_find_last(&d, vec_default_condition, &temp, &temp) != VEC_NOT_FOUND)
        return 2;

    return 0;
}

int binary_search_simple()
{
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    for (size_t i = 0; i < 10; i++)
    {
        vec_push_back(&d, &i);
    }
    size_t temp;
    size_t target = 2;
    vec_status_t res = vec_binary_search(&d, vec_default_ordering, &temp, &target);
    if (res != VEC_OK)
        return 1;
    if (temp != 2)
        return 2;

    vec_destroy(&d);
    return 0;
}

int binary_search_empty()
{
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    size_t temp;
    size_t target = 2;
    vec_status_t res = vec_binary_search(&d, vec_default_ordering, &temp, &target);
    if (res != VEC_NOT_FOUND)
        return 1;

    vec_destroy(&d);
    return 0;
}

int binary_search_small()
{
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    for (size_t i = 0; i < 3; i++)
    {
        vec_push_back(&d, &i);
    }

    size_t temp;
    size_t target = 2;
    vec_status_t res = vec_binary_search(&d, vec_default_ordering, &temp, &target);
    if (res != VEC_OK)
        return 1;
    if (temp != 2)
        return 2;

    vec_destroy(&d);
    return 0;
}