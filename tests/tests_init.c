#include "../inc/vec/vec_algs.h"

int init_elementSize_0()
{
    vec_t d;
    vec_status_t res = vec_init(&d, 1, 0);

    if (res != VEC_ERROR_INVALID)
        return 1;

    return 0;
}

int init_NULL()
{
    vec_status_t res = vec_init(NULL, 1, 1);

    if (res != VEC_ERROR_NULL)
        return 1;

    return 0;
}

int init_size_0()
{
    vec_t d;
    vec_init(&d, 0, sizeof(int));

    if (d.item_size != sizeof(int))
        return 1;
    if (d.capacity_allocated != VEC_MIN_SIZE)
        return 2;
    if (d.size_used != 0)
        return 3;

    return 0;
}

int init_size_1()
{
    vec_t d;
    vec_init(&d, 1, sizeof(int));

    if (d.item_size != sizeof(int))
        return 1;
    if (d.capacity_allocated != VEC_MIN_SIZE)
        return 2;
    if (d.size_used != 1)
        return 3;

    return 0;
}

int init_size_pow2()
{
    vec_t d;
    size_t size = 2 * 2 * 2 * 2 * 2 * 2;
    vec_init(&d, size, sizeof(int));

    if (d.item_size != sizeof(int))
        return 1;
    if (d.capacity_allocated != size)
        return 2;
    if (d.size_used != size)
        return 3;

    return 0;
}

int init_size_XL()
{
    vec_t d;
    size_t size = 10000000;
    vec_init(&d, size, sizeof(int));

    if (d.item_size != sizeof(int))
        return 1;
    if (d.capacity_allocated < size)
        return 2;
    if (d.size_used != size)
        return 3;

    return 0;
}

int init_size_XXXL()
{
    vec_t d;
    size_t size = (size_t)-1;
    vec_status_t res = vec_init(&d, size, sizeof(int));

    if (res == VEC_OK && d.m_data == NULL)
        return 1;

    return 0;
}