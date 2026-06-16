#include "../../../inc/str/str.h"
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