#include "../inc/vec/vec_algs.h"

int range_simple_forward()
{
    vec_t vec;
    vec_init(&vec, 0, sizeof(size_t));

    if (vec_range_from_to_step(&vec, 0, 5, 1) != VEC_OK)
        return 1;

    size_t expected[] = {0, 1, 2, 3, 4};
    if (vec_size(&vec) != 5)
        return 2;

    for (size_t i = 0; i < 5; i++)
    {
        size_t value;
        if (vec_get(&vec, i, &value) != VEC_OK)
            return 3;
        if (value != expected[i])
            return 4;
    }

    vec_destroy(&vec);
    return 0;
}

int range_forward_step_two()
{
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    if (vec_range_from_to_step(&d, 0, 10, 2) != VEC_OK)
        return 1;

    size_t expected[] = {0, 2, 4, 6, 8};
    if (vec_size(&d) != 5)
        return 2;

    for (size_t i = 0; i < 5; i++)
    {
        size_t value;
        if (vec_get(&d, i, &value) != VEC_OK)
            return 3;
        if (value != expected[i])
            return 4;
    }

    vec_destroy(&d);
    return 0;
}

int range_backward()
{
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    if (vec_range_from_to_step(&d, 5, 0, -1) != VEC_OK)
        return 1;

    size_t expected[] = {5, 4, 3, 2, 1};
    if (vec_size(&d) != 5)
        return 2;

    for (size_t i = 0; i < 5; i++)
    {
        size_t value;
        if (vec_get(&d, i, &value) != VEC_OK)
            return 3;
        if (value != expected[i])
            return 4;
    }

    vec_destroy(&d);
    return 0;
}

int range_backward_step_two()
{
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    if (vec_range_from_to_step(&d, 10, 0, -2) != VEC_OK)
        return 1;

    size_t expected[] = {10, 8, 6, 4, 2};
    if (vec_size(&d) != 5)
        return 2;

    for (size_t i = 0; i < 5; i++)
    {
        size_t value;
        if (vec_get(&d, i, &value) != VEC_OK)
            return 3;
        if (value != expected[i])
            return 4;
    }

    vec_destroy(&d);
    return 0;
}

int range_empty()
{
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    if (vec_range_from_to_step(&d, 3, 3, 1) != VEC_OK)
        return 1;
    if (vec_size(&d) != 0)
        return 2;

    vec_destroy(&d);
    return 0;
}

int range_zero_step()
{
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    if (vec_range_from_to_step(&d, 0, 5, 0) != VEC_ERROR_INVALID)
        return 1;

    vec_destroy(&d);
    return 0;
}

int range_invalid_negative_step_forward()
{
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    if (vec_range_from_to_step(&d, 0, 5, -1) != VEC_ERROR_INVALID)
        return 1;

    vec_destroy(&d);
    return 0;
}

int range_invalid_positive_step_backward()
{
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    if (vec_range_from_to_step(&d, 5, 0, 1) != VEC_ERROR_INVALID)
        return 1;

    vec_destroy(&d);
    return 0;
}

int range_stop_exclusive()
{
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    if (vec_range_from_to_step(&d, 0, 5, 3) != VEC_OK)
        return 1;

    size_t expected[] = {0, 3};
    if (vec_size(&d) != 2)
        return 2;

    for (size_t i = 0; i < 2; i++)
    {
        size_t value;
        if (vec_get(&d, i, &value) != VEC_OK)
            return 3;
        if (value != expected[i])
            return 4;
    }

    vec_destroy(&d);
    return 0;
}

int range_null_self()
{
    if (vec_range_from_to_step(NULL, 0, 5, 1) != VEC_ERROR_NULL)
        return 1;
    return 0;
}
