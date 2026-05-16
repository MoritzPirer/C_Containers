///
/// @file: vec_erase.c
/// @description: Contains functions related to erasing elements from a vec
///
/// @date: 2026-01-03
/// @author: Moritz Pirer
///

#include <string.h>

#include "../vec_internal.h"

vec_status_t vec_erase_from_to(vec_t* self, size_t start, size_t end) {
    if (self == NULL) {
        return VEC_ERROR_NULL;
    }

    if (!internal_vecIsValidIndex(self, start)) {
        return VEC_ERROR_BOUNDS;
    }

    if (!internal_vecIsValidIndex(self, end)) {
        return VEC_ERROR_BOUNDS;
    }

    if (end < start) {
        return VEC_ERROR_BOUNDS;
    }

    size_t num_elements_behind_erase = self->size_used - end;
    if (num_elements_behind_erase > 0) { // if erase is at end, no overwrite is needed
        size_t bytes_to_copy = num_elements_behind_erase * self->item_size;
        internal_moveBytes(self, end + 1, start, bytes_to_copy);
    }

    self->size_used -= (end - start + 1);

    vec_status_t result = internal_vecShrinkIfNeeded(self);

    return result;
}

vec_status_t vec_erase_from(vec_t* self, size_t start) {
    if (self == NULL) {
        return VEC_ERROR_NULL;
    }
    // synchronization in vec_erase_from_to
    return vec_erase_from_to(self, start, self->size_used - 1);
}

vec_status_t vec_erase_to(vec_t* self, size_t end) {
    // synchronization in vec_erase_from_to
    return vec_erase_from_to(self, 0, end);
}

vec_status_t vec_erase_at(vec_t* self, size_t index) {
    // synchronization in vec_erase_from_to
    return vec_erase_from_to(self, index, index);
}

vec_status_t vec_erase_all(vec_t* self) {
    if (self == NULL) {
        return VEC_ERROR_NULL;
    }

    // synchronization in vec_erase_from_to
    return vec_erase_from_to(self, 0, self->size_used - 1);
}

vec_status_t vec_clear(vec_t* self) {
    // synchronization in vec_erase_from_to
    return vec_erase_all(self);
}