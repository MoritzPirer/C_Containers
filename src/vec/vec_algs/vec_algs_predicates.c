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
#include "../../../inc/vec/vec_algs.h"

bool vec_any(const vec_t* self, vec_condition_t condition, const void *data) {
    if (self == NULL) {
        return false;
    }

    for (size_t index = 0; index < self->size; index++) {
        if (condition(_vec_nth_element(self, index), data) == true) {
            return true;
        }
    }

    return false;
}

bool vec_all(const vec_t* self, vec_condition_t condition, const void *data) {
    if (self == NULL) {
        return false;
    }

    for (size_t index = 0; index < self->size; index++) {
        if (condition(_vec_nth_element(self, index), data) == false) {
            return false;
        }
    }

    return true;
}

bool vec_none(const vec_t* self, vec_condition_t condition, const void *data) {
    if (self == NULL) {
        return false;
    }

    for (size_t index = 0; index < self->size; index++) {
        if (condition(_vec_nth_element(self, index), data) == true) {
            return false;
        }
    }

    return true;
}

void vec_reverse(vec_t* self)
{
    for (size_t index = 0; index < self->size / 2; index++) {
        size_t swap_index = self->size - index - 1;
        char buffer[self->item_size];
        memcpy(buffer, _vec_nth_element(self, index), self->item_size);
        memcpy(
            _vec_nth_element(self, index),
            _vec_nth_element(self, swap_index),
            self->item_size);
        memcpy(_vec_nth_element(self, swap_index), buffer, self->size);
    }

    self->iterator_version++;
}

vec_status_t vec_filter(const vec_t* self, vec_condition_t condition, vec_t* filtered, const void *data) {
    if (self == NULL || filtered == NULL) {
        return VEC_ERROR_NULL;
    }

    if (vec_init(filtered, 0, sizeof(size_t)) != VEC_OK) {
        return VEC_ERROR_ALLOCATION;
    }

    if (vec_reserve(filtered, self->size) != VEC_OK) {
        return VEC_ERROR_ALLOCATION;
    }

    for (size_t index = 0; index < self->size; index++) {
        if (condition(_vec_nth_element(self, index), data) == false) {
            continue;
        }

        vec_status_t result = vec_push_back(filtered, _vec_nth_element(self, index));
        if (result != VEC_OK) {
            return result;
        }
    }

    return vec_shrink(filtered);
}

vec_status_t vec_transform(vec_t* self, vec_transformation_t transfomration, const void *data) {
    if (self == NULL) {
        return VEC_ERROR_NULL;
    }

    for (size_t index = 0; index < self->size; index++) {
        transfomration(_vec_nth_element(self, index), data);
    }

    return VEC_OK;
}