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


vec_status_t vec_init(vec_t* self, size_t initial_capacity, size_t element_size) {
    if (self == NULL) {
        return VEC_ERROR_NULL;
    }

    if (element_size == 0) {
        return VEC_ERROR_INVALID;
    }

    self->size = 0;
    self->capacity = MAX(initial_capacity, VEC_MIN_CAPACITY);
    self->item_size = element_size;
    self->array = calloc(self->capacity, element_size);
    self->iterator_version = 0;

    if (self->array == NULL) {
        return VEC_ERROR_ALLOCATION;
    }

    return VEC_OK;
}

vec_status_t vec_destroy(vec_t* self) {
    if (self == NULL) {
        return VEC_ERROR_NULL;
    }

    free(self->array);
    self->array = NULL;
    self->capacity = 0;
    self->size = 0;
    self->iterator_version = 0;

    return VEC_OK;
}

vec_status_t vec_swap(vec_t* self, vec_t* other) {
    if (self == NULL || other == NULL) {
        return VEC_ERROR_NULL;
    }

    if (self == other) {
        return VEC_OK; // swap with self
    }

    swap(&(self->item_size), &(other->item_size));
    swap(&(self->capacity), &(other->capacity));
    swap(&(self->size), &(other->size));

    self->iterator_version++;
    other->iterator_version++;

    void* temp = self->array;
    self->array = other->array;
    other->array = temp;

    return VEC_OK;
}

vec_status_t vec_copy(const vec_t* original, vec_t* copy) {
    if (original == NULL || copy == NULL) {
        return VEC_ERROR_NULL;
    }

    size_t data_amount_bytes = original->capacity * original->item_size;

    copy->array = malloc(data_amount_bytes);
    if (copy->array == NULL) {
        return VEC_ERROR_ALLOCATION;
    }

    memcpy(copy->array, original->array, data_amount_bytes);

    copy->size = original->size;
    copy->capacity = original->capacity;
    copy->item_size = original->item_size;
    copy->iterator_version = original->iterator_version;

    return VEC_OK;
}

vec_status_t vec_add_all(vec_t* self, const vec_t* other) {
    if (self == NULL || other == NULL) {
        return VEC_ERROR_NULL;
    }

    // increase capacity if needed
    size_t needed_element_capacity = self->size + other->size;
    if (self->capacity < needed_element_capacity) {
        vec_status_t grow_result = _vec_set_size_to(self, needed_element_capacity);
        if (grow_result != VEC_OK) {
            return grow_result;
        }
    }

    memcpy(
        _vec_nth_element(self, self->size),
        _vec_nth_element(other, 0),
        other->size*  other->item_size
    );

    self->size += other->size;
    self->iterator_version++;

    return VEC_OK;
}
