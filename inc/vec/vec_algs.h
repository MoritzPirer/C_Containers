///
/// @file: vec_algs.h
/// @description: Non-essential functions built on top of the core vec features
///     that implement common algorithms
///
/// @date: 2026-01-06
/// @author: Morith Pirer
///

#ifndef VEC_ALGS_H
#define VEC_ALGS_H

#include <stddef.h>

#include "vec.h"

/// @brief takes a pointer to an element of a vec. Should return true if the element
///     matches a criteria and false otherwise. data can optionally be used for additional data
///     Should be a constant time operation to uphold the time complexity specified for each algorithm
typedef bool (*vec_condition_t)(const void* element, const void* data);

/// @brief compares two elements of the type that the vec contains. Should return any negative
///     value if a < b, any positive value if a > b and 0 if a == b. Should be a constant time operation
///     to uphold the time complexity specified for each algorithm
typedef int (*vec_ordering_t)(const void* a, const void* b);

/// @brief used by vecTransform. May change the element in-place. Should not change the dataype of
///     the vec, although that is not enforced as long as the element size stays the same. data can
///     be used to pass in additional date (for easier reuse of functions)
typedef void (*vec_transformation_t)(void* element, const void* data);
///
/// DEFAULTS
///

/// @brief simple equality comparison for find algorithms (among others).
///     Usable if the data type of the vec can (meaningfully) be converted to a size_t (i.e. most built-in types)
/// @return true if element == data
bool vec_default_condition(const void* element, const void* data);

/// @brief simple ordering for algorithms that need to compare elements.
///     Usable if the data type of the vec can (meaningfully) be converted to a size_t (i.e. most built-in types)
/// @return a negative value if a < b, a positive value if a > b, 0 if a == b
int vec_default_ordering(const void* a, const void* b);

///
/// SEARCHING
///

/// @brief find the index of the first element for which condition returns true
///     and write it to index_buffer
/// @param self the vec to search
/// @param condition a function that takes returns true if the element is the element searched for
/// @param index_buffer where to write the index
/// @param data any additional data for the condition function (see example usage).
///     Can pass NULL if not needed
/// @return VEC_ERROR_NULL if self, key or index_buffer is NULL,
///     VEC_NOT_FOUND if key was not found
///     VEC_OK if key was found (only then is the value at index_buffer valid)
/// @complexity O(n)
vec_status_t vec_find_first(vec_t* self, vec_condition_t condition,
                         size_t* index_buffer, const void* data);

/// @brief find the index of the last element for which condition returns true
///     and write it to index_buffer
/// @param self the vec to search
/// @param condition a function that takes an element returns true if the element is the element searched for
/// @param index_buffer where to write the index
/// @param data any additional data for the condition function (see example usage).
///     Can pass NULL if not needed
/// @return VEC_ERROR_NULL if self, key or index_buffer is NULL,
///     VEC_NOT_FOUND if key was not found
///     VEC_OK if key was found (only then is the value at index_buffer valid)
/// @complexity O(n)
vec_status_t vec_find_last(vec_t* self, vec_condition_t condition,
                         size_t* index_buffer, const void* data);

/// @brief checks if the vec contains at least one item for which condition returns true
/// @param self the vec to search
/// @param condition a function that takes an element of the vec and returns true or false
/// @param data any additional data for the condition function. Can pass NULL if not needed
/// @return true if self contains an element for chich condition returns true, false otherwise
/// @complexity O(n)
bool vec_contains(vec_t self, vec_condition_t condition, const void* data);

/// @brief performs a binary search to find the index of key. Caller is responsible for
///     ensuring that the vec has no duplicates and is sorted in ascending order. Otherwise, the
///     behavior is undefined
/// @param self the vec to search in
/// @param vec_ordering a function that compares two elements of the type contained by the vec
///     should return 0 if they are equal, any value < 0 if the first argument is less
///     or any value > 0 if the first argument is greater
/// @param index_buffer where to write the index if it is found
/// @param key the element to search for
/// @return VEC_ERROR_NULL if self, key or index_buffer is NULL,
///     VEC_NOT_FOUND if key was not found
///     VEC_OK if key was found (only then is the value at index_buffer valid)
/// @complexity O(log(n))
vec_status_t vec_binary_search(vec_t* self, vec_ordering_t vec_ordering,
                            size_t* index_buffer, const void* key);

///
/// ITERATING
///

/// @brief check if condition is true for at least one element of the vec
/// @param self the vec to check
/// @param condition the condition to apply to each element
/// @param data any additional data needed by condition (can pass NULL if not needed)
/// @return true if condition is true for at least one element, false otherwise
/// @param self the vec to reverse
/// @complexity O(n)
bool vec_any(vec_t self, vec_condition_t condition, const void* data);

