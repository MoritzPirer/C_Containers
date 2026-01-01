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
} DarrayStatus;

/// @brief initialize the given Darray object
/// @param darray the darray to initialize 
/// @param initial_size how many elements should be usable right away
/// @param element_size how large a single element is 
/// @return DARRAY_OK if everything is fine or DARRAY_ERROR_ALLOCATION if the resizing failed
DarrayStatus darrayInit(Darray* darray, size_t initial_size, size_t element_size);

/// @brief destroy the given Darray. Using the darray after this function
///     results in undefined behavior
/// @param darray the Darray to destroy 
void darrayDestroy(Darray* darray);

/// @brief guarantees that the darray can hold at least elements_to_reserve elements
///     without having to reallocate again
/// @param darray the darray to size up 
/// @param elements_to_reserve how many elements the darray should be able to hold 
/// @return DARRAY_OK if everything is fine or DARRAY_ERROR_ALLOCATION if the resizing failed 
DarrayStatus darrayReserve(Darray* darray, size_t elements_to_reserve);

/// @brief ensure the internal capacity matches the current size.
/// @param darray the darray to size down
/// @return DARRAY_OK if everything is fine or DARRAY_ERROR_ALLOCATION if the resizing failed 
DarrayStatus darrayShrinkToFit(Darray* darray);

/// @brief return the amount of currently used elements
/// @param darray the darray to check
/// @return the number of used elements
size_t darraySize(Darray darray);

/// @brief return the number of elements there is space reserved for
/// @param darray the darray to check 
/// @return the number of elements space is allocated for 
size_t darrayCapacity(Darray darray);

/// @return true if the given darray is empty, false otherwise
bool darrayIsEmpty(Darray darray);

/// @brief adds the element pointed to by element to the given darray, resizing if needed
/// @param darray the darray to add to
/// @param element a pointer to the element to add
/// @return DARRAY_OK if everything is fine or DARRAY_ERROR_ALLOCATION if the resizing failed
DarrayStatus darrayPushBack(Darray* darray, void* element);

void show(Darray darray);
#endif //DYNAMIC_ARRAY_H
