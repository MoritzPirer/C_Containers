#include <string.h>
#include <stdlib.h>

#include "../../../inc/str/str.h"
#include "../../utility.h"

///TODO: decide if this should be moved to an internal header
str_status_t _str_set_realloc(str_t* self, size_t new_size) {
    void* temp = realloc(self->array, new_size);

    if (temp == NULL) {
        return STR_ERROR_ALLOCATION;
    }

    self->array = temp;
    self->capacity = new_size;
    self->size = MIN(self->size, new_size);

    return STR_OK;
}

str_status_t _str_grow_if_needed(str_t* self) {
    if (self->size == self->capacity) {
        return _str_set_realloc(self, self->capacity << 1);
    }

    return STR_OK;
}

str_status_t _str_grow_if_needed(str_t* self) {
    if (self->size == self->capacity) {
        return _str_set_realloc(self, self->capacity << 1);
    }

    return STR_OK;
}

str_status_t str_get_at(const str_t* self, size_t index, char* destination) {
    if (self == NULL || destination == NULL) {
        return STR_ERROR_NULL;
    }

    if (index >= self->size) {
        return STR_ERROR_BOUNDS;
    }

    memcpy(destination, self->array + index, 1);

    return STR_OK;
}

str_status_t str_set_at(str_t* self, size_t index, char c) {
    if (self == NULL) {
        return STR_ERROR_NULL;
    }

    if (index >= self->size) {
        return STR_ERROR_BOUNDS;
    }

    self->array[index] = c;

    return STR_OK;
}

// how exactly with nullbyte???
const char* str_cstr(const str_t* self) { (void) self; return NULL; } 

str_status_t str_append_char(str_t* self, char c) {

}

str_status_t str_append_str(str_t* self, const str_t* other);

str_status_t str_prepend_char(str_t* self, char c);
str_status_t str_prepend_str(str_t* self, const str_t* other);

str_status_t str_insert_char(str_t* self, size_t index, char c);
str_status_t str_insert_str(str_t* self, size_t index, const str_t* other);