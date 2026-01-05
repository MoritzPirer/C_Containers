#include <stdlib.h>
#include <string.h>

#include "darray_internal.h"

size_t max(size_t a, size_t b) {
    return (a > b? a : b);
}

size_t min(size_t a, size_t b) {
    return (a < b? a : b);
}

void swapValues(size_t* a, size_t* b) {
    size_t temp = *a;
    *a =  *b;
    *b = temp;
}

/// @brief return a pointer to the n-th element of array. Only for internal use
///     because pointer can become stale if the array reallocates
/// @attention caller is responsible for making sure that address is valid
/// @param this the darray to access 
/// @param index the index to access in the darray
/// @return a pointer to the n-th element
void* internal_darrayNThElement(const Darray* this, size_t index) {
    return (void*) ((char*) this->m_data + (index * this->m_element_size));
}

/// @brief set the size of the darray to new_element_count. 
///     If the new size is less than the amount of elements in use, they are lost.
/// @param this the darray to modify
/// @param new_element_count the new size of the darray 
/// @return DARRAY_ERROR_ALLOCATION if reallocation failed, DARRAY_OK otherwise
DarrayStatus internal_darraySetSizeTo(Darray* this, size_t new_element_count) {
    void* temp = realloc(this->m_data, new_element_count * this->m_element_size);

    if (temp == NULL) {
        return DARRAY_ERROR_ALLOCATION;
    }

    this->m_data = temp;
    this->m_elements_allocated = new_element_count;

    //reduce elements used when sizing down
    this->m_elements_used = min(this->m_elements_used, new_element_count); 

    return DARRAY_OK; 
}

DarrayStatus internal_darrayGrow(Darray* this) {
    if (this->m_elements_used == this->m_elements_allocated) {
        DarrayStatus result = internal_darraySetSizeTo(
            this,
            this->m_elements_allocated << 1);
        return result;
    }

    return DARRAY_OK;
}

/// @brief If the darray is less than half full, shrink to be half the size
/// @param this the darray to shrink
/// @return DARRAY_ERROR_ALLOCATION if reallocation failed, DARRAY_OK otherwise
DarrayStatus internal_darrayShrinkIfNeeded(Darray* this) {
    if (this->m_elements_allocated >> 1 > this->m_elements_used) {
        return internal_darraySetSizeTo(this, this->m_elements_allocated >> 1);
    }

    return DARRAY_OK;
}

bool internal_darrayIsValidIndex(const Darray* this, size_t index) {
    return (index >= 0 && index < this->m_elements_used);
}

void internal_moveBytes(Darray* this, size_t read_index, size_t write_index, size_t bytes_to_copy) {
    char buffer[bytes_to_copy];
    memcpy(buffer, internal_darrayNThElement(this, read_index), bytes_to_copy);
    memcpy(internal_darrayNThElement(this, write_index), buffer, bytes_to_copy);
}