///
/// @file: darray_access.h
/// @description: Contains functions related to accessing elements of a darray
///
/// @date: 2026-01-03 
/// @author: Moritz Pirer
///
#include <string.h>

#include "../darray_internal.h"

DarrayStatus darrayGetAt(Darray* this, size_t index, void* buffer) {
    if (this == NULL || buffer == NULL) {
        return DARRAY_ERROR_NULL;
    }
    
    if (!internal_darrayIsValidIndex(this, index)) {
        return DARRAY_ERROR_BOUNDS;
    }

    memcpy(buffer, internal_darrayNThElement(this, index), this->m_element_size);

    return DARRAY_OK;
}

DarrayStatus darraySetAt(Darray* this, size_t index, void* buffer) {
    if (this == NULL) {
        return DARRAY_ERROR_NULL;
    }
    
    if (!internal_darrayIsValidIndex(this, index)) {
        return DARRAY_ERROR_BOUNDS;
    }

    memcpy(internal_darrayNThElement(this, index), buffer, this->m_element_size);

    return DARRAY_OK;
}

void* darrayData(Darray* this) {
    if (this == NULL) {
        return NULL;
    }

    return this->m_data;
}
