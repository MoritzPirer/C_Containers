#include "../../inc/hset/hset.h"
#include "hset_internal.h"
#include "../../inc/vec/vec.h"

hset_status_t hset_to_vec(const hset_t* self, vec_t* destination) {
    if (self == NULL || destination == NULL) {
        return HSET_ERROR_NULL;
    }

    vec_status_t init_status = vec_init(destination, self->size, self->item_size);
    if (init_status == VEC_ERROR_ALLOCATION) {
        return HSET_ERROR_ALLOCATION;
    }

    for (size_t index = 0; index < self->capacity; index++) {
        unsigned char entry[self->boosted_size];
        hset_copy_from_nth_index(entry, self, index);

        hset_item_state_t item_state = *((hset_item_state_t*) entry); 
        if (item_state == HSET_EMPTY) {
            continue;
        }

        vec_status_t status = vec_push_back(destination, entry);
        if (status == VEC_ERROR_ALLOCATION) {
            return HSET_ERROR_ALLOCATION;
        }
    }

    return HSET_OK;
}

hset_status_t hset_add_all(hset_t* self, vec_t* source) {
    if (self == NULL || source == NULL) {
        return HSET_ERROR_NULL;
    }

    if (self->item_size != source->item_size) {
        return HSET_ERROR_INVALID;
    }

    char element[self->item_size];
    for (size_t i = 0; i < vec_size(source); i++) {
        vec_get(source, i, element);
        hset_status_t result = hset_add(self, element);
        if (result != HSET_OK) {
            return result;
        }
    }

    return HSET_OK;
}

hset_status_t hset_remove_all(hset_t* self, vec_t* source) {
    if (self == NULL || source == NULL) {
        return HSET_ERROR_NULL;
    }

    if (self->item_size != source->item_size) {
        return HSET_ERROR_INVALID;
    }

    char element[self->item_size];
    for (size_t i = 0; i < vec_size(source); i++) {
        vec_get(source, i, element);
        hset_status_t result = hset_remove(self, element);
        if (result != HSET_OK) {
            return result;
        }
    }
    
    return HSET_OK;
}

bool hset_contains_all(hset_t* self, vec_t* source) {
    if (self == NULL || source == NULL) {
        return false;
    }

    if (self->item_size != source->item_size) {
        return false;
    }

    char element[self->item_size];
    for (size_t i = 0; i < vec_size(source); i++) {
        vec_get(source, i, element);
        if (!hset_contains(self, element)) {
            return false;
        }
    }
    
    return true;
}

bool hset_contains_any(hset_t* self, vec_t* source) {
    if (self == NULL || source == NULL) {
        return false;
    }

    if (self->item_size != source->item_size) {
        return false;
    }

    char element[self->item_size];
    for (size_t i = 0; i < vec_size(source); i++) {
        vec_get(source, i, element);
        if (hset_contains(self, element)) {
            return true;
        }
    }
    
    return false;
}