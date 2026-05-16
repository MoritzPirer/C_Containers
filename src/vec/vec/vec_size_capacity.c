///
/// @file: vec_size_capacity.h
/// @description: Contains functions related to the reserved capacity or used size
///
/// @date: 2026-01-03
/// @author: Moritz Pirer
///
#include <string.h>

#include "../vec_internal.h"

vec_status_t vec_reserve(vec_t* self, size_t elements_to_reserve) {
    if (self == NULL) {
        return VEC_ERROR_NULL;
    }

    if (elements_to_reserve <= self->capacity_allocated) {
        return VEC_OK;
    }

    size_t new_size = max(self->capacity_allocated, 1);
    while (new_size < elements_to_reserve) {
        new_size <<= 1;
    }

    vec_status_t result = internal_vecSetSizeTo(self, new_size);

    return result;
}

vec_status_t vec_shrink(vec_t* self) {
    if (self == NULL) {
        return VEC_ERROR_NULL;
    }

    if (self->capacity_allocated == self->size_used) {
        return VEC_OK;
    }

    vec_status_t result = internal_vecSetSizeTo(self, self->size_used);

    return result;
}

size_t vec_size(vec_t* self) {
    if (self == NULL) {
        return (size_t) -1;
    }

    return self->size_used;
}

size_t vec_capacity(vec_t* self) {
    if (self == NULL) {
        return (size_t) -1;
    }

    return self->capacity_allocated;
}

bool vec_is_empty(vec_t* self) {
    if (self == NULL) {
        return true;
    }
    return self->size_used == 0;
}

vec_status_t vec_resize(vec_t* self, size_t new_size) {
    if (self == NULL) {
        return VEC_ERROR_NULL;
    }

    if (new_size == self->size_used) {
        return VEC_OK;
    }

    size_t old_size = self->size_used;

    vec_status_t resize_result = internal_vecSetSizeTo(self, new_size);
    if (resize_result != VEC_OK) {
        return resize_result;
    }

    // zero new memory
    if (new_size > old_size) {
        self->size_used = new_size;
        memset(internal_vecNThElement(self, old_size), 0, (new_size - old_size) * self->item_size);
    }

    return VEC_OK;
}