/// @brief check if condition is true for all elements of the vec
/// @param self the vec to check
/// @param condition the condition to apply to each element
/// @param data any additional data needed by condition (can pass NULL if not needed)
/// @return true if condition is true for every element, false otherwise
/// @param self the vec to reverse
/// @complexity O(n)
bool vec_all(vec_t self, vec_condition_t condition, const void* data);

/// @brief check if condition is false for all elements of the vec
/// @param self the vec to check
/// @param condition the condition to apply to each element
/// @param data any additional data needed by condition (can pass NULL if not needed)
/// @return true if condition is false for every element, false otherwise
/// @complexity O(n)
bool vec_none(vec_t self, vec_condition_t condition, const void* data);

/// @brief reverses the elements of the vec in-place
/// @param self the vec to reverse
/// @complexity O(n)
void vec_reverse(vec_t* self);

/// @brief creates a new vec of all elements of self for which condition returns true
/// @param self the array to use as an input
/// @param condition the condition to check for all elements of self
/// @param filtered where to write the filtered result. Must be uninitialized.
/// @param data any additional data needed by condition. can pass NULL if not needed.
/// @return VEC_ERROR_NULL if self or filtered was NULL
///     VEC_ERROR_ALLOCATION if creating or resizing filtered failed,
///     VEC_OK if everything worked (only then is filtered valid)
/// @complexity O(n)
vec_status_t vec_filter(vec_t* self, vec_condition_t condition,
                       vec_t* filtered, const void* data);

/// @brief applies the given transformation function to each element of the vec.
/// @param self the vec to transform
/// @param transformation the transformation to apply. Should modify the element in-place.
///     Should not change the data type (although that is not technically enforced). Should not touch
///     more bytes than the one element uses.
/// @param data any additional data needed by transformation. Can pass NULL if not needed.
/// @return VEC_ERROR_NULL if self was null, VEC_OK otherwise
/// @complexity O(n)
vec_status_t vec_transform(vec_t* self, vec_transformation_t transformation, const void* data);

///
/// RANGES
///

/// @brief generates a range from start (inclusive) to stop (exclusive), increasing by step each time
/// @param self where to write the range. Must be uninitialized
/// @param start the first value in the range
/// @param stop the first value outside of the range
/// @param step how much to increase or decrease between elements. If negative,
///     start must be greater than stop. May not be 0
/// @return VEC_ERROR_NULL if self is NULL
///     VEC_ERROR_INVALID if step is 0 or step direction is away from stop point
///     VEC_ERROR_ALLOCATION if creating the vec failed,
///     VEC_OK if everything worked (only then is self valid)
vec_status_t vec_range_from_to_step(vec_t* self, size_t start, size_t stop, int step);

/// @brief generates a range from start (inclusive) to stop (exclusive), increasing by 1 each time
/// @param self where to write the range. Must be uninitialized
/// @param start the first value in the range
/// @param stop the first value outside of the range
/// @return VEC_ERROR_NULL if self is NULL
///     VEC_ERROR_INVALID if start > stop (use vec_range_from_to_step with
///     a negative step if you want a decrementing range)
///     VEC_ERROR_ALLOCATION if creating the vec failed,
///     VEC_OK if everything worked (only then is self valid)
vec_status_t vec_range_from_to(vec_t* self, size_t start, size_t stop);

/// @brief generates a range from 0 (inclusive) to stop (exclusive), increasing by step each time
/// @param self where to write the range. Must be uninitialized
/// @param stop the first value outside of the range
/// @param step how much to increase or decrease between elements. May not be negative
/// @return VEC_ERROR_NULL if self is NULL
///     VEC_ERROR_INVALID if step is <= 0
///     VEC_ERROR_ALLOCATION if creating the vec failed,
///     VEC_OK if everything worked (only then is self valid)
vec_status_t vec_range_to_step(vec_t* self, size_t stop, int step);

/// @brief generates a range from 0 (inclusive) to stop (exclusive), increasing by 1 each time
/// @param self where to write the range. Must be uninitialized
/// @param stop the first value outside of the range
/// @return VEC_ERROR_NULL if self is NULL
///     VEC_ERROR_ALLOCATION if creating the vec failed,
///     VEC_OK if everything worked (only then is self valid)
vec_status_t vec_range_to(vec_t* self, size_t stop);

///
/// SET OPERATIONS
///

