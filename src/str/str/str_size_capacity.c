#include "../../../inc/str/str.h"
#include "str_internal.h"
#include "../../utility.h"

size_t str_size(const str_t* self) {
    if (self == NULL) {
        return (size_t) -1;
    }

    return self->size;
}

size_t str_capacity(const str_t* self) {
    if (self == NULL) {
        return (size_t) -1;
    }

    return self->capacity;

}

bool str_is_empty(const str_t* self) {
    if (self == NULL) {
        return true;
    }

    return self->size == 0;
}


str_status_t str_reserve(str_t* self, size_t elements_to_reserve) {
    if (self == NULL) {
        return STR_ERROR_NULL;
    }

    if (elements_to_reserve <= self->capacity) {
        return STR_OK;
    }

    return _str_realloc(self, next_power_of_two(elements_to_reserve));
}

str_status_t str_shrink(str_t* self) {
    if (self == NULL) {
        return STR_ERROR_NULL;
    }

    if (self->capacity == self->size) {
        return STR_OK;
    }

    return _str_realloc(self, self->size);
}