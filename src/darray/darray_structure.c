///
/// @file: darray_structure.h
/// @description: Contains functions related to mutating the structure of a darray 
///
/// @date: 2026-01-03 
/// @author: Moritz Pirer
///

#include <string.h>

#include "../darray_internal.h"

DarrayStatus darrayPushBack(Darray* this, void* element) {
    if (this == NULL || element == NULL) {
        return DARRAY_ERROR_NULL;
    }

    DarrayStatus grow_result = internal_darrayGrow(this);
    if (grow_result != DARRAY_OK) {
        return grow_result;
    }
    
    memcpy(internal_darrayNThElement(this, this->m_elements_used), element, this->m_element_size);

    this->m_elements_used++;
    
    return DARRAY_OK;
}


DarrayStatus darrayPopBackInto(Darray* this, void* element) {
    if (this == NULL || element == NULL) {
        return DARRAY_ERROR_NULL;
    }
    
    if (this->m_elements_used == 0) {
        return DARRAY_ERROR_BOUNDS;
    }
    
    memcpy(element, internal_darrayNThElement(this, this->m_elements_used - 1), this->m_element_size);

    this->m_elements_used--;

    return internal_darrayShrinkIfNeeded(this);
}

DarrayStatus darrayPushFront(Darray* this, void* element) {
    return darrayInsertAt(this, 0, element);
}

DarrayStatus darrayPopFrontInto(Darray* this, void* element) {
    if (this == NULL || element == NULL) {
        return DARRAY_ERROR_NULL;
    }
    
    if (this->m_elements_used == 0) {
        return DARRAY_ERROR_BOUNDS;
    }

    memcpy(element, this->m_data, this->m_element_size);
    this->m_elements_used--;

    if (this->m_elements_used == 0) { // only element removed -> no need to move over others
        return DARRAY_OK;
    }

    size_t bytes_to_copy = this->m_elements_used * this->m_element_size;
    internal_moveBytes(this, 1, 2, bytes_to_copy);
    
    return internal_darrayShrinkIfNeeded(this);
}

DarrayStatus darrayInsertAt(Darray* this, size_t index, void* element) {
    if (this == NULL) {
        return DARRAY_ERROR_NULL;
    }
    
    if (!internal_darrayIsValidIndex(this, index)) {
        return DARRAY_ERROR_BOUNDS;
    }
    
    DarrayStatus grow_result = internal_darrayGrow(this);
    if (grow_result != DARRAY_OK) {
        return grow_result;
    }
    
    size_t num_elements_behind_insert = this->m_elements_used - index;

    size_t bytes_to_copy = num_elements_behind_insert * this->m_element_size;
    internal_moveBytes(this, index, index + 1, bytes_to_copy);

    memcpy(internal_darrayNThElement(this, index), element, this->m_element_size);

    this->m_elements_used++;

    return DARRAY_OK;
}