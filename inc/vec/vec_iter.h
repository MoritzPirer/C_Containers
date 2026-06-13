#ifndef VEC_ITER_H
#define VEC_ITER_H

#include "vec.h"

typedef struct vec_iter_t_ {
    vec_t* vec;
    size_t current_index;
    size_t iterator_version;
    bool is_on_deleted;
} vec_iter_t;

typedef enum vec_iter_status_t_ {
    VEC_ITER_OK = 0,    // action was successful
    VEC_ITER_NULL,      // a parameter was null
    VEC_ITER_END,       // iterator is at the end; cannot move in that direction
    VEC_ITER_INVALID,   // iterator was invalidated
    VEC_ITER_ALLOCATION // resize caused by insert failed
} vec_iter_status_t;

///
/// Creation
///

/// @brief initializes iter as an iterator of vec, starting at index
/// @param vec the vec to be iterated over
/// @param iter the iterator to initialize
/// @param index where in the vec the iterator should start
/// @return VEC_OK if the iter was successfully initialized, VEC_ERROR_NULL if vec or iter were NULL
///     VEC_ERROR_BOUNDS if index is out of bounds for vec
vec_status_t vec_iter_init(vec_t* vec, vec_iter_t* iter, size_t index); 

/// @brief initializes iter as an iterator of vec, starting on the first element (index 0)
/// @param vec the vec to be iterated over
/// @param iter the iterator to initialize
/// @return VEC_OK if the iter was successfully initialized, VEC_ERROR_NULL if vec or iter were NULL
///     VEC_ERROR_BOUNDS if the vec is empty
vec_status_t vec_iter_init_first(vec_t* vec, vec_iter_t* iter);

/// @brief initializes iter as an iterator of vec, starting on the last element
/// @param vec the vec to be iterated over
/// @param iter the iterator to initialize
/// @return VEC_OK if the iter was successfully initialized, VEC_ERROR_NULL if vec or iter were NULL
///     VEC_ERROR_BOUNDS if the vec is empty
vec_status_t vec_iter_init_last(vec_t* vec, vec_iter_t* iter);

///
/// Lookahead
///

/// @brief checks if the iterator can move forward
/// @param iter the iterator to check
/// @return true if the iterator can move forward, false if it cannot (or it was invalidated)
bool vec_iter_has_next(vec_iter_t* iter);

/// @brief checks if the iterator can move backward
/// @param iter the iterator to check
/// @return true if the iterator can move backward, false if it cannot (or it was invalidated)
bool vec_iter_has_previous(vec_iter_t* iter);

///
/// Reading 
///

/// @brief copies the element the iterator is on to destination. Equivalent to calling vec_get with
/// the iterator's index If vec_iter_remove was called, this function will fail until the iterator is moved
///     (with vec_iter_next or vec_iter_previous)
/// @param iter the iterator to get from
/// @param destination where to write the element
/// @return VEC_ITER_INVALID if the iterator was invalidated or vec_remove was called before,
///     VEC_ITER_NULL if iter or destination was NULL, VEC_ITER_OK if everything worked
vec_iter_status_t vec_iter_get(vec_iter_t* iter, void* destination);

///
/// Moving
///

/// @brief moves the iterator to the next element
/// @param iter the iterator to move
/// @return VEC_ITER_NULL if iter was NULL, VEC_ITER_INVALID if the iterator was invalidated,
///     VEC_ITER_END if the iterator was already on the end, VEC_ITER_OK if the operation succeeded
vec_iter_status_t vec_iter_next(vec_iter_t* iter);

/// @brief moves the iterator to the previous element
/// @param iter the iterator to move
/// @return VEC_ITER_NULL if iter was NULL, VEC_ITER_INVALID if the iterator was invalidated,
///     VEC_ITER_END if the iterator was already on the end, VEC_ITER_OK if the operation succeeded
vec_iter_status_t vec_iter_previous(vec_iter_t* iter);

///
/// Modifying
///

/// @brief sets the element the iterator is on to the value at source. Equivalent to calling vec_set with the iterator's index
///     if vec_iter_remove was called, this function will fail until the iterator is moved (with vec_iter_next
///     or vec_itter_previous)
/// @param iter the iterator to set at
/// @param destination where to read the element from
/// @return VEC_ITER_INVALID if the iterator was invalidated or vec_iter_remove was used,
///     VEC_ITER_NULL if iter or destination was NULL, VEC_ITER_OK if everything worked
vec_iter_status_t vec_iter_set(vec_iter_t* iter, void* source);

/// @brief removes the element the iterator is currently on. When called, subsequent calls to 
///     vec_iter_remove, vec_iter_get and vec_iter_set will fail until the iterator moves. All other iterators
///     are invalidated.
/// @param iter the iterator to remove with
/// @return VEC_ITER_NULL if iter was null, VEC_ITER_INVALID if the iterator was invalidated or remove was already called
///     VEC_ITER_OK if removing succeeded
vec_iter_status_t vec_iter_remove(vec_iter_t* iter);

/// @brief inserts the value pointed at by source into the vector *before* the current position (to allow forward iterating
///     without double-parsing elements). Using this function while iterating in reverse is not recommended.
///     invalidates all other iterators of this vec.
/// @param iter the iter to use as a reference point for the insertion
/// @param source a pointer to the value to insert
/// @return VEC_ITER_NULL if iter or source is NULL, VEC_ITER_INVALID if the iterator was invalidated, VEC_ITER_ALLOCATION
///     if the insertion caused a resizing that failed, VEC_ITER_OK otherwise
vec_iter_status_t vec_iter_insert(vec_iter_t* iter, void* source);

#endif // VEC_ITER_H
