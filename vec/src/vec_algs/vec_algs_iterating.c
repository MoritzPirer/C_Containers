///
/// @file: vec_algs_iterating.c
/// @description: Contains functions related to doing something to each element in the vec
///
/// @date: 2026-01-10
/// @author: Moritz Pirer
///

#include <string.h>
#include <assert.h>

#include "../vec_internal.h"
#include "../../inc/vec_algs.h"

bool vec_any(vec_t self, vec_condition_t condition, const void *data)
{
    for (size_t index = 0; index < self.size_used; index++)
    {
        if (condition(internal_vecNThElement(&self, index), data) == true)
        {
            return true;
        }
    }

    return false;
}

bool vec_all(vec_t self, vec_condition_t condition, const void *data)
{
    for (size_t index = 0; index < self.size_used; index++)
    {
        if (condition(internal_vecNThElement(&self, index), data) == false)
        {
            return false;
        }
    }

    return true;
}

bool vec_none(vec_t self, vec_condition_t condition, const void *data)
{
    for (size_t index = 0; index < self.size_used; index++)
    {
        if (condition(internal_vecNThElement(&self, index), data) == true)
        {
            return false;
        }
    }

    return true;
}

void vec_reverse(vec_t *self)
{
    for (size_t index = 0; index < self->size_used / 2; index++)
    {
        size_t swap_index = self->size_used - index - 1;
        char buffer[self->item_size];
        memcpy(buffer, internal_vecNThElement(self, index), self->item_size);
        memcpy(
            internal_vecNThElement(self, index),
            internal_vecNThElement(self, swap_index),
            self->item_size);
        memcpy(internal_vecNThElement(self, swap_index), buffer, self->size_used);
    }
}

VecStatus vec_filter(vec_t *self, vec_condition_t condition,
                     vec_t *filtered, const void *data)
{
    if (self == NULL || filtered == NULL)
    {
        return VEC_ERROR_NULL;
    }

    if (vec_init(filtered, 0, sizeof(size_t)) != VEC_OK)
    {
        return VEC_ERROR_ALLOCATION;
    }

    if (vec_reserve(filtered, self->size_used) != VEC_OK)
    {
        return VEC_ERROR_ALLOCATION;
    }

    for (size_t index = 0; index < self->size_used; index++)
    {
        if (condition(internal_vecNThElement(self, index), data) == false)
        {
            continue;
        }

        VecStatus result = vec_push_back(filtered, internal_vecNThElement(self, index));
        if (result != VEC_OK)
        {
            return result;
        }
    }

    return vec_shrink(filtered);
}

VecStatus vec_transform(vec_t *self, vec_transformation_t transfomration, const void *data)
{
    if (self == NULL)
    {
        return VEC_ERROR_NULL;
    }

    for (size_t index = 0; index < self->size_used; index++)
    {
        transfomration(internal_vecNThElement(self, index), data);
    }

    return VEC_OK;
}