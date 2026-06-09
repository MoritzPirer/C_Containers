///
/// @file: hset.h
/// @description: an implementation of an unordered set using a hash table
///
/// @date: 2025-12-31
/// @author: Moritz Pirer
///

#ifndef HSET_H
#define HSET_H

#include <stddef.h>
#include <stdbool.h>

/// @brief for internal use; indicates if an entry in the hash table is free
typedef enum hset_item_state_t {
    HSET_EMPTY = 0,
    HSET_USED = 1,
    HSET_DELETED = 2,
} hset_item_state_t;

/// @brief a function that compares two items of the type stored in the hash set; return
///     true if they are equal, false otherwise
/// @param item_size the size of the item stored in the table
typedef bool (*hset_comparison_t)(void* a, void* b, size_t item_size);

#define HSET_MIN_SIZE 4
#define HSET_LOAD_FACTOR_GROW 0.75f
#define HSET_LOAD_FACTOR_SHRINK 0.25f

typedef struct hset_t_ {
    void* table;
    size_t size; // items in set
    size_t capacity; // table size
    size_t item_size; // size of item
    size_t boosted_size; // sizeof item + metadata
    hset_comparison_t comparison;
} hset_t;

typedef enum hset_status_t_ {
    HSET_OK = 0,
    HSET_ERROR_ALLOCATION,
    HSET_ERROR_NULL,
    HSET_ERROR_INVALID
} hset_status_t;

///
/// OWNERSHIP
///

/// @brief initialize the given hset_t object
/// @param self the hset to initialize
/// @param initial_size how many elements should be usable right away
/// @param element_size the size of a single element
/// @param comparison a function that compares two elements and returns true if they are equal. Pass NULL to
///     default to comparing the bits of the items (may not be ideal for objects with pointers)
/// @return HSET_OK if everything is fine, HSET_ERROR_ALLOC if the memory allocation failed,
///     HSET_ERROR_INVALID if element size is 0, HSET_ERROR_NULL if self is NULL
hset_status_t hset_init(hset_t* self, size_t initial_size, size_t element_size, hset_comparison_t comparison);

/// @brief destroy the hset. using it after this function is undefined behaviour
/// @param self the hset to destroy
/// @return HSET_ERROR_NULL if self is NULL, HSET_ERROR_OK otherwise
hset_status_t hset_destroy(hset_t* self);

hset_status_t hset_copy(const hset_t* self, hset_t* copy);

///
/// CORE FUNCTIONS
///

/// @brief add the given item to the hset. No effect if the item is already contained
/// @param self the set to add to
/// @param source the item to add
/// @return HSET_ERROR_ALLOC if resizing failed, HSET_ERROR_NULL if self or source were NULL, HSET_OK otherwise
hset_status_t hset_add(hset_t* self, void* source);

/// @brief remove the given item from the hset. No effect if the item not contained
/// @param self the set to remove from
/// @param source the item to remvoe
/// @return HSET_ERROR_ALLOC if resizing failed, HSET_ERROR_NULL if self or source were NULL, HSET_OK otherwise
hset_status_t hset_remove(hset_t* self, void* source);

/// @brief check if the set contains the given item
/// @param self the set to check
/// @param item the item to look for
/// @return true if the item is contained, false otherwise
bool hset_contains(const hset_t* self, void* item);

/// @param self the set to check. Is set is NULL, -1 is returned
/// @return the number of items in the set.
size_t hset_size(const hset_t* self);

/// @param self the set to check
/// @return true if the set has 0 items in it or if self is NULL, false otherwise
bool hset_is_empty(const hset_t* self);

/// @brief removes all elements from the set
/// @param self the set to clear
/// @return HSET_ERROR_NULL if self is NULL, HSET_OK otherwise
hset_status_t hset_clear(hset_t* self);

/// @brief checks if two hsets contain the same elements
/// @return false if the hsets cannot be compared or have different elements
bool hset_equals(const hset_t* a, const hset_t* b);

///
/// SET OPERATIONS
///

/// @brief initalizes result as a set containing all elements contained in at least one of the other sets
/// @param a the first set
/// @param b the second set
/// @param result an UNINITIALIZED hset. passing an initialized hset will lose data / leak memory
/// @return HSET if everything worked, otherwise an error value corresponding to the problem
hset_status_t hset_union(const hset_t* a, const hset_t* b, hset_t* result);

/// @brief initalizes result as a set containing all elements contained in both of the other sets
/// @param a the first set
/// @param b the second set
/// @param result an UNINITIALIZED hset. passing an initialized hset will lose data / leak memory
/// @return HSET if everything worked, otherwise an error value corresponding to the problem
hset_status_t hset_intersection(const hset_t* a, const hset_t* b, hset_t* result);

/// @brief initializes result as a set containing all elements contained in a, but not in b.
/// @param a the set to include
/// @param b the set do exclude
/// @param result an UNINITIALIZED hset. passing an initialized hset will lose data / leak memory
/// @return HSET if everything worked, otherwise an error value corresponding to the problem
hset_status_t hset_difference(const hset_t* a, const hset_t* b, hset_t* result);

/// @brief initializes result as a set containing all elements contained in either a or b, but not both
/// @param a the first set
/// @param b the second set
/// @param result an UNINITIALIZED hset. passing an initialized hset will lose data / leak memory
/// @return HSET if everything worked, otherwise an error value corresponding to the problem
hset_status_t hset_symmetric_difference(const hset_t* a, const hset_t* b, hset_t* result);

/// @brief checks if a is a subset of (or equal to) b. If a and b have different item sizes or comparision functions,
///     false is returned (datatype missmatch). Equivalent ot hset_is_superset_of(b, a);
/// @param a the subset
/// @param b the superset
/// @return true if every item of a is contained in b, false if a has items that b does not have or if
///     a and b are not comparable 
bool hset_is_subset_of(const hset_t* a, const hset_t* b);

/// @brief checks if a is a superset of (or equal to) b. If a and b have different item sizes or comparison function,
///     false is returned (datatype missmatch). Equivalent to hset_is_subset_of(b, a);
/// @param a the superset
/// @param b the subset
/// @return true if every item of b is contained in a, false if b has items that a does not have or if 
///     a and b are not comparable
bool hset_is_superset_of(const hset_t* a, const hset_t* b);

///
/// INTEGRATION
///

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
hset_status_t hset_add_all(hset_t* self, vec_t* source);

/// @brief removes all items of source from self. If an item in source is not contained in self (or if it was a duplicate)
///     it has no effect
/// @param self the hset to remove from
/// @param source the vec with items to remove
/// @return 
hset_status_t hset_remove_all(hset_t* self, vec_t* source);

/// @brief checks if all items in source are also contained in self
/// @param self the hset to check
/// @param source the vec with the items to look for
/// @return false if self and source aren't compatible or if at least one item in source is not contained in self
bool hset_contains_all(hset_t* self, vec_t* source);

/// @brief checks if at least one item in source is also contained in self
/// @param self the hset to check
/// @param source the vec with the items to look for
/// @return false if self and source aren't compatible or if no item in source is contained in self
bool hset_contains_any(hset_t* self, vec_t* source);

#endif // HSET_H
