#include "../../../inc/str/str.h"
#include "str_internal.h"
#include "../../utility.h"

str_status_t str_erase_from_to(str_t* self, size_t start, size_t end) {
    if (self == NULL) {
        return STR_ERROR_NULL;
    }

    if (start >= self->size) {
        return STR_ERROR_BOUNDS;
    }

    if (end >= self->size) {
        return STR_ERROR_BOUNDS;
    }

    if (end < start) {
        return STR_ERROR_BOUNDS;
    }

    size_t num_elements_behind_erase = self->size - end;
    if (num_elements_behind_erase > 0) {
        char buffer[num_elements_behind_erase];
        void* read_pos = self->array + end + 1;
        void* write_pos = self->array + start;
        memcpy(buffer, read_pos, num_elements_behind_erase);
        memcpy(write_pos, buffer, num_elements_behind_erase);
    }

    self->size -= (end - start + 1);
    
    if (_str_is_less_than_half_full(self)) {
        return _str_realloc(self, next_power_of_two(self->size));
    }
    
    return STR_OK;
}

str_status_t str_erase_from(str_t* self, size_t start) {
    if (self == NULL) {
        return STR_ERROR_NULL;
    }

    return str_erase_from_to(self, start, self->size - 1);
}

str_status_t str_erase_to(str_t* self, size_t end) {
    return str_erase_from_to(self, 0, end);
}

str_status_t str_erase_at(str_t* self, size_t index) {
    return str_erase_from_to(self, index, index);
}

str_status_t str_clear(str_t* self) {
    if (self == NULL) {
        return STR_ERROR_NULL;
    }

    return str_erase_from_to(self, 0, self->size - 1);
}