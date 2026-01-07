///
/// @file: darray_structure.h
/// @description: Contains functions related to mutating the structure of a darray 
///
/// @date: 2026-01-03 
/// @author: Moritz Pirer
///

#include <stdio.h>
#include <string.h>

#include "../darray_internal.h"

DarrayStatus darrayPushBack(Darray* self, void* element) {
    if (self == NULL || element == NULL) {
        printf("NULL");
        return DARRAY_ERROR_NULL;
    }

    DarrayStatus grow_result = internal_darrayGrow(self);
    if (grow_result != DARRAY_OK) {
        printf("GROW");
        return grow_result;
    }
    memcpy(internal_darrayNThElement(self, self->m_elements_used), element, self->m_element_size);

    self->m_elements_used++;
    
    return DARRAY_OK;
}


DarrayStatus darrayPopBackInto(Darray* self, void* element) {
    if (self == NULL || element == NULL) {
        return DARRAY_ERROR_NULL;
    }
    
    if (self->m_elements_used == 0) {
        return DARRAY_ERROR_BOUNDS;
    }
    
    memcpy(element, internal_darrayNThElement(self, self->m_elements_used - 1), self->m_element_size);

    self->m_elements_used--;

    return internal_darrayShrinkIfNeeded(self);
}

DarrayStatus darrayPushFront(Darray* self, void* element) {
    return darrayInsertAt(self, 0, element);
}

DarrayStatus darrayPopFrontInto(Darray* self, void* element) {
    if (self == NULL || element == NULL) {
        return DARRAY_ERROR_NULL;
    }
    
    if (self->m_elements_used == 0) {
        return DARRAY_ERROR_BOUNDS;
    }

    memcpy(element, self->m_data, self->m_element_size);
    self->m_elements_used--;

    if (self->m_elements_used == 0) { // only element removed -> no need to move over others
        return DARRAY_OK;
    }

    size_t bytes_to_copy = self->m_elements_used * self->m_element_size;
    internal_moveBytes(self, 1, 0, bytes_to_copy);
    
    return internal_darrayShrinkIfNeeded(self);
}

DarrayStatus darrayInsertAt(Darray* self, size_t index, void* element) {
    if (self == NULL) {
        return DARRAY_ERROR_NULL;
    }
    
    if (!internal_darrayIsValidIndex(self, index)) {
        return DARRAY_ERROR_BOUNDS;
    }
    
    DarrayStatus grow_result = internal_darrayGrow(self);
    if (grow_result != DARRAY_OK) {
        return grow_result;
    }
    
    size_t num_elements_behind_insert = self->m_elements_used - index;

    size_t bytes_to_copy = num_elements_behind_insert * self->m_element_size;
    internal_moveBytes(self, index, index + 1, bytes_to_copy);

    memcpy(internal_darrayNThElement(self, index), element, self->m_element_size);

    self->m_elements_used++;

    return DARRAY_OK;
}