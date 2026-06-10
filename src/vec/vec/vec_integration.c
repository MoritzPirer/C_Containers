
#include "../vec_internal.h"
#include "../../../inc/hset/hset.h"

vec_status_t vec_to_hset(const vec_t* self, hset_t* destination,
    bool (*hset_comparison)(const void* a, const void* b, size_t item_size)) {

    if (self == NULL || destination == NULL) {
        return VEC_ERROR_NULL;
    }

    if (hset_init(destination, self->size_used, self->item_size, hset_comparison) != HSET_OK) {
        return VEC_ERROR_ALLOCATION;
    }

    hset_status_t result = hset_add_all(destination, self);
    if (result == HSET_ERROR_ALLOCATION) {
        return VEC_ERROR_ALLOCATION;
    } 

    return VEC_OK;
}