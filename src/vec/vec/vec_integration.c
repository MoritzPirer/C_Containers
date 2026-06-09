
#include "../vec_internal.h"
#include "../../../inc/hset/hset.h"

vec_status_t vec_to_hset(const vec_t* self, hset_t* destination,
    bool (*hset_comparison)(void* a, void* b, size_t item_size)) {

    (void) self;
    (void) destination;
    (void) hset_comparison;

    return VEC_OK;
}