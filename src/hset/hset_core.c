#include <string.h>
#include <memory.h>
#include <stdlib.h>

#include "../../inc/hset/hset.h"
#include "hset_internal.h"
#include <stdio.h>

/// @brief calculats a hash value from an item
/// @param value a pointer to the item to hash
/// @param num_bytes the length of the item to hash
/// @return the fnv-1a hash of the item
size_t hset_hash(void* value, size_t num_bytes) {
    size_t hash = 1469598103934665603ULL; 
    for (size_t i = 0; i < num_bytes; i++) {
        hash ^= ((unsigned char*) value)[i];
        hash *= 1099511628211ULL;
    }
    return hash;
}

/// @brief calculates the load factor, i.e. the percentage of the hash set that is filled
/// @param self the hset to calculate the load factor of
/// @return the load factor
static inline float hset_load_factor(const hset_t* self) {
    return ((float) self->size / (float) self->capacity);
}

hset_status_t hset_rehash(hset_t* self, size_t old_capacity) {
    void* temp = calloc(self->capacity, self->boosted_size);
    if (temp == NULL) {
        return HSET_ERROR_ALLOCATION;
    }

    for (size_t index = 0; index < old_capacity; index++) {
        unsigned char entry[self->boosted_size];
        hset_copy_from_nth_index(entry, self, index);

        hset_item_state_t item_state = HSET_STATE(entry); 
        if (item_state != HSET_USED) { 
            continue;
        }
        
        size_t hash = hset_hash(HSET_PAYLOAD(entry), self->item_size);
        
        for (size_t offset = 0; offset < self->capacity; offset++) {
            size_t hashed_index = (hash + offset) % self->capacity;

            unsigned char* dest_slot = (unsigned char*)temp + (hashed_index * self->boosted_size);
            hset_item_state_t dest_state = HSET_STATE(dest_slot);

            if (dest_state != HSET_USED) {
                memcpy(dest_slot, entry, self->boosted_size);
                break;
            }
        }
    }

    free(self->table);
    self->table = temp;
    return HSET_OK;
}

/// @brief if the load factor is high enough, the hash table size is doubled and all elements are rehashed
/// @param self the hset to grow
/// @return HSET_OK if everything worked or HSET_ERROR_ALLOCATION if resizing failed, 
hset_status_t hset_grow_if_needed(hset_t* self) {
    if (hset_load_factor(self) < HSET_LOAD_FACTOR_GROW) {
        return HSET_OK;
    }

    size_t old_capacity = self->capacity;
    self->capacity <<= 1;

    return hset_rehash(self, old_capacity);
}

/// @brief if the load factor is low enough, the hash table size is halved and all elements are rehashed
/// @param self the hset to shrink
/// @return HSET_OK if everything worked or HSET_ERROR_ALLOCATION if resizing failed
hset_status_t hset_shrink_if_needed(hset_t* self) {
    if (hset_load_factor(self) > HSET_LOAD_FACTOR_SHRINK) {
        return HSET_OK;
    }

    size_t old_capacity = self->capacity;
    self->capacity >>= 1;

    return hset_rehash(self, old_capacity);
}

hset_status_t hset_add(hset_t* self, void* source) {
    if (self == NULL || source == NULL) {
        return HSET_ERROR_NULL;
    }

    hset_status_t result = hset_grow_if_needed(self);
    if (result != HSET_OK) {
        return result;
    }

    size_t hash = hset_hash(source, self->item_size);
    for (size_t offset = 0; offset < self->capacity; offset++) {
        size_t hashed_index = (hash + offset) % self->capacity;

        unsigned char entry[self->boosted_size];
        hset_copy_from_nth_index(entry, self, hashed_index);

        hset_item_state_t item_state = HSET_STATE(entry); 

        if ((hset_item_state_t) item_state != HSET_USED) {
            // free or deleted slot -> can be used
            entry[0] = HSET_USED;
            memcpy(HSET_PAYLOAD(entry), source, self->item_size);
            hset_copy_to_nth_index(self, entry, hashed_index);
            break;
        }
        else if (self->comparison(source, HSET_PAYLOAD(entry), self->item_size)) {
            return HSET_OK; // already contained
        }
    }

    self->size++;
    return HSET_OK;
}

hset_status_t hset_remove(hset_t* self, void* source) {
    if (self == NULL || source == NULL) {
        return HSET_ERROR_NULL;
    }

    size_t hash = hset_hash(source, self->item_size);
    for (size_t offset = 0; offset < self->capacity; offset++) {
        size_t hashed_index = (hash + offset) % self->capacity;

        unsigned char entry[self->boosted_size];
        hset_copy_from_nth_index(entry, self, hashed_index);

        hset_item_state_t item_state = HSET_STATE(entry); 

        // not contained
        if (item_state != HSET_USED) {
            return HSET_OK; 
        }

        if (self->comparison(source, &entry[sizeof(hset_item_state_t)], self->item_size)) {
            entry[0] = HSET_DELETED;
            hset_copy_to_nth_index(self, entry, hashed_index);
            break;
        }
    }

    self->size--;

    hset_shrink_if_needed(self);

    return HSET_OK;
}

bool hset_contains(const hset_t* self, void* item) {
    if (self == NULL || item == NULL) {
        return false;
    }

    size_t hash = hset_hash(item, self->item_size);

    for (size_t offset = 0; offset < self->capacity; offset++) {
        size_t hashed_index = (hash + offset) % self->capacity; 

        unsigned char entry[self->boosted_size];
        hset_copy_from_nth_index(entry, self, hashed_index);
        hset_item_state_t item_state = HSET_STATE(entry);
        
        // not contained
        if (item_state != HSET_USED) {
            return false; 
        }

        if (self->comparison(item, HSET_PAYLOAD(entry), self->item_size)) {
            return true;
        }
    }

    return false;
}

size_t hset_size(const hset_t* self) {
    if (self == NULL) {
        return (size_t) -1;
    }

    return self->size;
}

bool hset_is_empty(const hset_t* self) {
    if (self == NULL) {
        return true;
    }

    return self->size == 0;
}

hset_status_t hset_clear(hset_t* self) {
    if (self == NULL) {
        return HSET_ERROR_NULL;
    }

    memset(self->table, 0, self->boosted_size * self->capacity);
    self->size = 0;

    return HSET_OK;
}

bool hset_equals(const hset_t* a, const hset_t* b) {
    hset_t temp;

    if (hset_symmetric_difference(a, b, &temp) != HSET_OK) {
        hset_destroy(&temp);
        return false;
    }  

    bool result = hset_is_empty(&temp);
    hset_destroy(&temp);

    return result;
}