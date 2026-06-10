#include <string.h>

#include "../../../inc/vec/vec_iter.h"

static inline bool vec_iter_is_valid(vec_iter_t* iter) {
    return iter->iterator_version == iter->vec->iterator_version;
}

vec_status_t vec_iter_init(vec_t* vec, vec_iter_t* iter, size_t index) {
    if (vec == NULL || iter == NULL) {
        return VEC_ERROR_NULL;
    }

    if (index >= vec->size) {
        return VEC_ERROR_BOUNDS;
    }

    iter->vec = vec;
    iter->current_index = index;
    iter->iterator_version = vec->iterator_version;

    return VEC_OK;
}

vec_iter_status_t vec_iter_next(vec_iter_t* iter, void* destination) {
    if (iter == NULL) {
        return VEC_ITER_NULL;
    }

    if (!vec_iter_is_valid(iter)) {
        return VEC_ITER_INVALID;
    }

    if (iter->current_index == iter->vec->size - 1) {
        return VEC_ITER_END;
    }

    iter->current_index++;
    if (destination != NULL) {
        vec_get(iter->vec, iter->current_index, destination);
    }

    return VEC_ITER_OK;
}

vec_iter_status_t vec_iter_previous(vec_iter_t* iter, void* destination) {
    if (iter == NULL) {
        return VEC_ITER_NULL;
    }

    if (!vec_iter_is_valid(iter)) {
        return VEC_ITER_INVALID;
    }

    if (iter->current_index == 1) {
        return VEC_ITER_END;
    }

    iter->current_index--;
    
    if (destination != NULL) {
        vec_get(iter->vec, iter->current_index, destination);
    }

    return VEC_ITER_OK;
}

vec_iter_status_t vec_iter_get(vec_iter_t* iter, void* destination) {
    if (iter == NULL || destination == NULL) {
        return VEC_ITER_NULL;
    }

    if (!vec_iter_is_valid(iter)) {
        return VEC_ITER_INVALID;
    }

    vec_get(iter->vec, iter->current_index, destination);

    return VEC_ITER_OK;
}

vec_iter_status_t vec_iter_set(vec_iter_t* iter, void* source) {
    if (iter == NULL || source == NULL) {
        return VEC_ITER_NULL;
    }

    if (!vec_iter_is_valid(iter)) {
        return VEC_ITER_INVALID;
    }

    vec_set(iter->vec, iter->current_index, source);

    return VEC_ITER_OK;
}

bool vec_iter_has_next(vec_iter_t* iter) {
    if (iter == NULL) {
        return false;
    }
    
    if (!vec_iter_is_valid(iter)) {
        return false;
    }

    return (iter->current_index < iter->vec->size - 1);
}

bool vec_iter_has_previous(vec_iter_t* iter) {
    if (iter == NULL) {
        return false;
    }
    
    if (!vec_iter_is_valid(iter)) {
        return false;
    }

    return (iter->current_index > 0);
}