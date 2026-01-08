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

///
/// SEARCHING
///

/// @brief takes a pointer to an element of a darray. Should return true if the element
///     matches a criteria and false otherwise. data can optionally be used for additional data
///     Must ensure to only touch that element (i.e. element_size bytes)
typedef bool (*darrayCondition) (const void* element, const void* data);

/// @brief simple equality comparison for find algorithms (among others).
///     Usable if the data type of the darray can (meaningfully) be convertet to a size_t (i.e. most built-in types)
/// @return true if element == data
bool darrayDefaultCondition(const void* element, const void* data);


typedef int (*darrayOrdering) (const void* a, const void* b);

/// @brief simple ordering for algorithms that need to compare elements.
///     Usable if the data type of the darray can (meaningfully) be converted to a size_t (i.e. most built-in types)
/// @return a negative value if a < b, a positive value if a > b, 0 if a == b
int darrayDefaultOrdering(const void* a, const void* b);

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
DarrayStatus darrayBinarySearch(Darray* self, darrayOrdering darray_ordering,
    size_t* index_buffer, void* key);

///
/// SET OPERATIONS
///

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
bool darrayIsSortedAscending(Darray self, darrayOrdering darray_ordering);

/// @brief checks if self is sorted in descending order (each element is <= the previous element)
/// @param self the darray to check
/// @param darray_ordering a function that compares two elements of the darray and returns
///     a negative value if the first value is smaller, a positive one if the second is smaller,
///     or 0 if they are equal
/// @return true if the darray is sorted, false otherwise
bool darrayIsSortedDescending(Darray self, darrayOrdering darray_ordering);

#endif //DARRAY_ALGS_H
