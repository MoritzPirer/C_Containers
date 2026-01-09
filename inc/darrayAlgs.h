///
/// @file: darrayAlgs.hpp
/// @description: Non-essential functions built on top of the core darray features
///     that implement common algorithms 
///
/// @date: 2026-01-06
/// @author: Morith Pirer
///

#ifndef DARRAY_ALGS_H
#define DARRAY_ALGS_H

#include <stddef.h>

#include "darray.h"

/// @brief takes a pointer to an element of a darray. Should return true if the element
///     matches a criteria and false otherwise. data can optionally be used for additional data
///     Should be a constant time operation to uphold the time complexity specified for each algorithm
typedef bool (*darrayCondition) (const void* element, const void* data);

/// @brief compares two elements of the type that the darray contains. Should return any negative
///     value if a < b, any positive value if a > b and 0 if a == b. Should be a constant time operation
///     to uphold the time complexity specified for each algorithm
typedef int (*darrayOrdering) (const void* a, const void* b);

///
/// DEFAULTS
///

/// @brief simple equality comparison for find algorithms (among others).
///     Usable if the data type of the darray can (meaningfully) be convertet to a size_t (i.e. most built-in types)
/// @return true if element == data
bool darrayDefaultCondition(const void* element, const void* data);

/// @brief simple ordering for algorithms that need to compare elements.
///     Usable if the data type of the darray can (meaningfully) be converted to a size_t (i.e. most built-in types)
/// @return a negative value if a < b, a positive value if a > b, 0 if a == b
int darrayDefaultOrdering(const void* a, const void* b);

///
/// SEARCHING
///

/// @brief find the index of the first element for which condition returns true
///     and write it to index_buffer
/// @param self the darray to search
/// @param condition a function that takes returns true if the element is the element searched for 
/// @param index_buffer where to write the index
/// @param data any additional data for the condition function (see example usage).
///     Can pass NULL if not needed
/// @return DARRAY_ERROR_NULL if self, key or index_buffer is NULL,
///     DARRAY_NOT_FOUND if key was not found
///     DARRAY_OK if key was found (only then is the value at index_buffer valid)
/// @complexity O(n)
DarrayStatus darrayFindFirst(const Darray* self, darrayCondition condition,
    size_t* index_buffer, const void* data);

/// @brief find the index of the last element for which condition returns true
///     and write it to index_buffer
/// @param self the darray to search
/// @param condition a function that takes an element returns true if the element is the element searched for 
/// @param index_buffer where to write the index
/// @param data any additional data for the condition function (see example usage).
///     Can pass NULL if not needed 
/// @return DARRAY_ERROR_NULL if self, key or index_buffer is NULL,
///     DARRAY_NOT_FOUND if key was not found
///     DARRAY_OK if key was found (only then is the value at index_buffer valid)
/// @complexity O(n)
DarrayStatus darrayFindLast(const Darray* self, darrayCondition condition,
    size_t* index_buffer, const void* data);

/// @brief checks if the darray contains at least one item for which condition returns true
/// @param self the darray to search
/// @param condition a function that takes an element of the darray and returns true or false
/// @param data any additional data for the condition function. Can pass NULL if not needed
/// @return true if self contains an element for chich condition returns true, false otherwise
/// @complexity O(n)
bool darrayContains(Darray self, darrayCondition condition, const void* data);

/// @brief performs a binary search to find the index of key. Caller is responsible for
///     ensuring that the darray has no duplicates and is sorted in ascending order. Otherwise, the
///     behavior is undefined
/// @param self the darray to search in
/// @param darray_ordering a function that compares two elements of the type contained by the darray
///     should return 0 if they are equal, any value < 0 if the first argument is less
///     or any value > 0 if the first argument is greater
/// @param index_buffer where to write the index if it is found
/// @param key the element to search for
/// @return DARRAY_ERROR_NULL if self, key or index_buffer is NULL,
///     DARRAY_NOT_FOUND if key was not found
///     DARRAY_OK if key was found (only then is the value at index_buffer valid)
/// @complexity O(log(n))
DarrayStatus darrayBinarySearch(const Darray* self, darrayOrdering darray_ordering,
    size_t* index_buffer, const void* key);

///
/// SET OPERATIONS
///

/// @brief checks if the darray is unique, i.e. has no duplicate elements. Caller is 
///     responsible for ensuring darray is sorted (ascending or descending), otherwise behavior is
///     undefined
/// @param self the darray to check
/// @param darray_ordering a function that can compare two elements of the darray's datatype
/// @return true if all elements are unique, false if there is at least one duplicate value 
/// @complexity O(n)
bool darrayIsUnique(Darray self, darrayOrdering darray_ordering);

/// @brief create a new darray consisting of only the unique elements of self. Caller is responsible
///     for ensuring self is sorted (ascending or descending), otherwise behavior is undefined
/// @param self the darray to make unique
/// @param darray_ordering a function that can compare two elements of the darray's datatype
/// @param unique where to write the result. must not be initialized to avoid memory leaks.
/// @return DARRAY_ERROR_NULL if self or unique is NULL 
///     DARRAY_ERROR_INVALID if self was not sorted 
///     DARRAY_ERROR_ALLOCATION if creating the new darray failed,
///     DARRAY_OK if everything went fine (only then is unique valid) 
/// @complexity O(n)
DarrayStatus darrayGetUnique(const Darray* self, darrayOrdering darray_ordering, Darray* unique);

/// @brief create a new darray consisting of the elements that both left and right contain.
///     Caller is responsible for ensuring both are sorted in (either both ascending or both descending)
/// @param left a sorted darry (may contain duplicates) 
/// @param right a darray sorted the same way and containing the same type as left (may contain duplicates) 
/// @param darray_ordering a function that can compare the elements of the darrays' datatype 
/// @param intersection where to write the result. Must not be initialized to avoid memory leaks.
/// @return DARRAY_ERROR_NULL if left, right or intersection is NULL
///     DARRAY_ERROR_INVALID if left or right was not sorted (or if the were not sorted the same way)
///     DARRAY_ERROR_ALLOCATION if creating the new darray failed,
///     DARRAY_OK if everything went fine (only then is intersection valid) 
/// @complexity O(n + m)
DarrayStatus darrayGetIntersection(const Darray* left, const Darray* right,
    darrayOrdering darray_ordering, Darray* intersection);

///
/// SORTING
///

//sort

/// @brief checks if self is sorted in ascending order (each element is >= the previous element)
/// @param self the darray to check
/// @param darray_ordering a function that compares two elements of the darray and returns
///     a negative value if the first value is smaller, a positive one if the second is smaller,
///     or 0 if they are equal
/// @return true if the darray is sorted, false otherwise
/// @complexity O(n)
bool darrayIsSortedAscending(Darray self, darrayOrdering darray_ordering);

/// @brief checks if self is sorted in descending order (each element is <= the previous element)
/// @param self the darray to check
/// @param darray_ordering a function that compares two elements of the darray and returns
///     a negative value if the first value is smaller, a positive one if the second is smaller,
///     or 0 if they are equal
/// @return true if the darray is sorted, false otherwise
/// @complexity O(n)
bool darrayIsSortedDescending(Darray self, darrayOrdering darray_ordering);

#endif //DARRAY_ALGS_H
