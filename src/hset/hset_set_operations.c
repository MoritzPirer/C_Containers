#include "../../inc/hset/hset.h"
#include "hset_internal.h"
#include <stdint.h>
#define UCHAR_TO_VOID_PTR(i) (void*)(uintptr_t)(i)

bool hset_is_compatible_with(const hset_t* a, const hset_t* b) {
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

    return true;
}

hset_status_t hset_union(const hset_t* a, const hset_t* b, hset_t* result) {
    if (a == NULL || b == NULL || result == NULL) {
        return HSET_ERROR_NULL;
    }

    if (!hset_is_compatible_with(a, b)) {
        return HSET_ERROR_INVALID;
    }

    hset_status_t status = hset_copy(a, result);
    if (status != HSET_OK) {
        return status;
    }

    for (size_t index = 0; index < b->capacity; index++) {
        unsigned char entry[b->boosted_size];
        hset_copy_from_nth_index(entry, b, index);

        hset_item_state_t item_state = *((hset_item_state_t*) entry); 
        if (item_state == HSET_EMPTY) {
            continue;
        }

        status = hset_add(result, UCHAR_TO_VOID_PTR(entry[sizeof(hset_item_state_t)]));
        if (status != HSET_OK) {
            return status;
        }
    }

    return HSET_OK;
}

hset_status_t hset_intersection(const hset_t* a, const hset_t* b, hset_t* result) {
    if (a == NULL || b == NULL || result == NULL) {
        return HSET_ERROR_NULL;
    }

    if (!hset_is_compatible_with(a, b)) {
        return HSET_ERROR_INVALID;
    }

    hset_status_t status = hset_init(result, a->size, a->item_size, a->comparison);

    if (status != HSET_OK) {
        return status;
    }

    for (size_t index = 0; index < a->capacity; index++) {
        unsigned char entry[a->boosted_size];
        hset_copy_from_nth_index(entry, a, index);

        hset_item_state_t item_state = *((hset_item_state_t*) entry); 
        if (item_state == HSET_EMPTY) {
            continue;
        }

        if (!hset_contains(b, entry + sizeof(hset_item_state_t))) {
            continue;
        }

        status = hset_add(result, entry + sizeof(hset_item_state_t));
        if (status != HSET_OK) {
            return status;
        }
    }

    return HSET_OK;
}

hset_status_t hset_difference(const hset_t* a, const hset_t* b, hset_t* result) {
    if (a == NULL || b == NULL || result == NULL) {
        return HSET_ERROR_NULL;
    }

    if (!hset_is_compatible_with(a, b)) {
        return HSET_ERROR_INVALID;
    }

    hset_status_t status = hset_init(result, a->size, a->item_size, a->comparison);

    if (status != HSET_OK) {
        return status;
    }

    for (size_t index = 0; index < a->capacity; index++) {
        unsigned char entry[a->boosted_size];
        hset_copy_from_nth_index(entry, a, index);

        hset_item_state_t item_state = *((hset_item_state_t*) entry); 
        if (item_state == HSET_EMPTY) {
            continue;
        }

        if (hset_contains(b, entry + sizeof(hset_item_state_t))) {
            continue;
        }

        status = hset_add(result, entry + sizeof(hset_item_state_t));
        if (status != HSET_OK) {
            return status;
        }
    }

    return HSET_OK;
   
}

hset_status_t hset_symmetric_difference(const hset_t* a, const hset_t* b, hset_t* result) {
    if (a == NULL || b == NULL || result == NULL) {
        return HSET_ERROR_NULL;
    }

    if (!hset_is_compatible_with(a, b)) {
        return HSET_ERROR_INVALID;
    }

    hset_difference(a, b, result);

    for (size_t index = 0; index < b->capacity; index++) {
        unsigned char entry[b->boosted_size];
        hset_copy_from_nth_index(entry, b, index);

        hset_item_state_t item_state = *((hset_item_state_t*) entry); 
        if (item_state == HSET_EMPTY) {
            continue;
        }

        if (hset_contains(a, UCHAR_TO_VOID_PTR(entry[sizeof(hset_item_state_t)]))) {
            continue;
        }

        hset_status_t status = hset_add(result, UCHAR_TO_VOID_PTR(entry[sizeof(hset_item_state_t)]));
        if (status != HSET_OK) {
            return status;
        }
    }

    return HSET_OK;
}

bool hset_is_subset_of(const hset_t* a, const hset_t* b) {
    if (!hset_is_compatible_with(a, b)) {
        return false;
    }

    if (a->size == 0) { //empty set is subset of everything
        return true;
    }

    for (size_t index = 0; index < a->capacity; index++) {
        unsigned char entry[a->boosted_size];
        hset_copy_from_nth_index(entry, a, index);

        hset_item_state_t item_state = *((hset_item_state_t*) entry); 
        if (item_state != HSET_USED) {
            continue;
        }

        if (!hset_contains(b, UCHAR_TO_VOID_PTR(entry[sizeof(hset_item_state_t)]))) {
            return false;
        }
    }

    return true;
}

bool hset_is_superset_of(const hset_t* a, const hset_t* b) {
    return hset_is_subset_of(b, a);
}