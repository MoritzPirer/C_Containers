///
/// @file: vec_algs_searching.c
/// @description: Contains functions related to searching for the index of elements
///
/// @date: 2026-01-06
/// @author: Moritz Pirer
///

#include "../vec_internal.h"
#include "../../inc/vec_algs.h"

VecStatus vec_find_first(vec_t *self, vec_condition_t condition,
                          size_t *index_buffer, const void *data)
{

    if (self == NULL || index_buffer == NULL)
    {
        return VEC_ERROR_NULL;
    }

    for (size_t index = 0; index < self->size_used; index++)
    {
        if (condition(internal_vecNThElement(self, index), data) == true)
        {
            *index_buffer = index;
            return VEC_OK;
        }
    }

    return VEC_NOT_FOUND;
}

VecStatus vec_find_last(vec_t *self, vec_condition_t condition,
                         size_t *index_buffer, const void *data)
{

    if (self == NULL || index_buffer == NULL)
    {
        return VEC_ERROR_NULL;
    }

    for (size_t i = 0; i < self->size_used; i++)
    {
        size_t index = self->size_used - i - 1; // covers some edge cases better because of underflow
        if (condition(internal_vecNThElement(self, index), data) == true)
        {
            *index_buffer = index;
            return VEC_OK;
        }
    }

    return VEC_NOT_FOUND;
}

bool vec_contains(vec_t self, vec_condition_t condition, const void *data)
{
    size_t dummy;
    return vec_find_first(&self, condition, &dummy, data) == VEC_OK;
}

VecStatus vec_binary_search(vec_t *self, vec_ordering_t vector_ordering,
                             size_t *index_buffer, const void *key)
{

    if (self == NULL || index_buffer == NULL || key == NULL)
    {
        return VEC_ERROR_NULL;
    }

    if (self->size_used == 0)
    {
        return VEC_NOT_FOUND;
    }

    size_t left = 0;
    size_t right = self->size_used - 1;

    while (left <= right)
    {
        size_t middle = (left + right) / 2;

        int ordering = vector_ordering(&middle, key);

        if (ordering == 0)
        {
            *index_buffer = middle;
            return VEC_OK;
        }

        if (ordering < 0)
        {
            left = middle + 1;
            continue;
        }

        if (ordering > 0)
        {
            right = middle - 1;
            continue;
        }
    }

    return VEC_NOT_FOUND;
}