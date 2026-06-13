#include "hset.h"

typedef struct vec_t_ vec_t;

/// @brief intitializes destination as a vector containing all elements of self (order cannot be guaranteed)
/// @param self the hset to copy
/// @param destination the vec_t to write to (must be uninitialized)
/// @return 
hset_status_t hset_to_vec(const hset_t* self, vec_t* destination);

/// @brief adds all items of source to self. Duplicates in source are ignored.
/// @param self the hset to add to
/// @param source the vec with items to add
/// @return 
hset_status_t hset_add_all(hset_t* self, const vec_t* source);

/// @brief removes all items of source from self. If an item in source is not contained in self (or if it was a duplicate)
///     it has no effect
/// @param self the hset to remove from
/// @param source the vec with items to remove
/// @return 
hset_status_t hset_remove_all(hset_t* self, const vec_t* source);

/// @brief checks if all items in source are also contained in self
/// @param self the hset to check
/// @param source the vec with the items to look for
/// @return false if self and source aren't compatible or if at least one item in source is not contained in self
bool hset_contains_all(const hset_t* self, const vec_t* source);

/// @brief checks if at least one item in source is also contained in self
/// @param self the hset to check
/// @param source the vec with the items to look for
/// @return false if self and source aren't compatible or if no item in source is contained in self
bool hset_contains_any(const hset_t* self, const vec_t* source);
