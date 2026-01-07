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

void* internal_darrayNThElement(const Darray* self, size_t index) {
    return (void*) ((char*) self->m_data + (index * self->m_element_size));
}

DarrayStatus internal_darraySetSizeTo(Darray* self, size_t new_element_count) {
    void* temp = realloc(self->m_data, new_element_count * self->m_element_size);

    if (temp == NULL) {
        return DARRAY_ERROR_ALLOCATION;
    }

    self->m_data = temp;
    self->m_elements_allocated = new_element_count;

    //reduce elements used when sizing down
    self->m_elements_used = min(self->m_elements_used, new_element_count); 

    return DARRAY_OK; 
}

DarrayStatus internal_darrayGrow(Darray* self) {
    if (self->m_elements_used == self->m_elements_allocated) {
        DarrayStatus result = internal_darraySetSizeTo(
            self,
            self->m_elements_allocated << 1);
        return result;
    }

    return DARRAY_OK;
}

DarrayStatus internal_darrayShrinkIfNeeded(Darray* self) {
    if (self->m_elements_allocated >> 1 > self->m_elements_used) {
        return internal_darraySetSizeTo(self, self->m_elements_allocated >> 1);
    }

    return DARRAY_OK;
}

bool internal_darrayIsValidIndex(const Darray* self, size_t index) {
    return (index >= 0 && index < self->m_elements_used);
}

void internal_moveBytes(Darray* self, size_t read_index, size_t write_index, size_t bytes_to_copy) {
    char buffer[bytes_to_copy];
    memcpy(buffer, internal_darrayNThElement(self, read_index), bytes_to_copy);
    memcpy(internal_darrayNThElement(self, write_index), buffer, bytes_to_copy);
}