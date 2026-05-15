///
/// @file: vec_size_capacity.h
/// @description: Contains functions related to the reserved capacity or used size
///
/// @date: 2026-01-03
/// @author: Moritz Pirer
///
#include <string.h>

#include "../vec_internal.h"

VecStatus vec_reserve(vec_t *self, size_t elements_to_reserve)
{
    if (self == NULL)
    {
        return VEC_ERROR_NULL;
    }

    if (elements_to_reserve <= self->capacity_allocated)
    {
        return VEC_OK;
    }

    size_t new_size = max(self->capacity_allocated, 1);
    while (new_size < elements_to_reserve)
    {
        new_size <<= 1;
    }

    VecStatus result = internal_vecSetSizeTo(self, new_size);

    return result;
}

VecStatus vec_shrink(vec_t *self)
{
    if (self == NULL)
    {
        return VEC_ERROR_NULL;
    }

    if (self->capacity_allocated == self->size_used)
    {
        return VEC_OK;
    }

    VecStatus result = internal_vecSetSizeTo(self, self->size_used);

    return result;
}

size_t vec_size(vec_t self)
{
    return self.size_used;
}

size_t vec_capacity(vec_t self)
{
    return self.capacity_allocated;
}

bool vec_is_empty(vec_t self)
{
    return self.size_used == 0;
}

VecStatus vec_resize(vec_t *self, size_t new_size)
{
    if (self == NULL)
    {
        return VEC_ERROR_NULL;
    }

    if (new_size == self->size_used)
    {
        return VEC_OK;
    }

    size_t old_size = self->size_used;

    VecStatus resize_result = internal_vecSetSizeTo(self, new_size);
    if (resize_result != VEC_OK)
    {
        return resize_result;
    }

    // zero new memory
    if (new_size > old_size)
    {
        self->size_used = new_size;
        memset(internal_vecNThElement(self, old_size), 0, (new_size - old_size) * self->item_size);
    }

    return VEC_OK;
}