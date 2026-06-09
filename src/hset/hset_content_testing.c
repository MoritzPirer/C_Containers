#include <string.h>
#include <memory.h>
#include <stdlib.h>

#include "../../inc/hset/hset.h"
#include "hset_internal.h"


bool hset_default_condition(const void* element, const void* data) {
    return (*(size_t* )element == *(size_t* )data);
}

bool hset_any(hset_t* self, hset_condition_t condition, const void* data) {
    if (self == NULL) {
        return false;
    }

    unsigned char entry[self->boosted_size];
    for (size_t index = 0; index < self->capacity; index++) {
        hset_copy_from_nth_index(entry, self, index);

        hset_item_state_t item_state = *((hset_item_state_t*) entry); 
        if (item_state == HSET_EMPTY) {
            continue;
        }

        if (condition(entry, data)) {
            return true;
        }
    }

    return false;
} 

bool hset_all(hset_t* self, hset_condition_t condition, const void* data) {
    if (self == NULL) {
        return false;
    }

    unsigned char entry[self->boosted_size];
    for (size_t index = 0; index < self->capacity; index++) {
        hset_copy_from_nth_index(entry, self, index);

        hset_item_state_t item_state = *((hset_item_state_t*) entry); 
        if (item_state == HSET_EMPTY) {
            continue;
        }

        if (!condition(entry, data)) {
            return false;
        }
    }

    return true;
}

bool hset_none(hset_t* self, hset_condition_t condition, const void* data) {
    if (self == NULL) {
        return false;
    }

    unsigned char entry[self->boosted_size];
    for (size_t index = 0; index < self->capacity; index++) {
        hset_copy_from_nth_index(entry, self, index);

        hset_item_state_t item_state = *((hset_item_state_t*) entry); 
        if (item_state == HSET_EMPTY) {
            continue;
        }

        if (condition(entry, data)) {
            return false;
        }
    }

    return true;
}
 
hset_status_t hset_filter(hset_t* self, hset_condition_t condition, hset_t* filtered, const void* data) {
    if (self == NULL || filtered == NULL) {
        return HSET_ERROR_NULL;
    }

    if (hset_init(filtered, 0, self->item_size, self->comparison) != HSET_OK) {
        return HSET_ERROR_ALLOCATION;
    }

    unsigned char entry[self->boosted_size];
    for (size_t index = 0; index < self->capacity; index++) {
        hset_copy_from_nth_index(entry, self, index);

        hset_item_state_t item_state = *((hset_item_state_t*) entry); 
        if (item_state == HSET_EMPTY) {
            continue;
        }

        if (condition(entry, data)) {
            hset_status_t result = hset_add(filtered, entry);
            if (result != HSET_OK) {
                return result;
            }
        }
    }

    return HSET_OK;
}