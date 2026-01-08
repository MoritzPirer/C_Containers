///
/// @file: darrayAlgs_searching.c
/// @description: Contains functions related to searching for the index of elements
///
/// @date: 2026-01-06 
/// @author: Moritz Pirer
///

#include "../darray_internal.h"
#include "../../inc/darrayAlgs.h"

DarrayStatus darrayFindFirst(const Darray* self, darrayCondition condition,
    size_t* index_buffer, const void* data) {

    if (self == NULL || index_buffer == NULL) {
        return DARRAY_ERROR_NULL;
    }

    for (size_t index = 0; index < self->m_elements_used; index++) {
        if (condition(internal_darrayNThElement(self, index), data) == true) {
            *index_buffer = index;
            return DARRAY_OK;
        }
    }

    return DARRAY_NOT_FOUND;
}

DarrayStatus darrayFindLast(const Darray* self, darrayCondition condition,
    size_t* index_buffer, const void* data) {

    if (self == NULL || index_buffer == NULL) {
        return DARRAY_ERROR_NULL;
    }

    for (size_t i = 0; i < self->m_elements_used; i++) {
        size_t index = self->m_elements_used - i - 1; //covers some edge cases better because of underflow
        if (condition(internal_darrayNThElement(self, index), data) == true) {
            *index_buffer = index;
            return DARRAY_OK;
        }
    }

    return DARRAY_NOT_FOUND;
}

bool darrayContains(Darray self, darrayCondition condition, const void* data) {
    size_t dummy;
    return darrayFindFirst(&self, condition, &dummy, data) == DARRAY_OK;
}

DarrayStatus darrayBinarySearch(const Darray* self, darrayOrdering darray_ordering,
    size_t* index_buffer, const void* key) {

    if (self == NULL || index_buffer == NULL || key == NULL) {
        return DARRAY_ERROR_NULL;
    }

    if (self->m_elements_used == 0) {
        return DARRAY_NOT_FOUND;
    }

    size_t left = 0;
    size_t right = self->m_elements_used - 1;

    while (left <= right) {
        size_t middle = (left + right) / 2;

        int ordering = darray_ordering(&middle, key); 

        if (ordering == 0) {
            *index_buffer = middle;
            return DARRAY_OK;
        }
        
        if (ordering < 0) {
            left = middle + 1;
            continue;
        }

        if (ordering > 0) {
            right = middle - 1;
            continue;
        }
    }
    
    return DARRAY_NOT_FOUND;
}