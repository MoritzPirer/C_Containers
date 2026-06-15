#include <string.h>

#include "../../inc/hset/hset_iter.h"
#include "hset_internal.h"

/// @brief return the indext of the first non-empty entry after start, or start if already on the last entry
size_t _hset_get_next_used_entry(const hset_t* hset, size_t start) {
    unsigned char entry[hset->boosted_size];
    for (size_t index = start; index < hset->capacity; index++) {
        _hset_copy_from_nth_index(entry, hset, index);

        hset_item_state_t item_state = HSET_STATE(entry); 
        if (item_state == HSET_USED) {
            return index;
        }
    }

    return start;
}

size_t _hset_iter_is_valid(const hset_iter_t* iter) {
    return iter->iterator_version == iter->hset->iterator_version;
}

hset_status_t hset_iter_init(hset_t* hset, hset_iter_t* iter) {
    if (hset == NULL || iter == NULL) {
        return HSET_ERROR_NULL;
    }

    iter->hset = hset;
    iter->iterator_version = hset->iterator_version;

    if (HSET_STATE(hset->table) == HSET_USED) {
        iter->current_index = 0;
    }
    else {
        size_t first_element = _hset_get_next_used_entry(hset, 0);
        if (first_element == 0) {
            // empty hset
            return HSET_ERROR_INVALID;
        }

        iter->current_index = first_element;
    }
    
   return HSET_OK;
}

bool hset_iter_has_next(const hset_iter_t* iter) {
    if (iter == NULL) {
        return false;
    }

    if (!_hset_iter_is_valid(iter)) {
        return false;
    }

    return _hset_get_next_used_entry(iter->hset, iter->current_index) != iter->current_index;
}

hset_iter_status_t hset_iter_get(const hset_iter_t* iter, void* destination) {
    if (iter == NULL || destination == NULL) {
        return HSET_ITER_NULL;
    }

    if (!_hset_iter_is_valid(iter)) {
        return HSET_ITER_INVALID;
    }

    unsigned char entry[iter->hset->boosted_size];
    _hset_copy_from_nth_index(entry, iter->hset, iter->current_index);

    if (HSET_STATE(entry) == HSET_USED) {
        memcpy(destination, HSET_PAYLOAD(entry), iter->hset->item_size);
        return HSET_ITER_OK;
    }

    return HSET_ITER_INVALID;
}

hset_iter_status_t hset_iter_next(hset_iter_t* iter) {
    if (iter == NULL) {
        return HSET_ITER_NULL;
    }

    if (!_hset_iter_is_valid(iter)) {
        return HSET_ITER_INVALID;
    }

    size_t next_entry = _hset_get_next_used_entry(iter->hset, iter->current_index);

    if (next_entry == iter->current_index) {
        return HSET_ITER_END;
    }

    iter->current_index = next_entry;

    return HSET_ITER_OK;
}

hset_iter_status_t hset_iter_remove(hset_iter_t* iter) {
    if (iter == NULL) {
        return HSET_ITER_NULL;
    }

    if (!_hset_iter_is_valid(iter)) {
        return HSET_ITER_INVALID;
    }

    unsigned char entry[iter->hset->boosted_size];
    _hset_copy_from_nth_index(entry, iter->hset, iter->current_index);

    if (HSET_STATE(entry) == HSET_DELETED) {
        // was already deleted
        return HSET_ITER_INVALID;
    }

    memcpy(entry, HSET_DELETED, sizeof(hset_item_state_t));
    _hset_copy_to_nth_index(iter->hset, entry, iter->current_index);

    // invalidate all other iterators of this hset
    iter->iterator_version++;
    iter->hset->iterator_version++;

    return HSET_ITER_OK;
}

void hset_iter_debug(const hset_iter_t* iter) {
    if (iter == NULL) {
        return;
    }

    printf("=== Hset Iter Debug ===\n");
    printf("hset_iter at %x\n", iter);
    printf("at internal index %d\n", iter->current_index);
    printf("iterator_version: %d\n", iter->iterator_version);

    printf("iterating over following hset at %x\n", iter->hset);
    hset_debug(iter->hset);

    printf("=== Hset Iter ===\n");
}