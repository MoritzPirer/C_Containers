///
/// @file: vec_access.h
/// @description: Contains functions related to accessing elements of a vec_t
///
/// @date: 2026-01-03
/// @author: Moritz Pirer
///
#include <string.h>

#include "../vec_internal.h"

vec_status_t vec_get(const vec_t* self, size_t index, void *buffer) {
    if (self == NULL || buffer == NULL) {
        return VEC_ERROR_NULL;
    }

    if (!internal_vecIsValidIndex(self, index)) {
        return VEC_ERROR_BOUNDS;
    }

    memcpy(buffer, internal_vecNThElement(self, index), self->item_size);

    return VEC_OK;
}

vec_status_t vec_set(vec_t* self, size_t index, const void *buffer) {
    if (self == NULL) {
        return VEC_ERROR_NULL;
    }

    if (!internal_vecIsValidIndex(self, index)) {
        return VEC_ERROR_BOUNDS;
    }

    memcpy(internal_vecNThElement(self, index), buffer, self->item_size);

    return VEC_OK;
}

void *vec_data(vec_t* self) {
    if (self == NULL) {
        return NULL;
    }

    return self->array;
}
