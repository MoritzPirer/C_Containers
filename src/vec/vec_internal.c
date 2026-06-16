#include <stdlib.h>
#include <string.h>

#include "vec_internal.h"

void* _vec_nth_element(const vec_t* self, size_t index) {
    return (void *)((char *)self->array + (index * self->item_size));
}

vec_status_t _vec_set_size_to(vec_t* self, size_t new_element_count) {
    void* temp = realloc(self->array, new_element_count * self->item_size);

    if (temp == NULL) {
        return VEC_ERROR_ALLOCATION;
    }

    self->array = temp;
    self->capacity = new_element_count;

    // reduce elements used when sizing down
    self->size = MIN(self->size, new_element_count);

    return VEC_OK;
}

vec_status_t _vec_grow(vec_t* self) {
    if (self->size == self->capacity) {
        vec_status_t result = _vec_set_size_to( self, self->capacity << 1);
        return result;
    }

    return VEC_OK;
}

vec_status_t _vec_shrink_if_needed(vec_t* self) {
    if (self->capacity >> 1 > self->size) {
        return _vec_set_size_to(self, self->capacity >> 1);
    }

    return VEC_OK;
}

bool _vec_is_valid_index(const vec_t* self, size_t index) {
    return (index >= 0 && index < self->size);
}

void _vec_move_bytes(vec_t* self, size_t read_index, size_t write_index, size_t bytes_to_copy) {
    char buffer[bytes_to_copy];
    memcpy(buffer, _vec_nth_element(self, read_index), bytes_to_copy);
    memcpy(_vec_nth_element(self, write_index), buffer, bytes_to_copy);
}
