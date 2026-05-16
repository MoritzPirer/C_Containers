///
/// @file: vec_ownership.h
/// @description: Contains functions related to obtaining, owning and transferring
///     ownership of memory. If it would be a constructor / destructor in C++, it belongs here.
///
/// @date: 2025-12-31
/// @author: Moritz Pirer
///

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../vec_internal.h"

vec_status_t vec_init(vec_t *self, size_t initial_size, size_t element_size) {
    if (self == NULL) {
        return VEC_ERROR_NULL;
    }

    if (element_size == 0) {
        return VEC_ERROR_INVALID;
    }

    self->size_used = initial_size;
    self->capacity_allocated = max(initial_size, VEC_MIN_SIZE);
    self->item_size = element_size;
    self->m_data = calloc(self->capacity_allocated, element_size);

    if (self->m_data == NULL) {
        return VEC_ERROR_ALLOCATION;
    }

    return VEC_OK;
}

vec_status_t vec_destroy(vec_t *self) {
    if (self == NULL) {
        return VEC_ERROR_NULL;
    }

    free(self->m_data);
    self->m_data = NULL;
    self->capacity_allocated = 0;
    self->size_used = 0;

    return VEC_OK;
}

vec_status_t vec_swap(vec_t *self, vec_t *other) {
    if (self == NULL || other == NULL) {
        return VEC_ERROR_NULL;
    }

    if (self == other) {
        return VEC_OK; // swap with self
    }

    swapValues(&(self->item_size), &(other->item_size));
    swapValues(&(self->capacity_allocated), &(other->capacity_allocated));
    swapValues(&(self->size_used), &(other->size_used));

    void *temp = self->m_data;
    self->m_data = other->m_data;
    other->m_data = temp;

    return VEC_OK;
}

vec_status_t vec_copy(vec_t *original, vec_t *copy) {
    if (original == NULL || copy == NULL) {
        return VEC_ERROR_NULL;
    }

    size_t data_amount_bytes = original->capacity_allocated * original->item_size;

    copy->m_data = malloc(data_amount_bytes);
    if (copy->m_data == NULL) {
        return VEC_ERROR_ALLOCATION;
    }

    memcpy(copy->m_data, original->m_data, data_amount_bytes);

    copy->size_used = original->size_used;
    copy->capacity_allocated = original->size_used;
    copy->item_size = original->item_size;

    return VEC_OK;
}

vec_status_t vec_append(vec_t *self, vec_t *other) {
    if (self == NULL || other == NULL) {
        return VEC_ERROR_NULL;
    }

    // increase capacity if needed
    size_t needed_element_capacity = self->size_used + other->size_used;
    if (self->capacity_allocated < needed_element_capacity) {
        vec_status_t grow_result = internal_vecSetSizeTo(self, needed_element_capacity);
        if (grow_result != VEC_OK) {
            return grow_result;
        }
    }

    memcpy(
        internal_vecNThElement(self, self->size_used),
        internal_vecNThElement(other, 0),
        other->size_used * other->item_size);

    self->size_used += other->size_used;

    return VEC_OK;
}
