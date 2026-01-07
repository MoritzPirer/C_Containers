///
/// @file: darray_access.h
/// @description: Contains functions related to accessing elements of a darray
///
/// @date: 2026-01-03 
/// @author: Moritz Pirer
///
#include <string.h>

#include "../darray_internal.h"

DarrayStatus darrayGetAt(const Darray* self, size_t index, void* buffer) {
    if (self == NULL || buffer == NULL) {
        return DARRAY_ERROR_NULL;
    }
    
    if (!internal_darrayIsValidIndex(self, index)) {
        return DARRAY_ERROR_BOUNDS;
    }

    memcpy(buffer, internal_darrayNThElement(self, index), self->m_element_size);

    return DARRAY_OK;
}

DarrayStatus darraySetAt(Darray* self, size_t index, const void* buffer) {
    if (self == NULL) {
        return DARRAY_ERROR_NULL;
    }
    
    if (!internal_darrayIsValidIndex(self, index)) {
        return DARRAY_ERROR_BOUNDS;
    }

    memcpy(internal_darrayNThElement(self, index), buffer, self->m_element_size);

    return DARRAY_OK;
}

void* darrayData(const Darray* self) {
    if (self == NULL) {
        return NULL;
    }

    return self->m_data;
}
