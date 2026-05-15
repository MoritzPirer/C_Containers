///
/// @file: vec_access.h
/// @description: Contains functions related to accessing elements of a vec_t
///
/// @date: 2026-01-03
/// @author: Moritz Pirer
///
#include <string.h>

#include "../vec_internal.h"

VecStatus vec_get(vec_t *self, size_t index, void *buffer)
{
    if (self == NULL || buffer == NULL)
    {
        return VEC_ERROR_NULL;
    }

    if (!internal_vecIsValidIndex(self, index))
    {
        return VEC_ERROR_BOUNDS;
    }

    memcpy(buffer, internal_vecNThElement(self, index), self->item_size);

    return VEC_OK;
}

VecStatus vec_set(vec_t *self, size_t index, const void *buffer)
{
    if (self == NULL)
    {
        return VEC_ERROR_NULL;
    }

    if (!internal_vecIsValidIndex(self, index))
    {
        return VEC_ERROR_BOUNDS;
    }

    memcpy(internal_vecNThElement(self, index), buffer, self->item_size);

    return VEC_OK;
}

void *vec_data(vec_t *self)
{
    if (self == NULL)
    {
        return NULL;
    }

    return self->m_data;
}
