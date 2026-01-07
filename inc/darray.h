///
/// @file: Darray.h
/// @description: description
///
/// @date: 2025-12-31
/// @author: Moritz Pirer
///

#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stddef.h>
#include <stdbool.h>

#define DARRAY_MIN_SIZE 1

typedef struct _Darray_ {
    size_t m_elements_used;
    size_t m_elements_allocated;
    size_t m_element_size;
    void* m_data;
} Darray;

typedef enum _DarrayStatus_ {
    DARRAY_OK,                  // function succeded
    DARRAY_ERROR_ALLOCATION,    // an allocation failed
    DARRAY_ERROR_BOUNDS,        // an index was out of range
    DARRAY_ERROR_NULL,          // an argument was NULL
    DARRAY_ERROR_INVALID,       // an argument was not valid
    DARRAY_NOT_FOUND      // find operation failed
} DarrayStatus;

///
/// OWNERSHIP 
///

/// @brief initialize the given Darray object
/// @param self the darray to initialize 
/// @param initial_size how many elements should be usable right away
/// @param element_size how large a single element is 
/// @return DARRAY_OK if everything is fine, DARRAY_ERROR_ALLOCATION if the resizing failed,
///     DARRAY_ERROR_INVALID if element_size is 0,
///     or DARRAY_ERROR_NULL if the given darray was NULL
DarrayStatus darrayInit(Darray* self, size_t initial_size, size_t element_size);

/// @brief destroy the given Darray. Using the self after this function
///     results in undefined behavior
/// @param self the Darray to destroy 
/// @return DARRAY_OK if everything is fine or DARRAY_ERROR_NULL if the given darray was NULL
DarrayStatus darrayDestroy(Darray* self);

/// @brief swap two darrays
/// @param self the first darray to swap 
/// @param other the second darray to swap
/// @return DARRAY_ERROR_NULL if self or other was NULL, DARRAY_OK otherwise 
DarrayStatus darraySwap(Darray* self, Darray* other);

/// @brief Initializes copy as a deep copy of original (same values, but it's own memory).
///     copy should not own memory (i.e. should be uninitialized) to avoid memory leaks
/// @param original the darray to copy 
/// @param copy the darray that should be a copy of original 
/// @return DARRAY_ERROR_NULL if original or copy was NULL,
///     DARRAY_ERROR_ALLOCATION if allocation failed,
///     DARRAY_OK otherwise
DarrayStatus darrayDeepCopy(const Darray* original, Darray* copy);

/// @brief Copies all elements of other to the end of self. other is not modified and stays a 
///     valid darray. Caller is responsible for ensuring self and other store the same datatype
/// @param self the darray that should be added to 
/// @param other the darray that shoud be added to self 
/// @return DARRAY_ERROR_NULL if self or other was NULL,
///     DARRAY_ERROR_ALLOCATION if resiting failed,
///     DARRAY_OK otherwise 
DarrayStatus darrayAppend(Darray* self, const Darray* other);

///
/// SIZE & CAPACITY
///

/// @brief guarantees that the darray can hold at least elements_to_reserve elements
///     without having to reallocate again
/// @param self the darray to size up 
/// @param elements_to_reserve how many elements the darray should be able to hold 
/// @return DARRAY_OK if everything is fine, DARRAY_ERROR_ALLOCATION if the resizing failed 
///     or DARRAY_ERROR_NULL if the given darray was NULL
DarrayStatus darrayReserve(Darray* self, size_t elements_to_reserve);

/// @brief ensure the internal capacity matches the current size.
/// @param self the darray to size down
/// @return DARRAY_OK if everything is fine, DARRAY_ERROR_ALLOCATION if the resizing failed 
///     or DARRAY_ERROR_NULL if the given darray was NULL
DarrayStatus darrayShrinkToFit(Darray* self);

/// @brief return the amount of currently used elements
/// @param self the darray to check
/// @return the number of used elements
size_t darraySize(Darray self);

/// @brief return the number of elements there is space reserved for
/// @param self the darray to check 
/// @return the number of elements space is allocated for 
size_t darrayCapacity(Darray self);

/// @return true if the given darray is empty, false otherwise
bool darrayIsEmpty(Darray self);

/// @brief resize the darray to hold exactly new_size elements. Sizing up zeros new memory.
///     sizing down loses elements that don't fit into the new size.
/// @param self the darray to resize 
/// @param new_size the size the darray should be set to 
/// @return 
DarrayStatus darrayResize(Darray* self, size_t new_size);

///
/// STRUCTURE
///

/// @brief adds the element pointed to by element to the end of given darray, resizing if needed
/// @param self the darray to add to
/// @param element a pointer to the element to add
/// @return DARRAY_OK if everything is fine or DARRAY_ERROR_ALLOCATION if the resizing failed
///     or DARRAY_ERROR_NULL if darray or element was NULL
DarrayStatus darrayPushBack(Darray* self, void* element);

/// @brief removes the last element from the darray and writes it to the location
///     pointed to by element. Shrinks the darray if it becomes empty enough
/// @param self the darray to pop from
/// @param element where to pop to
/// @return DARRAY_ERROR_BOUNDS if there is no element to pop, 
///     DARRAY_ERROR_NULL if darray or buffer are NULL,
///     DARRAY_ERROR_ALLOC if shrinking failed,
///     DARRAY_OK otherwise
DarrayStatus darrayPopBackInto(Darray* self, void* element);

