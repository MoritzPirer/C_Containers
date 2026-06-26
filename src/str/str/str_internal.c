#include "str_internal.h"

str_status_t _str_realloc(str_t* self, size_t new_size) {
    void* temp = realloc(self->array, new_size);

    if (temp == NULL) {
        return STR_ERROR_ALLOCATION;
    }

    self->array = temp;
    self->capacity = new_size;
    self->size = MIN(self->size, new_size);

    return STR_OK;
}

inline bool _str_is_less_than_half_full(str_t* self) {
    return (self->size << 1 < self->capacity);
}
