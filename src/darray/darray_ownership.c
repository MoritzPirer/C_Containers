///
/// @file: darray_ownership.h
/// @description: Contains functions related to obtaining, owning and transferring 
///     ownership of memory. If it would be a constructor / destructor in C++, it belongs here.
///
/// @date: 2025-12-31
/// @author: Moritz Pirer
///

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../darray_internal.h"

DarrayStatus darrayInit(Darray* self, size_t initial_size, size_t element_size) {
    if (self == NULL) {
        return DARRAY_ERROR_NULL;
    }
    if (element_size == 0) {
        return DARRAY_ERROR_INVALID;
    }

    self->m_elements_used = initial_size;
    self->m_elements_allocated = max(initial_size, DARRAY_MIN_SIZE);
    self->m_element_size = element_size;
    self->m_data = malloc(self->m_elements_allocated * element_size);

    if (self->m_data == NULL) {
        return DARRAY_ERROR_ALLOCATION;
    }

    return DARRAY_OK;
}

DarrayStatus darrayDestroy(Darray* self) {
    if (self == NULL) {
        return DARRAY_ERROR_NULL;
    }

    free(self->m_data);
    self->m_data = NULL;
    self->m_elements_allocated = 0;
    self->m_elements_used = 0;

    return DARRAY_OK;
}

DarrayStatus darraySwap(Darray* self, Darray* other) {
    if (self == NULL || other == NULL) {
        return DARRAY_ERROR_NULL;
    }

    swapValues(&(self->m_element_size), &(other->m_element_size));
    swapValues(&(self->m_elements_allocated), &(other->m_elements_allocated));
    swapValues(&(self->m_elements_used), &(other->m_elements_used));

    void* temp = self->m_data;
    self->m_data = other->m_data;
    other->m_data = temp;
    
    return DARRAY_OK;
}

DarrayStatus darrayDeepCopy(const Darray* original, Darray* copy) {
    if (original == NULL || copy == NULL) {
        return DARRAY_ERROR_NULL;
    }
    
    size_t data_amount_bytes = original->m_elements_allocated * original->m_element_size;
    copy->m_data = malloc(data_amount_bytes);
    if (copy->m_data == NULL) {
        return DARRAY_ERROR_ALLOCATION;
    }

    memcpy(copy->m_data, original->m_data, data_amount_bytes);

    copy->m_elements_used = original->m_elements_used;
    copy->m_elements_allocated = original->m_elements_used;
    copy->m_element_size = original->m_element_size;
   
    return DARRAY_OK;
}

DarrayStatus darrayAppend(Darray* self, const Darray* other) {
    if (self == NULL || other == NULL) {
        return DARRAY_ERROR_NULL;
    }

    // increase capacity if needed
    size_t needed_element_capacity = self->m_elements_used + other->m_elements_used;
    if (self->m_elements_allocated < needed_element_capacity) {
        DarrayStatus grow_result = internal_darraySetSizeTo(self, needed_element_capacity);
        if (grow_result != DARRAY_OK) {
            return grow_result;
        }
    }

    memcpy(
        internal_darrayNThElement(self, self->m_elements_used),
        internal_darrayNThElement(other, 0),
        other->m_elements_used * other->m_element_size
    );

    self->m_elements_used += other->m_elements_used;

    return DARRAY_OK;
}
