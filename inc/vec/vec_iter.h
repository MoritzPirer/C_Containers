#ifndef VEC_ITER_H
#define VEC_ITER_H

#include "vec.h"

typedef struct vec_iter_t_ {
    vec_t* vec;
    size_t current_index;
    size_t iterator_version;
} vec_iter_t;

typedef enum vec_iter_status_t_ {
    VEC_ITER_OK = 0,    // action was successful
    VEC_ITER_NULL,      // a parameter was null
    VEC_ITER_END,       // iterator is at the end; cannot move in that direction
    VEC_ITER_INVALID    // iterator was invalidated
} vec_iter_status_t;

/// @brief initializes iter as an iterator of vec, starting at index
/// @param vec the vec to be iterated over
/// @param iter the iterator to initialize
/// @param index where in the vec the iterator should start
/// @return VEC_OK if the iter was successfully initialized, VEC_ERROR_NULL if vec or iter were NULL
///     VEC_ERROR_BOUNDS if index is out of bounds for vec
vec_status_t vec_iter_init(vec_t* vec, vec_iter_t* iter, size_t index); 

/// @brief moves the iterator to the next element and copies that element to destination
/// @param iter the iterator to move
/// @param destination where to write the new element (the one the iterator is on AFTER moving)
///     pass NULL to disregard the element
/// @return VEC_ITER_INVALID if the iterator was invalidated,
///     VEC_ITER_NULL if iter was NULL, VEC_ITER_END if the iterator was already at the end,
///     VEC_ITER_OK if the iterator moved successfully. Only in the last case is destination a valid value
vec_iter_status_t vec_iter_next(vec_iter_t* iter, void* destination);

/// @brief moves the iterator to the previous element and copies that element to destination
/// @param iter the iterator to move
/// @param destination where to write the new element (the one the iterator is on AFTER moving)
///     pass NULL to disregard the element
/// @return VEC_ITER_INVALID if the iterator was invalidated,
///     VEC_ITER_NULL if iter was NULL, VEC_ITER_END if the iterator was already at the end,
///     VEC_ITER_OK if the iterator moved successfully. Only in the last case is destination a valid value
vec_iter_status_t vec_iter_previous(vec_iter_t* iter, void* destination);

/// @brief copies the element the iterator is on to destination. Equivalent to calling vec_get with the iterator's index
/// @param iter the iterator to get from
/// @param destination where to write the element
/// @return VEC_ITER_INVALID if the iterator was invalidated, VEC_ITER_NULL if iter or destination was NULL,
///     VEC_ITER_OK if everything worked
vec_iter_status_t vec_iter_get(vec_iter_t* iter, void* destination);

/// @brief sets the element the iterator is on to the value at source. Equivalent to calling vec_set with the iterator's index
/// @param iter the iterator to set at
/// @param destination where to read the element from
/// @return VEC_ITER_INVALID if the iterator was invalidated, VEC_ITER_NULL if iter or destination was NULL,
///     VEC_ITER_OK if everything worked
vec_iter_status_t vec_iter_set(vec_iter_t* iter, void* source);

/// @brief checks if the iterator can move forward
/// @param iter the iterator to check
/// @return true if the iterator can move forward, false if it cannot (or it was invalidated)
bool vec_iter_has_next(vec_iter_t* iter);

/// @brief checks if the iterator can move backward
/// @param iter the iterator to check
/// @return true if the iterator can move backward, false if it cannot (or it was invalidated)
bool vec_iter_has_previous(vec_iter_t* iter);

#endif // VEC_ITER_H