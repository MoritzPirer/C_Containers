///
/// @file: vec_algs_setlike.c
/// @description: Contains functions related to setlike operations
///
/// @date: 2026-01-08
/// @author: Moritz Pirer
///

#include <assert.h>

#include "../vec_internal.h"
#include "../../../inc/vec/vec_algs.h"

/// TODO REWRITE!!!! self as pointer
bool vec_is_unique(vec_t self, vec_ordering_t vec_ordering) {
    if (self.size <= 1) {
        return true; // unique by default
    }

    for (size_t index = 1; index < self.size; index++) {
        if (vec_ordering(
            internal_vecNThElement(&self, index - 1),
            internal_vecNThElement(&self, index)) == 0)
        {
            return false;
        }
    }

    return true;
}

// TODO CONST
vec_status_t vec_get_unique(vec_t* self, vec_ordering_t vec_ordering, vec_t* unique) {
    if (self == NULL || unique == NULL) {
        return VEC_ERROR_NULL;
    }

    if (!vec_is_sorted_desc(*self, vec_ordering) && !vec_is_sorted_asc(*self, vec_ordering)) {
        return VEC_ERROR_INVALID;
    }

    if (self->size <= 1) {
        vec_copy(self, unique);
        return VEC_OK;
    }

    vec_status_t result = vec_init(unique, 0, self->item_size);
    if (result != VEC_OK) {
        return result;
    }

    result = vec_reserve(unique, self->size);
    if (result != VEC_OK) {
        return result;
    }

    result = vec_push_back(unique, internal_vecNThElement(self, 0));
    if (result != VEC_OK) {
        return result;
    }

    for (size_t index = 1; index < self->size; index++) {
        if (vec_ordering(
                internal_vecNThElement(self, index - 1),
                internal_vecNThElement(self, index)) == 0)
        {
            continue;
        }

        vec_push_back(unique, internal_vecNThElement(self, index));
    }

    vec_shrink(unique);

    return VEC_OK;
}

/// @brief returns the first index after the given index that is not a duplicate in self
size_t skipDuplicates(vec_t* self, size_t index, vec_ordering_t ordering) {
    size_t next = index + 1;

    while (next < self->size &&
        ordering( internal_vecNThElement(self, index), internal_vecNThElement(self, next)) == 0) {
        index = next;
        next++;
    }

    return index + 1;
}

// TODO const
vec_status_t vec_get_intersection(vec_t* left, vec_t* right, vec_ordering_t vec_ordering, vec_t* intersection) {
    if (left == NULL || right == NULL || intersection == NULL) {
        return VEC_ERROR_NULL;
    }

    int factor;
    if (vec_is_sorted_asc(*left, vec_ordering) && vec_is_sorted_asc(*right, vec_ordering)) {
        factor = 1;
    }
    else if (vec_is_sorted_desc(*left, vec_ordering) && vec_is_sorted_desc(*right, vec_ordering)) {
        factor = -1;
    }
    else {
        return VEC_ERROR_INVALID;
    }

    vec_status_t result = vec_init(intersection, 0, left->item_size);
    if (result != VEC_OK) {
        return result;
    }

    result = vec_reserve(intersection, max(left->size, right->size));
    if (result != VEC_OK) {
        return result;
    }

    size_t left_index = 0;
    size_t right_index = 0;

    while (left_index < left->size && right_index < right->size) {
        int ordering = vec_ordering(
            internal_vecNThElement(left, left_index),
            internal_vecNThElement(right, right_index));
        ordering *= factor;

        if (ordering == 0) {
            vec_push_back(intersection, internal_vecNThElement(left, left_index));
            left_index = skipDuplicates(left, left_index, vec_ordering);
            right_index = skipDuplicates(right, right_index, vec_ordering);
        }
        else if (ordering < 0) {
            left_index++;
        }
        else {
            right_index++;
        }
    }

    return vec_shrink(intersection);
}

vec_status_t vec_get_union(vec_t* left, vec_t* right, vec_ordering_t vec_ordering, vec_t* union_elements) {
    if (left == NULL || right == NULL || union_elements == NULL) {
        return VEC_ERROR_NULL;
    }

    int factor;
    if (vec_is_sorted_asc(*left, vec_ordering) && vec_is_sorted_asc(*right, vec_ordering)) {
        factor = 1;
    }
    else if (vec_is_sorted_desc(*left, vec_ordering) && vec_is_sorted_desc(*right, vec_ordering)) {
        factor = -1;
    }
    else {
        return VEC_ERROR_INVALID;
    }

    vec_status_t result = vec_init(union_elements, 0, left->item_size);
    if (result != VEC_OK) {
        return result;
    }

    result = vec_reserve(union_elements, left->size + right->size);
    if (result != VEC_OK) {
        return result;
    }

    size_t left_index = 0;
    size_t right_index = 0;

    while (left_index < left->size && right_index < right->size) {
        int ordering = vec_ordering(
            internal_vecNThElement(left, left_index),
            internal_vecNThElement(right, right_index));
        ordering *= factor;

        if (ordering == 0) {
            vec_push_back(union_elements, internal_vecNThElement(left, left_index));
            left_index = skipDuplicates(left, left_index, vec_ordering);
            right_index = skipDuplicates(right, right_index, vec_ordering);
        }
        else if (ordering < 0) {
            vec_push_back(union_elements, internal_vecNThElement(left, left_index));
            left_index = skipDuplicates(left, left_index, vec_ordering);
        }
        else {
            vec_push_back(union_elements, internal_vecNThElement(right, right_index));
            right_index = skipDuplicates(right, right_index, vec_ordering);
        }
    }

    // Add remaining
    while (left_index < left->size) {
        vec_push_back(union_elements, internal_vecNThElement(left, left_index));
        left_index = skipDuplicates(left, left_index, vec_ordering);
    }

    while (right_index < right->size) {
        vec_push_back(union_elements, internal_vecNThElement(right, right_index));
        right_index = skipDuplicates(right, right_index, vec_ordering);
    }

    return vec_shrink(union_elements);
}

bool vec_equals(vec_t left, vec_t right, vec_ordering_t vec_ordering) {
    if (left.size != right.size) {
        return false;
    }

    for (size_t index = 0; index < left.size; index++) {
        if (vec_ordering(
            internal_vecNThElement(&left, index),
            internal_vecNThElement(&right, index)) != 0)
        {
            return false;
        }
    }

    return true;
}
