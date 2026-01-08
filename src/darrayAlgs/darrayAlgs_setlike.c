///
/// @file: darrayAlgs_setlike.c
/// @description: Contains functions related to setlike operations
///
/// @date: 2026-01-08 
/// @author: Moritz Pirer
///

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