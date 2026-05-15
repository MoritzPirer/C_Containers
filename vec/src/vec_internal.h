///
/// @file: vec_internal.h
/// @description: Internal helper functions used across multiple implementation files
///
/// @date: 2026-01-03
/// @author: Moritz Pirer
///

#ifndef VEC_INTERNAL_H
#define VEC_INTERNAL_H

#include <stdbool.h>

#include "../inc/vec.h"

size_t max(size_t a, size_t b);

size_t min(size_t a, size_t b);

void swapValues(size_t *a, size_t *b);

/// @brief return a pointer to the n-th element of array. Only for internal use
///     because pointer can become stale if the array reallocates
/// @attention caller is responsible for making sure that address is valid
/// @param self the vec to access
/// @param index the index to access in the vec
/// @return a pointer to the n-th element
void *internal_vecNThElement(vec_t *self, size_t index);

/// @brief set the size of the vec to new_element_count.
///     If the new size is less than the amount of elements in use, they are lost.
/// @param self the vec to modify
/// @param new_element_count the new size of the vec
/// @return VEC_ERROR_ALLOCATION if reallocation failed, VEC_OK otherwise
VecStatus internal_vecSetSizeTo(vec_t *self, size_t new_element_count);

/// @brief double the size of the vec
/// @param self the vec to size up
/// @return VEC_ERROR_ALLOCATION if reallocation failed, VEC_OK otherwise
VecStatus internal_vecGrow(vec_t *self);

/// @brief If the vec is less than half full, shrink to be half the size
/// @param self the vec to shrink
/// @return VEC_ERROR_ALLOCATION if reallocation failed, VEC_OK otherwise
VecStatus internal_vecShrinkIfNeeded(vec_t *self);

/// @return true if index is valid for self, false otherwise
bool internal_vecIsValidIndex(vec_t *self, size_t index);

void internal_moveBytes(vec_t *self, size_t read_index, size_t write_index, size_t bytes_to_copy);
#endif // VEC_INTERNAL_H
