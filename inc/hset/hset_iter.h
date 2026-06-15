#ifndef HSET_ITER_H
#define HSET_ITER_H

#include "hset.h"

typedef struct hset_iter_t_ {
    hset_t* hset;
    size_t current_index;
    size_t iterator_version;
} hset_iter_t;

typedef enum hset_iter_status_t_ {
    HSET_ITER_OK = 0,    // action was successful
    HSET_ITER_NULL,      // a parameter was null
    HSET_ITER_END,       // iterator is at the end; cannot move in that direction
    HSET_ITER_INVALID    // iterator was invalidated
} hset_iter_status_t;

/// @brief initializes iter as an iterator of hset
/// @param hset the hset to iterate over
/// @param iter the iterator to initialize
/// @return HSET_ERROR_NULL if hset or iter was NULL, HSET_ERROR_INVALID if the set is empty, HSET_OK if 
///     initialization succeeded
hset_status_t hset_iter_init(hset_t* hset, hset_iter_t* iter);

/// @brief checks if the iterator can move
/// @param iter the iterator to check
/// @return false if iter cannot move anymore, if it was invalidated or if it was NULL
bool hset_iter_has_next(const hset_iter_t* iter);

/// @brief reads the entry the iterator is on to destination
/// @param iter the iterator to read from
/// @param destination where to write the element
/// @return HSET_ITER_NULL if iter or destination was NULL, HSET_ITER_INVALID if iter was invalidated
///     or remove has been called since the last move, HSET_ITER_OK if reading worked (only then is destination valid)
hset_iter_status_t hset_iter_get(const hset_iter_t* iter, void* destination);

/// @brief moves the iterator to the next element
/// @param iter the iterator to move
/// @return HSET_ITER_NULL if iter was NULL, HSET_ITER_INVALID if the iterator was invalidated,
///     HSET_ITER_END if iter was already at the end, HSET_ITER_OK if moving was successful
hset_iter_status_t hset_iter_next(hset_iter_t* iter);

/// @brief removes the element the iterator is currently on. Blocks hset_iter_get until the iterator is
///     moved with hset_iter_next. Invalidates all other iterators of this hset.
/// @param iter the iterator to remove at
/// @return HSET_ITER_NULL if iter was NULL, Hset_ITER_INVALID if the iterator was invalidated or 
///     the entry was already deleted, HSET_ITER_OK if deletion was successful
hset_iter_status_t hset_iter_remove(hset_iter_t* iter);

///

void hset_iter_debug(const hset_iter_t* iter);

#endif // HSET_ITER_H