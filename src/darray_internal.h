///
/// @file: darray_internal.h
/// @description: Internal helper functions used across multiple implementation files
///
/// @date: 2026-01-03 
/// @author: Moritz Pirer
///

#ifndef DARRAY_INTERNAL_H
#define DARRAY_INTERNAL_H

#include <stdbool.h>

#include "../inc/darray.h"


size_t max(size_t a, size_t b);

size_t min(size_t a, size_t b);

void swapValues(size_t* a, size_t* b);

/// @brief return a pointer to the n-th element of array. Only for internal use
///     because pointer can become stale if the array reallocates
/// @attention caller is responsible for making sure that address is valid
/// @param this the darray to access 
/// @param index the index to access in the darray
/// @return a pointer to the n-th element
void* internal_darrayNThElement(const Darray* this, size_t index);

/// @brief set the size of the darray to new_element_count. 
///     If the new size is less than the amount of elements in use, they are lost.
/// @param this the darray to modify
/// @param new_element_count the new size of the darray 
/// @return DARRAY_ERROR_ALLOCATION if reallocation failed, DARRAY_OK otherwise
DarrayStatus internal_darraySetSizeTo(Darray* this, size_t new_element_count);

/// @brief double the size of the darray
/// @param this the darray to size up
/// @return DARRAY_ERROR_ALLOCATION if reallocation failed, DARRAY_OK otherwise
DarrayStatus internal_darrayGrow(Darray* this);

/// @brief If the darray is less than half full, shrink to be half the size
/// @param this the darray to shrink
/// @return DARRAY_ERROR_ALLOCATION if reallocation failed, DARRAY_OK otherwise
DarrayStatus internal_darrayShrinkIfNeeded(Darray* this);

/// @return true if index is valid for this, false otherwise
bool internal_darrayIsValidIndex(const Darray* this, size_t index);

void internal_moveBytes(Darray* this, size_t read_index, size_t write_index, size_t bytes_to_copy);
#endif //DARRAY_INTERNAL_H
