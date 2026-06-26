#include <stdlib.h>
#include <string.h>

#include "../../../inc/str/str.h"
#include "../../utility.h"

str_status_t str_init(str_t* self, size_t initial_capacity) {
    if (self == NULL) {
        return STR_ERROR_NULL;
    }

    self->size = 0;
    self->capacity = MAX(next_power_of_two(initial_capacity), STR_MIN_CAPACITY);
    self->array = calloc(self->capacity, 1);

    if (self->array == NULL) {
        return STR_ERROR_ALLOCATION;
    }

    return STR_OK;
}

str_status_t str_init_from(str_t* self, const char* source, size_t len) {
    str_status_t result = str_init(self, len);

    if (result != STR_OK) {
        return result;
    }

    memcpy(self->array, source, len);

    return STR_OK;
}

str_status_t str_init_repeat(str_t* self, char c, size_t count) {
    str_status_t result = str_init(self, count);

    if (result != STR_OK) {
        return result;
    }

    self->size = count;

    if (count > 0) {
        memset(self->array, c, count);
    }

    return STR_OK;
}

str_status_t str_destroy(str_t* self) {
    if (self == NULL) {
        return STR_ERROR_NULL;
    }

    free(self->array);
    self->array = NULL;
    self->capacity = 0;
    self->size = 0;

    return STR_OK;
}

str_status_t str_copy(const str_t* original, str_t* copy) {
    if (original == NULL || copy == NULL) {
        return STR_ERROR_NULL;
    }

    copy->array = malloc(original->capacity);
    if (copy->array == NULL) {
        return STR_ERROR_ALLOCATION;
    }

    memcpy(copy->array, original->array, original->capacity);
    copy->size = original->size;
    copy->capacity = original->capacity;

    return STR_OK;
}

str_status_t str_swap(str_t* self, str_t* other) {
    if (self == NULL || other == NULL) {
        return STR_ERROR_NULL;
    }

    if (self == other) {
        return STR_OK; // swap with self
    }

    swap(&(self->capacity), &(other->capacity));
    swap(&(self->size), &(other->size));

    char* temp = self->array;
    self->array = other->array;
    other->array = temp;

    return STR_OK;
}