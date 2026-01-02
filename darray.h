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
#define DARRAY_GROW_FACTOR 2.0f

typedef struct _Darray_ {
    size_t m_elements_used;
    size_t m_elements_allocated;
    size_t m_element_size;
    void* m_data;
} Darray;

typedef enum _DarrayStatus_ {
    DARRAY_OK,
    DARRAY_ERROR_ALLOCATION,
    DARRAY_ERROR_BOUNDS,
    DARRAY_ERROR_NULL
} DarrayStatus;

///
/// INITIALIZE & DESTROY
///

/// @brief initialize the given Darray object
/// @param this the darray to initialize 
/// @param initial_size how many elements should be usable right away
/// @param element_size how large a single element is 
/// @return DARRAY_OK if everything is fine, DARRAY_ERROR_ALLOCATION if the resizing failed
///     or DARRAY_ERROR_NULL if the given darray was NULL
DarrayStatus darrayInit(Darray* this, size_t initial_size, size_t element_size);

/// @brief destroy the given Darray. Using the this after this function
///     results in undefined behavior
/// @param this the Darray to destroy 
/// @return DARRAY_OK if everything is fine or DARRAY_ERROR_NULL if the given darray was NULL
DarrayStatus darrayDestroy(Darray* this);

///
/// SIZE & CAPACITY
///

/// @brief guarantees that the darray can hold at least elements_to_reserve elements
///     without having to reallocate again
/// @param this the darray to size up 
/// @param elements_to_reserve how many elements the darray should be able to hold 
/// @return DARRAY_OK if everything is fine, DARRAY_ERROR_ALLOCATION if the resizing failed 
///     or DARRAY_ERROR_NULL if the given darray was NULL
DarrayStatus darrayReserve(Darray* this, size_t elements_to_reserve);

/// @brief ensure the internal capacity matches the current size.
/// @param this the darray to size down
/// @return DARRAY_OK if everything is fine, DARRAY_ERROR_ALLOCATION if the resizing failed 
///     or DARRAY_ERROR_NULL if the given darray was NULL
DarrayStatus darrayShrinkToFit(Darray* this);

/// @brief return the amount of currently used elements
/// @param this the darray to check
/// @return the number of used elements
size_t darraySize(Darray this);

/// @brief return the number of elements there is space reserved for
/// @param this the darray to check 
/// @return the number of elements space is allocated for 
size_t darrayCapacity(Darray this);

/// @return true if the given darray is empty, false otherwise
bool darrayIsEmpty(Darray this);

///
/// ADD & REMOVE
///

/// @brief adds the element pointed to by element to the given darray, resizing if needed
/// @param this the darray to add to
/// @param element a pointer to the element to add
/// @return DARRAY_OK if everything is fine or DARRAY_ERROR_ALLOCATION if the resizing failed
///     or DARRAY_ERROR_NULL if darray or element was NULL
DarrayStatus darrayPushBack(Darray* this, void* element);

/// @brief removes the last element from the darray and writes it to the location
///     pointed to by buffer.
/// @param this the darray to pop from
/// @param buffer where to pop to
/// @return DARRAY_ERROR_BOUNDS if there is no element to pop, DARRAY_ERROR_NULL if 
///     darray or buffer are NULL, DARRAY_OK otherwise
DarrayStatus darrayPopBackInto(Darray* this, void* buffer);

/// @brief removes all elements from index start to index end (both included), and potentially
///     shrinks the darray if it is empty enough
/// @param this the darray to erase from 
/// @param start the first element to be erased 
/// @param end the last element to be erased 
/// @return DARRAY_ERROR_BOUNDS if start or end are invalid indices or if start is greater than end
///     DARRAY_ERROR_NULL if this is NULL,
///     DARRAY_ERROR_BOUNDS if the shrinking failed, DARRAY_OK ohterwise
DarrayStatus darrayEraseFromTo(Darray* this, size_t start, size_t end);

/// @brief removes all elements from index start (inclusive) to the end of the darray, and potentially
///     shrinks the darray if it is empty enough
/// @param this the darray to erase from 
/// @param start the first element to be erased 
/// @return DARRAY_ERROR_BOUNDS if start is an invalid index, 
///     DARRAY_ERROR_NULL if this is NULL,
///     DARRAY_ERROR_BOUNDS if the shrinking failed, DARRAY_OK ohterwise
DarrayStatus darrayEraseFrom(Darray* this, size_t start);

/// @brief removes all elements from the start to index end (inclusive), and potentially
///     shrinks the darray if it is empty enough
/// @param this the darray to erase from 
/// @param end the last element to be erased 
/// @return DARRAY_ERROR_BOUNDS if end is an invalid index, 
///     DARRAY_ERROR_NULL if this is NULL,
///     DARRAY_ERROR_BOUNDS if the shrinking failed, DARRAY_OK ohterwise
DarrayStatus darrayEraseTo(Darray* this, size_t end);

/// @brief removes the element at the given index and potentially
///     shrinks the darray if it is empty enough
/// @param this the darray to erase from 
/// @param index the index to erase at 
/// @return DARRAY_ERROR_BOUNDS if index is an invalid index, 
///     DARRAY_ERROR_NULL if this is NULL,
///     DARRAY_ERROR_BOUNDS if the shrinking failed, DARRAY_OK ohterwise
DarrayStatus darrayEraseAt(Darray* this, size_t index);

/// @brief removes all elements from the darray and shrinks it if it is empty enough
/// @param this the darray to erase from 
/// @param index the index to erase at 
/// @return DARRAY_ERROR_BOUNDS if index is an invalid index, 
///     DARRAY_ERROR_NULL if this is NULL,
///     DARRAY_ERROR_BOUNDS if the shrinking failed, DARRAY_OK ohterwise
DarrayStatus darrayEraseAll(Darray* this);


/// 
/// ACCESS
///

/// @brief Reads the element at position index into buffer 
/// @param this the darray to read from
/// @param index the position to read from. The first element is 0
/// @param buffer where to write the value that has been read 
/// @return DARRAAY_OK if everything is fine, DARRAY_ERROR_NULL if darray or buffer is NULL
///     or DARRAY_ERROR_BOUNDS if index < 0 or index > darraySize(darray) 
DarrayStatus darrayGetAt(Darray* this, size_t index, void* buffer);

/// @brief Set the element at position index to the value pointed to by buffer
/// @param this the darray to write to
/// @param index the position to write to. The first element is 0
/// @param buffer where the value to write is 
/// @return DARRAAY_OK if everything is fine, DARRAY_ERROR_NULL if darray or buffer is NULL
///     or DARRAY_ERROR_BOUNDS if index < 0 or index > darraySize(darray) 
DarrayStatus darraySetAt(Darray* this, size_t index, void* buffer);



void show(Darray this);



#endif //DYNAMIC_ARRAY_H
