#ifndef VEC_INTEGRATION_H
#define VEC_INTEGRATION_H

#include "vec.h"

typedef struct hset_t_ hset_t;

/// @brief initialites destination as an hset containing all unique elements of self (i.e. duplicates are lost)
/// @param self the vector to source from
/// @param destination the hset to write to (must be uninitialized)
/// @param hset_comparision a function that compares two elements for equality
/// @return 
vec_status_t vec_to_hset(const vec_t* self, hset_t* destination,
    bool (*hset_comparison)(const void* a, const void* b, size_t item_size));

#endif //VEC_INTEGRATION_H