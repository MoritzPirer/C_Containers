#include <string.h>

#include "../../inc/hset/hset.h"

float hset_load_factor(hset_t* self) {
    return ((float) self->size / (float) self->capacity);
}


hset_status_t hset_grow(hset_t* self) {
    (void) self;
    return HSET_OK;
}

hset_status_t hset_shrink(hset_t* self) {
    (void) self;
    return HSET_OK;
}

/// @brief calculats a hash value from an item
/// @param value a pointer to the item to hash
/// @param num_bytes the length of the item to hash
/// @return the fnv1a hash of the item
size_t hset_hash(void* value, size_t num_bytes) {
    size_t hash = 1469598103934665603ULL; 
    for (size_t i = 0; i < num_bytes; i++) {
        hash ^= ((unsigned char*) value)[i];
        hash *= 1099511628211ULL;
    }
    return hash;
}

hset_status_t hset_add(hset_t* self, void* source) {
    if (self == NULL || source == NULL) {
        return HSET_ERROR_NULL;
    }

    //TODO GROW IF NECESSARY (alpha >= 0.75)

    size_t hash = hset_hash(source, self->item_size);
    for (size_t offset = 0; offset < self->capacity; offset++) {
        size_t hashed_index = (hash + offset) % self->capacity;

        unsigned char entry[self->item_size + sizeof(hset_item_state_t)];
        memcpy(entry, (void *)((char *)self->table + (hashed_index * self->boosted_size)), self->boosted_size);

        hset_item_state_t item_state = *((hset_item_state_t*) entry); 

        if ((hset_item_state_t) item_state != HSET_USED) {
            entry[0] = HSET_USED;
            memcpy(&entry[sizeof(hset_item_state_t)], source, self->item_size);
            memcpy((void *)((char *)self->table + (hashed_index * self->boosted_size)), entry, self->boosted_size);
            break;
        }
        else if (self->comparison(source, &entry[sizeof(hset_item_state_t)], self->item_size)) {
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

        unsigned char entry[self->item_size + sizeof(hset_item_state_t)];
        memcpy(entry, (void *)((char *)self->table + (hashed_index * self->boosted_size)), self->boosted_size);

        hset_item_state_t item_state = *((hset_item_state_t*) entry); 

        // not contained
        if (item_state != HSET_USED) {
            return HSET_OK; 
        }

        if (self->comparison(source, &entry[sizeof(hset_item_state_t)], self->item_size)) {
            entry[0] = HSET_DELETED;
            memcpy((void *)((char *)self->table + (hashed_index * self->boosted_size)), entry, self->boosted_size);
            break;
        }
    }

    //TODO SHRINK IF NECESSARY (alpha <= 0.25)
    self->size--;

    return HSET_OK;
}

bool hset_contains(const hset_t* self, void* item) {
    if (self == NULL || item == NULL) {
        return false;
    }

    size_t hash = hset_hash(item, self->item_size);

    for (size_t offset = 0; offset < self->capacity; offset++) {
        size_t hashed_index = (hash + offset) % self->capacity; 

        unsigned char entry[self->item_size + sizeof(hset_item_state_t)];
        memcpy(entry, (void *)((char *)self->table + (hashed_index * self->boosted_size)), self->boosted_size);
        hset_item_state_t item_state = *((hset_item_state_t*) entry);
        
        // not contained
        if (item_state != HSET_USED) {
            return false; 
        }

        if (self->comparison(item, &entry[sizeof(hset_item_state_t)], self->item_size)) {
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