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

void vec_debug(vec_t* self) {
    if (self == NULL) {
        return;
    }

    printf("=========\n");
    printf("====\n");
    printf("size: %zu\n", self->size);
    printf("capacity: %zu\n", self->capacity);
    printf("item size: %zu\n", self->item_size);

    for (size_t i = 0; i < self->size; i++) {
        printf("vec[%zu] = %d\n", i, *(int*) internal_vecNThElement(self, i));
    }

    printf("=========\n");
}
vec_status_t vec_push_back(vec_t* self, const void* element) {
    if (self == NULL || element == NULL) {
        return VEC_ERROR_NULL;
    }

    vec_status_t grow_result = internal_vecGrow(self);
    if (grow_result != VEC_OK) {
        return grow_result;
    }

    memcpy(internal_vecNThElement(self, self->size), element, self->item_size);
    self->size++;

    return VEC_OK;
}

vec_status_t vec_pop_back(vec_t* self, void* element) {
    if (self == NULL || element == NULL) {
        return VEC_ERROR_NULL;
    }

    if (self->size == 0) {
        return VEC_ERROR_BOUNDS;
    }

    memcpy(element, internal_vecNThElement(self, self->size - 1), self->item_size);

    self->size--;

    vec_status_t result = internal_vecShrinkIfNeeded(self);

    return result;
}

vec_status_t vec_push_front(vec_t* self, const void* element) {
    return vec_insert(self, 0, element);
}

vec_status_t vec_pop_front(vec_t* self, void* element) {
    if (self == NULL || element == NULL) {
        return VEC_ERROR_NULL;
    }

    if (self->size == 0) {
        return VEC_ERROR_BOUNDS;
    }

    memcpy(element, self->array, self->item_size);
    self->size--;

    if (self->size == 0) { // only element removed -> no need to move over others
        return VEC_OK;
    }

    size_t bytes_to_copy = self->size*  self->item_size;
    internal_moveBytes(self, 1, 0, bytes_to_copy);

    vec_status_t result = internal_vecShrinkIfNeeded(self);

    return result;
}

vec_status_t vec_insert(vec_t* self, size_t index, const void* element) {
    if (self == NULL) {
        return VEC_ERROR_NULL;
    }

    if (!internal_vecIsValidIndex(self, index)) {
        return VEC_ERROR_BOUNDS;
    }

    vec_status_t grow_result = internal_vecGrow(self);
    if (grow_result != VEC_OK) {
        return grow_result;
    }

    size_t num_elements_behind_insert = self->size - index;

    size_t bytes_to_copy = num_elements_behind_insert*  self->item_size;
    internal_moveBytes(self, index, index + 1, bytes_to_copy);

    memcpy(internal_vecNThElement(self, index), element, self->item_size);

    self->size++;

    return VEC_OK;
}