/// @brief adds the element pointed to by element to the front of
///     the given darray, resizing if needed
/// @param self the darray to add to
/// @param element a pointer to the element to add 
/// @return DARRAY_ERROR_NULL if self or element is NULL,
///     DARRAY_ERROR_ALLOCATION if resizing the darray failed,
///     DARRAY_OK otherwise
DarrayStatus darrayPushFront(Darray* self, void* element);

/// @brief removes the first element from the darray and writes it to the location
///     pointed to by element.
/// @param self the darray to pop from 
/// @param element where to pop to 
/// @return DARRAY_ERROR_NULL if self or element is NULL,
///     DARRAY_ERROR_BOUNDS if the index is out of range,
///     DARRAY_ERROR_ALLOCATION if resizing the darray failed,
///     DARRAY_OK otherwise
DarrayStatus darrayPopFrontInto(Darray* self, void* element);

/// @brief insert the given element at the given index, pushing all elements with index >= index back
/// @param self the darray to insert into 
/// @param index the index to insert at 
/// @param element the element to insert 
/// @return DARRAY_ERROR_NULL if self or element is NULL,
///     DARRAY_ERROR_BOUNDS if the index is out of range,
///     DARRAY_ERROR_ALLOCATION if resizing the darray failed,
///     DARRAY_OK otherwise
DarrayStatus darrayInsertAt(Darray* self, size_t index, void* element);

///
/// ERASE
///

/// @brief removes all elements from index start to index end (both included), and potentially
///     shrinks the darray if it is empty enough
/// @param self the darray to erase from 
/// @param start the first element to be erased 
/// @param end the last element to be erased 
/// @return DARRAY_ERROR_BOUNDS if start or end are invalid indices or if start is greater than end
///     DARRAY_ERROR_NULL if self is NULL,
///     DARRAY_ERROR_ALLOCATION if the shrinking failed, DARRAY_OK otherwise
DarrayStatus darrayEraseFromTo(Darray* self, size_t start, size_t end);

/// @brief removes all elements from index start (inclusive) to the end of the darray, and potentially
///     shrinks the darray if it is empty enough
/// @param self the darray to erase from 
/// @param start the first element to be erased 
/// @return DARRAY_ERROR_BOUNDS if start is an invalid index, 
///     DARRAY_ERROR_NULL if self is NULL,
///     DARRAY_ERROR_ALLOCATION if the shrinking failed, DARRAY_OK otherwise
DarrayStatus darrayEraseFrom(Darray* self, size_t start);

/// @brief removes all elements from the start to index end (inclusive), and potentially
///     shrinks the darray if it is empty enough
/// @param self the darray to erase from 
/// @param end the last element to be erased 
/// @return DARRAY_ERROR_BOUNDS if end is an invalid index, 
///     DARRAY_ERROR_NULL if self is NULL,
///     DARRAY_ERROR_ALLOCATION if the shrinking failed, DARRAY_OK otherwise
DarrayStatus darrayEraseTo(Darray* self, size_t end);

/// @brief removes the element at the given index and potentially
///     shrinks the darray if it is empty enough
/// @param self the darray to erase from 
/// @param index the index to erase at 
/// @return DARRAY_ERROR_BOUNDS if index is an invalid index, 
///     DARRAY_ERROR_NULL if self is NULL,
///     DARRAY_ERROR_ALLOCATION if the shrinking failed, DARRAY_OK otherwise
DarrayStatus darrayEraseAt(Darray* self, size_t index);

/// @brief removes all elements from the darray and shrinks it if it is empty enough
/// @param self the darray to erase from 
/// @param index the index to erase at 
/// @return DARRAY_ERROR_BOUNDS if index is an invalid index, 
///     DARRAY_ERROR_NULL if self is NULL,
///     DARRAY_ERROR_ALLOCATION if the shrinking failed, DARRAY_OK otherwise
DarrayStatus darrayEraseAll(Darray* self);

/// @brief alias for darrayEraseAll
DarrayStatus darrayClear(Darray* self);

/// 
/// ACCESS
///

/// @brief Reads the element at position index into buffer 
/// @param self the darray to read from
/// @param index the position to read from. The first element is 0
/// @param buffer where to write the value that has been read 
/// @return DARRAY_OK if everything is fine, DARRAY_ERROR_NULL if darray or buffer is NULL
///     or DARRAY_ERROR_BOUNDS if index > darraySize(darray) 
DarrayStatus darrayGetAt(const Darray* self, size_t index, void* buffer);

/// @brief Set the element at position index to the value pointed to by buffer
/// @param self the darray to write to
/// @param index the position to write to. The first element is 0
/// @param buffer where the value to write is 
/// @return DARRAY_OK if everything is fine, DARRAY_ERROR_NULL if darray or buffer is NULL
///     or DARRAY_ERROR_BOUNDS if index > darraySize(darray) 
DarrayStatus darraySetAt(Darray* self, size_t index, const void* buffer);

/// @brief returns a raw pointer to the darrays heap memory. Pointer may become invalid if used
///     after any operation that adds or removes elements
/// @param self the darray who's data shoud be accessed 
/// @return a pointer to the heap data or NULL if self was NULL 
void* darrayData(const Darray* self);

void show(Darray self);

#endif //DYNAMIC_ARRAY_H
