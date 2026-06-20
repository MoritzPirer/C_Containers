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
    return _str_set_realloc(self, self->capacity << 1);
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
    if (self == NULL) {
        return STR_ERROR_NULL;
    }

    if (self->size + 1 == self->capacity) {
        if (_str_grow_if_needed(self) == STR_ERROR_ALLOCATION) {
            return STR_ERROR_ALLOCATION;
        }
    }

    self->array[self->size++] = c;
    
    return STR_OK;
}

str_status_t str_append_str(str_t* self, const str_t* other) {
    if (self == NULL || other == NULL) {
        return STR_ERROR_NULL;
    }

    if (self->size + other->size >= self->capacity) {
        if (_str_grow_if_needed(self) == STR_ERROR_ALLOCATION) {
            return STR_ERROR_ALLOCATION;
        }
    }

    memcpy(self->array + self->size, other->array, other->size);
    self->size += other->size;

    return STR_OK;
}

str_status_t str_prepend_char(str_t* self, char c) {
    return str_insert_char(self, 0, c);
}

str_status_t str_prepend_str(str_t* self, const str_t* other) {
    return str_insert_str(self, 0, other);
}

str_status_t str_insert_char(str_t* self, size_t index, char c) {
    if (self == NULL) {
        return STR_ERROR_NULL;
    }

    if (index > self->size) {
        return STR_ERROR_BOUNDS;
    }

    if (self->size + 1 == self->capacity) {
        if (_str_grow_if_needed(self) == STR_ERROR_ALLOCATION) {
            return STR_ERROR_ALLOCATION;
        }
    }

    char out;
    char in = c;
    for (size_t i = index; i <= self->size; i++) {
        out = self->array[i];
        self->array[i] = in;
        in = out;
    }

    self->size++;

    return STR_OK;
}

str_status_t str_insert_str(str_t* self, size_t index, const str_t* other) {
    if (self == NULL || other == NULL) {
        return STR_ERROR_NULL;
    }

    if (index > self->size) {
        return STR_ERROR_BOUNDS;
    }

    if (other->size == 0) {
        return STR_OK;
    }

    if (self->size + other->size >= self->capacity) {
        if (_str_grow_if_needed(self) == STR_ERROR_ALLOCATION) {
            return STR_ERROR_ALLOCATION;
        }
    }
    
    if (index == self->size) {
        return str_append_str(self, other);
    }

    size_t chars_after_insert = self->size - index;
    char buffer[chars_after_insert];
    memcpy(buffer, self->array + index, chars_after_insert);

    memcpy(self->array + index, other->array, other->size);

    memcpy(self->array + index + other->size, buffer, chars_after_insert);

    self->size += other->size;

    return STR_OK;
}