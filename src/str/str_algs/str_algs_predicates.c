#include "../../../inc/str/str_algs.h"
#include "../../utility.h"
#include <ctype.h>
#include <stdbool.h>

bool str_equals(const str_t* a, const str_t* b) {
    if (a == NULL || b == NULL) {
        return false;
    }

    if (a->size != b->size) {
        return false;
    }

    for (size_t i = 0; i < a->size; i++) {
        if (a->array[i] != b->array[i]) {
            return false;
        }
    }

    return true;
}

bool str_equals_case(const str_t* a, const str_t* b) {
    if (a == NULL || b == NULL) {
        return false;
    }

    if (a->size != b->size) {
        return false;
    }

    for (size_t i = 0; i < a->size; i++) {
        if (toupper(a->array[i]) != toupper(b->array[i])) {
            return false;
        }
    }

    return true;
}

int str_compare(const str_t* a, const str_t* b) {
    if (a == NULL || b == NULL) {
        return 0; //TODO: decide if another sentinel value is better
    }

    if (a->size != b->size) {
        return 0; //TODO: decide if another sentinel value is better
    }

    for (size_t i = 0; i < a->size; i++) {
        if (a->array[i] == b->array[i]) {
            continue;
        }
        else if ((unsigned char) a->array[i] > (unsigned char) b->array[i]) {
            return 1;
        }
        else {
            return -1;
        }
    }

    return 0;
}

int str_compare_case(const str_t* a, const str_t* b) {
    if (a == NULL || b == NULL) {
        return 0; //TODO: decide if another sentinel value is better
    }

    if (a->size != b->size) {
        return 0; //TODO: decide if another sentinel value is better
    }

    for (size_t i = 0; i < a->size; i++) {
        if (a->array[i] == b->array[i]) {
            continue;
        }

        else if ((unsigned char) toupper(a->array[i]) > (unsigned char) toupper(b->array[i])) {
            return 1;
        }
        else {
            return -1;
        }
    }

    return 0;
}

bool str_starts_with_char(const str_t* self, char c) {
    if (self == NULL) {
        return false;
    }

    if (self->size == 0) {
        return false;
    }

    return self->array[0] == c;
}

bool str_starts_with_str(const str_t* self, const str_t* prefix) {
    if (self == NULL) {
        return false;
    }

    if (self->size < prefix->size) {
        return false;
    }

    for (size_t i = 0; i < prefix->size; i++) {
        if (self->array[i] != prefix->array[i]) {
            return false;
        }
    }
    
    return true;
}

bool str_ends_with_char(const str_t* self, char c) {
    if (self == NULL) {
        return false;
    }

    if (self->size == 0) {
        return false;
    }

    return self->array[self->size - 1] == c;
}

bool str_ends_with_str(const str_t* self, const str_t* suffix) {
    if (self == NULL) {
        return false;
    }

    if (self->size < suffix->size) {
        return false;
    }

    size_t offset = self->size - suffix->size;
    for (size_t i = 0; i < suffix->size; i++) {
        if (self->array[offset + i] != suffix->array[i]) {
            return false;
        }
    }
    
    return true;
}

bool str_is_uppercase(const str_t* self) {
    if (self == NULL) {
        return false;
    }

    for (size_t i = 0; i < self->capacity; i++) {
        if (islower(self->array[i])) {
            return false;
        }
    }

    return true;
}

bool str_is_lowercase(const str_t* self) {
    if (self == NULL) {
        return false;
    }

    for (size_t i = 0; i < self->capacity; i++) {
        if (isupper(self->array[i])) {
            return false;
        }
    }

    return true;
}

bool str_is_numeric(const str_t* self) {
    if (self == NULL) {
        return false;
    }

    for (size_t i = 0; i < self->capacity; i++) {
        if (!isnumber(self->array[i])) {
            return false;
        }
    }

    return true;
}

bool str_is_alphabetic(const str_t* self) {
    if (self == NULL) {
        return false;
    }

    for (size_t i = 0; i < self->capacity; i++) {
        if (!isalpha(self->array[i])) {
            return false;
        }
    }

    return true;
}

bool str_is_alphanumeric(const str_t* self) {
    if (self == NULL) {
        return false;
    }

    for (size_t i = 0; i < self->capacity; i++) {
        if (!isalnum(self->array[i])) {
            return false;
        }
    }

    return true;
}