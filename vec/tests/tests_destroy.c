#include "../inc/vec.h"

int destroy_initialized()
{
    vec_t vec;
    vec_init(&vec, 1, sizeof(int));

    vec_destroy(&vec);

    if (vec.m_data != NULL)
        return 1;
    if (vec.capacity_allocated != 0)
        return 2;
    if (vec.size_used != 0)
        return 3;

    return 0;
}

int destroy_NULL()
{
    vec_destroy(NULL); // should not crash

    return 0;
}

int destroy_double()
{
    vec_t vec;
    vec_init(&vec, 10, sizeof(int));

    vec_destroy(&vec);

    if (vec.m_data != NULL)
        return 1;
    if (vec.capacity_allocated != 0)
        return 2;
    if (vec.size_used != 0)
        return 3;

    vec_destroy(&vec); // should not crash

    if (vec.m_data != NULL)
        return 4;
    if (vec.capacity_allocated != 0)
        return 5;
    if (vec.size_used != 0)
        return 6;

    return 0;
}