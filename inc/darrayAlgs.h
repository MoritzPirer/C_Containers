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

/// @brief used by darrayTransform. May change the element in-place. Should not change the dataype of 
///     the darray, although that is not enforced as long as the element size stays the same. data can
///     be used to pass in additional date (for easier reuse of functions)
typedef void (*darrayTransformation) (void* element, const void* data);
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
/// ITERATING
///

/// @brief check if condition is true for at least one element of the darray
/// @param self the darray to check
/// @param condition the condition to apply to each element
/// @param data any additional data needed by condition (can pass NULL if not needed)
/// @return true if condition is true for at least one element, false otherwise
/// @param self the darray to reverse 
/// @complexity O(n)
bool darrayAny(Darray self, darrayCondition condition, const void* data);

/// @brief check if condition is true for all elements of the darray
/// @param self the darray to check
/// @param condition the condition to apply to each element
/// @param data any additional data needed by condition (can pass NULL if not needed)
/// @return true if condition is true for every element, false otherwise
/// @param self the darray to reverse 
/// @complexity O(n)
bool darrayAll(Darray self, darrayCondition condition, const void* data);

/// @brief check if condition is false for all elements of the darray
/// @param self the darray to check
/// @param condition the condition to apply to each element
/// @param data any additional data needed by condition (can pass NULL if not needed)
/// @return true if condition is false for every element, false otherwise
/// @complexity O(n)
bool darrayNone(Darray self, darrayCondition condition, const void* data);

/// @brief reverses the elements of the darray in-place
/// @param self the darray to reverse 
/// @complexity O(n)
void darrayReverse(Darray* self);

/// @brief creates a new darray of all elements of self for which condition returns true
/// @param self the array to use as an input
/// @param condition the condition to check for all elements of self
/// @param filtered where to write the filtered result. Must be uninitialized.
/// @param data any additional data needed by condition. can pass NULL if not needed.
/// @return DARRAY_ERROR_NULL if self or filtered was NULL
///     DARRAY_ERROR_ALLOCATION if creating or resizing filtered failed, 
///     DARRAY_OK if everything worked (only then is filtered valid)
/// @complexity O(n)
DarrayStatus darrayFilter(const Darray* self, darrayCondition condition,
    Darray* filtered, const void* data);

/// @brief applies the given transformation function to each element of the darray.
/// @param self the darray to transform
/// @param transformation the transformation to apply. Should modify the element in-place.
///     Should not change the data type (although that is not technically enforced). Should not touch 
///     more bytes than the one element uses.
/// @param data any additional data needed by transformation. Can pass NULL if not needed.
/// @return DARRAY_ERROR_NULL if self was null, DARRAY_OK otherwise
/// @complexity O(n)
DarrayStatus darrayTransform(Darray* self, darrayTransformation transformation, const void* data);

///
/// RANGES
///

/// @brief generates a range from start (inclusive) to stop (exclusive), increasing by step each time
/// @param self where to write the range. Must be uninitialized
/// @param start the first value in the range
/// @param stop the first value outside of the range
/// @param step how much to increase or decrease between elements. If negative,
///     start must be greater than stop. May not be 0
/// @return DARRAY_ERROR_NULL if self is NULL
///     DARRAY_ERROR_INVALID if step is 0 or step direction is away from stop point
///     DARRAY_ERROR_ALLOCATION if creating the darray failed,
///     DARRAY_OK if everything worked (only then is self valid)
DarrayStatus darrayRangeFromToStep(Darray* self, size_t start, size_t stop, int step);

/// @brief generates a range from start (inclusive) to stop (exclusive), increasing by 1 each time
/// @param self where to write the range. Must be uninitialized
/// @param start the first value in the range
/// @param stop the first value outside of the range
/// @return DARRAY_ERROR_NULL if self is NULL
///     DARRAY_ERROR_INVALID if start > stop (use darrayRangeFromToStep with
///     a negative step if you want a decrementing range)
///     DARRAY_ERROR_ALLOCATION if creating the darray failed,
///     DARRAY_OK if everything worked (only then is self valid)
DarrayStatus darrayRangeFromTo(Darray* self, size_t start, size_t stop);

/// @brief generates a range from 0 (inclusive) to stop (exclusive), increasing by step each time
/// @param self where to write the range. Must be uninitialized
/// @param stop the first value outside of the range
/// @param step how much to increase or decrease between elements. May not be negative
/// @return DARRAY_ERROR_NULL if self is NULL
///     DARRAY_ERROR_INVALID if step is <= 0
///     DARRAY_ERROR_ALLOCATION if creating the darray failed,
///     DARRAY_OK if everything worked (only then is self valid)
DarrayStatus darrayRangeToStep(Darray* self, size_t stop, int step);

/// @brief generates a range from 0 (inclusive) to stop (exclusive), increasing by 1 each time
/// @param self where to write the range. Must be uninitialized
/// @param stop the first value outside of the range
/// @return DARRAY_ERROR_NULL if self is NULL
///     DARRAY_ERROR_ALLOCATION if creating the darray failed,
///     DARRAY_OK if everything worked (only then is self valid)
DarrayStatus darrayRangeTo(Darray* self, size_t stop);

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
///     Caller is responsible for ensuring both are sorted (either both ascending or both descending)
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

/// @brief create a new darray consisting of the elements contained by left and / or right.
///     Caller is responsible for ensuring both are sorted (either both ascending or both descending)
/// @param left a sorted darray (may contain duplicates)
/// @param right a darray sorted the same way and containing the same type as left (may contain duplicates)
/// @param darray_ordering a function that compare the elements of the darrays' datatype
/// @param union_elements where to write the result. Must not be initialized to avoid memory leaks 
/// @return DARRAY_ERROR_NULL if left, right or union_elements is NULL
///     DARRAY_ERROR_INVALID if left or right was not sorted (or if the were not sorted the same way)
///     DARRAY_ERROR_ALLOCATION if creating the new darray failed,
///     DARRAY_OK if everything went fine (only then is union_elements valid) 
/// @complexity O(n + m)
DarrayStatus darrayGetUnion(const Darray* left, const Darray* right,
    darrayOrdering darray_ordering, Darray* union_elements);

///
/// SORTING
///

/// @brief sorts the darray using stdlib's qsort().
/// @param self the darray to sort 
/// @param darray_ordering the comparison function to use
/// @return DARRAY_ERROR_NULL if self is NULL, DARRAY_OK otherwise
DarrayStatus darraySort(Darray* self, darrayOrdering darray_ordering);

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

/// @brief checks if two darrays holding the same dataytpe are equal with regard to darray_ordering
/// @param left one of the darrays to compare
/// @param right the other darray ot compare
/// @param darray_ordering a function that can compare two elements of the darrays' datatype.
///     should return 0 for equal elements
/// @return true if the darrays are equal, false otherwise
/// @complexity O(n)
bool darrayEquals(Darray left, Darray right, darrayOrdering darray_ordering);

#endif //DARRAY_ALGS_H
