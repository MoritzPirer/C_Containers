///
/// @file: vec_structure.h
/// @description: Contains functions related to mutating the structure of a vec
///
/// @date: 2026-01-03
/// @author: Moritz Pirer
///

#include <stdio.h>
#include <string.h>

#include "../vec_internal.h"

VecStatus vec_push_back(vec_t *self, void *element)
{
    if (self == NULL || element == NULL)
    {
        return VEC_ERROR_NULL;
    }

    VecStatus grow_result = internal_vecGrow(self);
    if (grow_result != VEC_OK)
    {
        return grow_result;
    }
    memcpy(internal_vecNThElement(self, self->size_used), element, self->item_size);

    self->size_used++;

    return VEC_OK;
}

VecStatus vec_pop_back(vec_t *self, void *element)
{
    if (self == NULL || element == NULL)
    {
        return VEC_ERROR_NULL;
    }

    if (self->size_used == 0)
    {
        return VEC_ERROR_BOUNDS;
    }

    memcpy(element, internal_vecNThElement(self, self->size_used - 1), self->item_size);

    self->size_used--;

    VecStatus result = internal_vecShrinkIfNeeded(self);

    return result;
}

VecStatus vec_push_front(vec_t *self, void *element)
{
    return vec_insert(self, 0, element);
}

VecStatus vec_pop_front(vec_t *self, void *element)
{
    if (self == NULL || element == NULL)
    {
        return VEC_ERROR_NULL;
    }

    if (self->size_used == 0)
    {
        return VEC_ERROR_BOUNDS;
    }

    memcpy(element, self->m_data, self->item_size);
    self->size_used--;

    if (self->size_used == 0)
    { // only element removed -> no need to move over others
        return VEC_OK;
    }

    size_t bytes_to_copy = self->size_used * self->item_size;
    internal_moveBytes(self, 1, 0, bytes_to_copy);

    VecStatus result = internal_vecShrinkIfNeeded(self);

    return result;
}

VecStatus vec_insert(vec_t *self, size_t index, void *element)
{
    if (self == NULL)
    {
        return VEC_ERROR_NULL;
    }

    if (!internal_vecIsValidIndex(self, index))
    {
        return VEC_ERROR_BOUNDS;
    }

    VecStatus grow_result = internal_vecGrow(self);
    if (grow_result != VEC_OK)
    {
        return grow_result;
    }

    size_t num_elements_behind_insert = self->size_used - index;

    size_t bytes_to_copy = num_elements_behind_insert * self->item_size;
    internal_moveBytes(self, index, index + 1, bytes_to_copy);

    memcpy(internal_vecNThElement(self, index), element, self->item_size);

    self->size_used++;

    return VEC_OK;
}