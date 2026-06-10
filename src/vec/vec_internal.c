#include <stdlib.h>
#include <string.h>

#include "vec_internal.h"

size_t max(size_t a, size_t b) {
    return (a > b ? a : b);
}

size_t min(size_t a, size_t b) {
    return (a < b ? a : b);
}

void swapValues(size_t* a, size_t* b) {
    size_t temp = *a;
    *a = *b;
    *b = temp;
}

void* internal_vecNThElement(const vec_t* self, size_t index) {
    return (void *)((char *)self->m_data + (index * self->item_size));
}

vec_status_t internal_vecSetSizeTo(vec_t* self, size_t new_element_count) {
    void *temp = realloc(self->m_data, new_element_count*  self->item_size);

    if (temp == NULL) {
        return VEC_ERROR_ALLOCATION;
    }

    self->m_data = temp;
    self->capacity_allocated = new_element_count;

    // reduce elements used when sizing down
    self->size_used = min(self->size_used, new_element_count);

    return VEC_OK;
}

vec_status_t internal_vecGrow(vec_t* self) {
    if (self->size_used == self->capacity_allocated) {
        vec_status_t result = internal_vecSetSizeTo( self, self->capacity_allocated << 1);
        return result;
    }

    return VEC_OK;
}

vec_status_t internal_vecShrinkIfNeeded(vec_t* self) {
    if (self->capacity_allocated >> 1 > self->size_used) {
        return internal_vecSetSizeTo(self, self->capacity_allocated >> 1);
    }

    return VEC_OK;
}

bool internal_vecIsValidIndex(const vec_t* self, size_t index) {
    return (index >= 0 && index < self->size_used);
}

void internal_moveBytes(vec_t* self, size_t read_index, size_t write_index, size_t bytes_to_copy) {
    char buffer[bytes_to_copy];
    memcpy(buffer, internal_vecNThElement(self, read_index), bytes_to_copy);
    memcpy(internal_vecNThElement(self, write_index), buffer, bytes_to_copy);
}
