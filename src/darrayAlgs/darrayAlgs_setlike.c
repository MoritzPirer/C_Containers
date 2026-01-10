///
/// @file: darrayAlgs_setlike.c
/// @description: Contains functions related to setlike operations
///
/// @date: 2026-01-08 
/// @author: Moritz Pirer
///
#include <stdio.h>
#include "../darray_internal.h"
#include "../../inc/darrayAlgs.h"

bool darrayIsUnique(Darray self, darrayOrdering darray_ordering) {
    if (self.m_elements_used <= 1) {
        return true; //unique by default
    }

    for (size_t index = 1; index < self.m_elements_used; index++) {
        if (darray_ordering(
            internal_darrayNThElement(&self, index - 1),
            internal_darrayNThElement(&self, index)
        ) == 0) {
            return false;
        } 
    }
    return true;
}

DarrayStatus darrayGetUnique(const Darray* self, darrayOrdering darray_ordering, Darray* unique) {
    if (self == NULL || unique == NULL) {
        return DARRAY_ERROR_NULL;
    }

    if (!darrayIsSortedDescending(*self, darray_ordering)
        && !darrayIsSortedAscending(*self, darray_ordering)) {
        return DARRAY_ERROR_INVALID;
    }

    if (self->m_elements_used <= 1) {
        darrayDeepCopy(self, unique);
        return DARRAY_OK;
    }

    DarrayStatus result = darrayInit(unique, 0, self->m_element_size);
    if (result != DARRAY_OK) return result;

    result = darrayReserve(unique, self->m_elements_used);
    if (result != DARRAY_OK) return result;

    result = darrayPushBack(unique, internal_darrayNThElement(self, 0));
    if (result != DARRAY_OK) return result;

    for (size_t index = 1; index < self->m_elements_used; index++) {
        if (darray_ordering(
            internal_darrayNThElement(self, index - 1),
            internal_darrayNThElement(self, index)
        ) == 0) {
            continue;
        } 

        darrayPushBack(unique, internal_darrayNThElement(self, index));
    }

    darrayShrinkToFit(unique);

    return DARRAY_OK;
}

/// @brief returns the first index after the given index that is not a duplicate in self
size_t skipDuplicates(const Darray* self, size_t index, darrayOrdering ordering) {
    size_t next = index + 1;

    while (next < self->m_elements_used && ordering(
            internal_darrayNThElement(self, index),
            internal_darrayNThElement(self, next)
        ) == 0) {
        index = next;
        next++;
    }

    return index + 1;
}

DarrayStatus darrayGetIntersection(const Darray* left, const Darray* right,
    darrayOrdering darray_ordering, Darray* intersection) {

    if (left == NULL || right == NULL || intersection == NULL) {
        return DARRAY_ERROR_NULL;
    }
    
    int factor;
    if (darrayIsSortedAscending(*left, darray_ordering) 
        && darrayIsSortedAscending(*right, darray_ordering)) {
        factor = 1;
    }
    else if (darrayIsSortedDescending(*left, darray_ordering)
        && darrayIsSortedDescending(*right, darray_ordering)) {
        factor = -1;
    } 
    else {
        return DARRAY_ERROR_INVALID;
    }

    DarrayStatus result = darrayInit(intersection, 0, left->m_element_size);
    if (result != DARRAY_OK) return result;
    
    result = darrayReserve(intersection, max(left->m_elements_used, right->m_elements_used));
    if (result != DARRAY_OK) return result;

    size_t left_index = 0;
    size_t right_index = 0;
    
    while (left_index < left->m_elements_used && right_index < right->m_elements_used) {
        int ordering = darray_ordering(
            internal_darrayNThElement(left, left_index),
            internal_darrayNThElement(right, right_index)
        );
        ordering *= factor;

        if (ordering == 0) {
            darrayPushBack(intersection, internal_darrayNThElement(left, left_index));
            left_index = skipDuplicates(left, left_index, darray_ordering);
            right_index = skipDuplicates(right, right_index, darray_ordering);
        }
        else if (ordering < 0) {
            left_index++;
        }
        else {
            right_index++;
        }
    }

    return darrayShrinkToFit(intersection);
}

DarrayStatus darrayGetUnion(const Darray* left, const Darray* right,
    darrayOrdering darray_ordering, Darray* union_elements) {

    if (left == NULL || right == NULL || union_elements == NULL) {
        return DARRAY_ERROR_NULL;
    }
    
    int factor;
    if (darrayIsSortedAscending(*left, darray_ordering) 
        && darrayIsSortedAscending(*right, darray_ordering)) {
        factor = 1;
    }
    else if (darrayIsSortedDescending(*left, darray_ordering)
        && darrayIsSortedDescending(*right, darray_ordering)) {
        factor = -1;
    } 
    else {
        return DARRAY_ERROR_INVALID;
    }

    DarrayStatus result = darrayInit(union_elements, 0, left->m_element_size);
    if (result != DARRAY_OK) return result;
    
    result = darrayReserve(union_elements, left->m_elements_used + right->m_elements_used);
    if (result != DARRAY_OK) return result;

    size_t left_index = 0;
    size_t right_index = 0;

    while (left_index < left->m_elements_used && right_index < right->m_elements_used) {
        int ordering = darray_ordering(
            internal_darrayNThElement(left, left_index),
            internal_darrayNThElement(right, right_index)
        );
        ordering *= factor;

        if (ordering == 0) {
            darrayPushBack(union_elements, internal_darrayNThElement(left, left_index));
            left_index = skipDuplicates(left, left_index, darray_ordering);
            right_index = skipDuplicates(right, right_index, darray_ordering);
        }
        else if (ordering < 0) {
            darrayPushBack(union_elements, internal_darrayNThElement(left, left_index));
            left_index = skipDuplicates(left, left_index, darray_ordering);
        }
        else {
            darrayPushBack(union_elements, internal_darrayNThElement(right, right_index));
            right_index = skipDuplicates(right, right_index, darray_ordering);
        }
    }

    // Add remaining
    while (left_index < left->m_elements_used) {
        darrayPushBack(union_elements, internal_darrayNThElement(left, left_index));
        left_index = skipDuplicates(left, left_index, darray_ordering);
    }

    while (right_index < right->m_elements_used) {
        darrayPushBack(union_elements, internal_darrayNThElement(right, right_index));
        right_index = skipDuplicates(right, right_index, darray_ordering);
    }

    return darrayShrinkToFit(union_elements);
}

bool darrayEquals(Darray left, Darray right, darrayOrdering darray_ordering) {
    if (left.m_elements_used != right.m_elements_used) {
        return false;
    }

    for (size_t index = 0; index < left.m_elements_used; index++) {
        if (darray_ordering(
            internal_darrayNThElement(&left, index),
            internal_darrayNThElement(&right, index)
        ) != 0) {
            return false;
        }
    }

    return true;
}
