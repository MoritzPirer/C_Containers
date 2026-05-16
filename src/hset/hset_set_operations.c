#include "../../inc/hset/hset.h"

hset_status_t hset_union(const hset_t* a, const hset_t* b, hset_t* result);

hset_status_t hset_intersection(const hset_t* a, const hset_t* b, hset_t* result);

hset_status_t hset_difference(const hset_t* a, const hset_t* b, hset_t* result);

hset_status_t hset_symmetric_difference(const hset_t* a, const hset_t* b, hset_t* result);

bool hset_is_subset_of(const hset_t* a, const hset_t* b) {
    if (a == NULL || b == NULL) {
        return false;
    }

    if (a->item_size != b->item_size) {
        return false;
    }

    if (a->boosted_size != b->boosted_size) {
        return false;
    }

    if (a->comparison != b->comparison) {
        return false;
    }

    if (a->size == 0) { //empty set is subset of everything
        return;
    }

    for (size_t index = 0; index < a->capacity; index++) {
        unsigned char entry[a->item_size + sizeof(hset_item_state_t)];
        memcpy(entry, (void *)((char *)a->table + (index * a->boosted_size)), a->boosted_size);

        hset_item_state_t item_state = *((hset_item_state_t*) entry); 
        if (item_state != HSET_USED) {
            continue;
        }

        if (!hset_contains(b, entry[sizeof(hset_item_state_t)])) {
            return false;
        }
    }

    return true;
}

bool hset_is_superset_of(const hset_t* a, const hset_t* b) {
    return hset_is_subset_of(b, a);
}