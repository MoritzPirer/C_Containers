#include "../../../inc/str/str_algs.h"
#include "../../utility.h"
#include "../str/str_internal.h"

#include <ctype.h>
#include <string.h>

void str_to_uppercase(str_t* self) {
    if (self == NULL) {
        return;
    }

    for (size_t i = 0; i < self->size; i++) {
        self->array[i] = toupper(self->array[i]);
    }
}

void str_to_lowercase(str_t* self) {
    if (self == NULL) {
        return;
    }

    for (size_t i = 0; i < self->size; i++) {
        self->array[i] = tolower(self->array[i]);
    }
}

void str_reverse(str_t* self) {
    if (self == NULL) {
        return;
    }

    for (size_t i = 0; i < self->size >> 1; i++) {
        char temp = self->array[i];
        self->array[i] = self->array[self->size - i - 1];
        self->array[self->size - i - 1] = temp;
    }
}

str_status_t str_trim_left(str_t* self) {
    if (self == NULL) {
        return STR_ERROR_NULL;
    } 

    size_t i = 0;
    for (; i < self->size; i++) {
        if (!isblank(self->array[i])) {
            break;
        }
    }

    const size_t surviving_chars = self->size - i;
    char temp[surviving_chars];
    memcpy(temp, self->array + i, surviving_chars);
    memcpy(self->array, temp, surviving_chars);
    self->size = surviving_chars;

    if (_str_is_less_than_half_full) {
        return _str_realloc(self, next_power_of_two(self->size));
    }

    return STR_OK;
}

str_status_t str_trim_right(str_t* self) {
    if (self == NULL) {
        return STR_ERROR_NULL;
    } 

    size_t i = 0;
    for (; i < self->size; i++) {
        if (!isblank(self->array[self->size - i - 1])) {
            break;
        }
    }

    self->size = self->size - i;

    if (_str_is_less_than_half_full(self)) {
        return _str_realloc(self, next_power_of_two(self->size));
    }

    return STR_OK;
}

str_status_t str_trim(str_t* self) {
    str_status_t result = str_trim_left(self);
    if (result != STR_OK) {
        return result;
    }

    return str_trim_right(self);
}

str_status_t str_collapse_repeated(str_t* self, char c) {
    if (self == NULL) {
        return STR_ERROR_NULL;
    } 

    size_t write_index = 0;

    bool previous_was_seperator = false;
    size_t new_size = self->size;

    for (size_t read = 0; read < self->size; read++) {
        if (self->array[read] == c) {
            if (previous_was_seperator) {
                new_size--;
                continue;
            }

            previous_was_seperator = true;
        }
        else {
            previous_was_seperator = false;
        }
        self->array[write_index] = self->array[read];
        self->size = new_size;

        write_index++;
    }

    if (_str_is_less_than_half_full) {
        return _str_realloc(self, next_power_of_two(self->size));
    }

    return STR_OK;
}