/// @brief checks if the vec is unique, i.e. has no duplicate elements. Caller is
///     responsible for ensuring vec is sorted (ascending or descending), otherwise behavior is
///     undefined
/// @param self the vec to check
/// @param vec_ordering a function that can compare two elements of the vec's datatype
/// @return true if all elements are unique, false if there is at least one duplicate value
/// @complexity O(n)
bool vec_is_unique(vec_t self, vec_ordering_t vec_ordering);

/// @brief create a new vec consisting of only the unique elements of self. Caller is responsible
///     for ensuring self is sorted (ascending or descending), otherwise behavior is undefined
/// @param self the vec to make unique
/// @param vec_ordering a function that can compare two elements of the vec's datatype
/// @param unique where to write the result. must not be initialized to avoid memory leaks.
/// @return VEC_ERROR_NULL if self or unique is NULL
///     VEC_ERROR_INVALID if self was not sorted
///     VEC_ERROR_ALLOCATION if creating the new vec failed,
///     VEC_OK if everything went fine (only then is unique valid)
/// @complexity O(n)
vec_status_t vec_get_unique(vec_t* self, vec_ordering_t vec_ordering, vec_t* unique);

/// @brief create a new vec consisting of the elements that both left and right contain.
///     Caller is responsible for ensuring both are sorted (either both ascending or both descending)
/// @param left a sorted darry (may contain duplicates)
/// @param right a vec sorted the same way and containing the same type as left (may contain duplicates)
/// @param vec_ordering a function that can compare the elements of the vecs' datatype
/// @param intersection where to write the result. Must not be initialized to avoid memory leaks.
/// @return VEC_ERROR_NULL if left, right or intersection is NULL
///     VEC_ERROR_INVALID if left or right was not sorted (or if the were not sorted the same way)
///     VEC_ERROR_ALLOCATION if creating the new vec failed,
///     VEC_OK if everything went fine (only then is intersection valid)
/// @complexity O(n + m)
vec_status_t vec_get_intersection(vec_t* left, vec_t* right,
                                vec_ordering_t vec_ordering, vec_t* intersection);

/// @brief create a new vec consisting of the elements contained by left and / or right.
///     Caller is responsible for ensuring both are sorted (either both ascending or both descending)
/// @param left a sorted vec (may contain duplicates)
/// @param right a vec sorted the same way and containing the same type as left (may contain duplicates)
/// @param vec_ordering a function that compare the elements of the vecs' datatype
/// @param union_elements where to write the result. Must not be initialized to avoid memory leaks
/// @return VEC_ERROR_NULL if left, right or union_elements is NULL
///     VEC_ERROR_INVALID if left or right was not sorted (or if the were not sorted the same way)
///     VEC_ERROR_ALLOCATION if creating the new vec failed,
///     VEC_OK if everything went fine (only then is union_elements valid)
/// @complexity O(n + m)
vec_status_t vec_get_union(vec_t* left, vec_t* right,
                         vec_ordering_t vec_ordering, vec_t* union_elements);

///
/// SORTING
///

/// @brief sorts the vec using stdlib's qsort().
/// @param self the vec to sort
/// @param vec_ordering the comparison function to use
/// @return VEC_ERROR_NULL if self is NULL, VEC_OK otherwise
vec_status_t vec_sort(vec_t* self, vec_ordering_t vec_ordering);

/// @brief checks if self is sorted in ascending order (each element is >= the previous element)
/// @param self the vec to check
/// @param vec_ordering a function that compares two elements of the vec and returns
///     a negative value if the first value is smaller, a positive one if the second is smaller,
///     or 0 if they are equal
/// @return true if the vec is sorted, false otherwise
/// @complexity O(n)
bool vec_is_sorted_asc(vec_t self, vec_ordering_t vec_ordering);

/// @brief checks if self is sorted in descending order (each element is <= the previous element)
/// @param self the vec to check
/// @param vec_ordering a function that compares two elements of the vec and returns
///     a negative value if the first value is smaller, a positive one if the second is smaller,
///     or 0 if they are equal
/// @return true if the vec is sorted, false otherwise
/// @complexity O(n)
bool vec_is_sorted_desc(vec_t self, vec_ordering_t vec_ordering);

/// @brief checks if two vecs holding the same dataytpe are equal with regard to vec_ordering
/// @param left one of the vecs to compare
/// @param right the other vec ot compare
/// @param vec_ordering a function that can compare two elements of the vecs' datatype.
///     should return 0 for equal elements
/// @return true if the vecs are equal, false otherwise
/// @complexity O(n)
bool vec_equals(vec_t left, vec_t right, vec_ordering_t vec_ordering);

#endif // VEC_ALGS_H
