///
/// @file: vec.h
/// @description: an implementation of a dynamic array similar to c++'s vector
///
/// @date: 2025-12-31
/// @author: Moritz Pirer
///

#ifndef VEC_H
#define VEC_H

#include <stddef.h>
#include <stdbool.h>

#define VEC_MIN_SIZE 4

typedef struct vec_t_ {
    size_t size;
    size_t capacity;
    size_t item_size;
    void *array;
} vec_t;

typedef enum vec_status_t_ {
    VEC_OK,               // function succeded
    VEC_ERROR_ALLOCATION, // an allocation failed
    VEC_ERROR_BOUNDS,     // an index was out of range
    VEC_ERROR_NULL,       // an argument was NULL
    VEC_ERROR_INVALID,    // an argument was not valid
    VEC_NOT_FOUND         // find operation failed
} vec_status_t;

///
/// OWNERSHIP
///

/// @brief prints metadata and contents of the vec. For debugging / development process only
void vec_debug(vec_t* self);

/// @brief initialize the given vec_t object
/// @param self the vec to initialize
/// @param initial_size how many elements the vec has upon creation (0 for an emty vec)
/// @param element_size how large a single element is
/// @return VEC_OK if everything is fine, VEC_ERROR_ALLOCATION if the resizing failed,
///     VEC_ERROR_INVALID if element_size is 0,
///     or VEC_ERROR_NULL if the given vec was NULL
vec_status_t vec_init(vec_t* self, size_t initial_size, size_t element_size);

/// @brief destroy the given vec_t. Using the self after this function
///     results in undefined behavior
/// @param self the vec_t to destroy
/// @return VEC_OK if everything is fine or VEC_ERROR_NULL if the given vec was NULL
vec_status_t vec_destroy(vec_t* self);

/// @brief swap two vecs
/// @param self the first vec to swap
/// @param other the second vec to swap
/// @return VEC_ERROR_NULL if self or other was NULL, VEC_OK otherwise
vec_status_t vec_swap(vec_t* self, vec_t* other);

/// @brief Initializes copy as a deep copy of original (same values, but it's own memory).
///     copy should be uninitialized to avoid memory leaks
/// @param original the vec to copy
/// @param copy the vec that should be a copy of original
/// @return VEC_ERROR_NULL if original or copy was NULL,
///     VEC_ERROR_ALLOCATION if allocation failed,
///     VEC_OK otherwise
vec_status_t vec_copy(vec_t* original, vec_t* copy);

/// @brief Copies all elements of other to the end of self. other is not modified and stays a
///     valid vec. Caller is responsible for ensuring self and other store the same datatype
/// @param self the vec that should be added to
/// @param other the vec that shoud be added to self
/// @return VEC_ERROR_NULL if self or other was NULL,
///     VEC_ERROR_ALLOCATION if resizing failed,
///     VEC_OK otherwise
vec_status_t vec_append(vec_t* self, vec_t* other);

///
/// SIZE & CAPACITY
///

/// @brief guarantees that the vec can hold at least elements_to_reserve elements
///     without having to reallocate again
/// @param self the vec to size up
/// @param elements_to_reserve how many elements the vec should be able to hold
/// @return VEC_OK if everything is fine, VEC_ERROR_ALLOCATION if the resizing failed
///     or VEC_ERROR_NULL if the given vec was NULL
vec_status_t vec_reserve(vec_t* self, size_t elements_to_reserve);

/// @brief ensure the internal capacity matches the current size.
/// @param self the vec to size down
/// @return VEC_OK if everything is fine, VEC_ERROR_ALLOCATION if the resizing failed
///     or VEC_ERROR_NULL if the given vec was NULL
vec_status_t vec_shrink(vec_t* self);

/// @brief return the amount of currently used elements
/// @param self the vec to check
/// @return the number of used elements
size_t vec_size(const vec_t* self);

/// @brief return the number of elements there is space reserved for
/// @param self the vec to check
/// @return the number of elements space is allocated for
size_t vec_capacity(const vec_t* self);

/// @return true if the given vec is empty, false otherwise
bool vec_is_empty(const vec_t* self);

/// @brief resize the vec to hold exactly new_size elements. Sizing up zeros new memory.
///     sizing down loses elements that don't fit into the new size.
/// @param self the vec to resize
/// @param new_size the size the vec should be set to
/// @return
vec_status_t vec_resize(vec_t* self, size_t new_size);

///
/// STRUCTURE
///

/// @brief adds the element pointed to by element to the end of given vec, resizing if needed
/// @param self the vec to add to
/// @param source a pointer to the element to add. Caller must guarantee element is valid until
///     the function call returns
/// @return VEC_OK if everything is fine or VEC_ERROR_ALLOCATION if the resizing failed
///     or VEC_ERROR_NULL if vec or element was NULL
vec_status_t vec_push_back(vec_t* self, void *source);

/// @brief removes the last element from the vec and writes it to the location
///     pointed to by element. Shrinks the vec if it becomes empty enough
/// @param self the vec to pop from
/// @param destination a pointer to the location to write to. Caller must guarantee element is valid until
///     the function call returns
/// @return VEC_ERROR_BOUNDS if there is no element to pop,
///     VEC_ERROR_NULL if vec or buffer are NULL,
///     VEC_ERROR_ALLOC if shrinking failed,
///     VEC_OK otherwise
vec_status_t vec_pop_back(vec_t* self, void *destination);

/// @brief adds the element pointed to by element to the front of
///     the given vec, resizing if needed
/// @param self the vec to add to
/// @param source a pointer to the location to write to. Caller must guarantee element is valid until
///     the function call returns
/// @return VEC_ERROR_NULL if self or element is NULL,
///     VEC_ERROR_ALLOCATION if resizing the vec failed,
///     VEC_OK otherwise
vec_status_t vec_push_front(vec_t* self, void *source);

/// @brief removes the first element from the vec and writes it to the location
///     pointed to by element.
/// @param self the vec to pop from
/// @param destination where to pop to. Caller must guarantee that element is valid
///     until the function call returns
/// @return VEC_ERROR_NULL if self or element is NULL,
///     VEC_ERROR_BOUNDS if the index is out of range,
///     VEC_ERROR_ALLOCATION if resizing the vec failed,
///     VEC_OK otherwise
vec_status_t vec_pop_front(vec_t* self, void *destination);

/// @brief insert the given element at the given index, pushing all elements with index >= index back
/// @param self the vec to insert into
/// @param index the index to insert at
/// @param element the element to insert. Caller must guarantee that element is
///     valid until the function call returns
/// @return VEC_ERROR_NULL if self or element is NULL,
///     VEC_ERROR_BOUNDS if the index is out of range,
///     VEC_ERROR_ALLOCATION if resizing the vec failed,
///     VEC_OK otherwise
vec_status_t vec_insert(vec_t* self, size_t index, void *element);

///
/// ERASE
///

/// @brief removes all elements from index start to index end (both included), and potentially
///     shrinks the vec if it is empty enough
/// @param self the vec to erase from
/// @param start the first element to be erased
/// @param end the last element to be erased
/// @return VEC_ERROR_BOUNDS if start or end are invalid indices or if start is greater than end
///     VEC_ERROR_NULL if self is NULL,
///     VEC_ERROR_ALLOCATION if the shrinking failed, VEC_OK otherwise
vec_status_t vec_erase_from_to(vec_t* self, size_t start, size_t end);

/// @brief removes all elements from index start (inclusive) to the end of the vec, and potentially
///     shrinks the vec if it is empty enough
/// @param self the vec to erase from
/// @param start the first element to be erased
/// @return VEC_ERROR_BOUNDS if start is an invalid index,
///     VEC_ERROR_NULL if self is NULL,
///     VEC_ERROR_ALLOCATION if the shrinking failed, VEC_OK otherwise
vec_status_t vec_erase_from(vec_t* self, size_t start);

/// @brief removes all elements from the start to index end (inclusive), and potentially
///     shrinks the vec if it is empty enough
/// @param self the vec to erase from
/// @param end the last element to be erased
/// @return VEC_ERROR_BOUNDS if end is an invalid index,
///     VEC_ERROR_NULL if self is NULL,
///     VEC_ERROR_ALLOCATION if the shrinking failed, VEC_OK otherwise
vec_status_t vec_erase_to(vec_t* self, size_t end);

/// @brief removes the element at the given index and potentially
///     shrinks the vec if it is empty enough
/// @param self the vec to erase from
/// @param index the index to erase at
/// @return VEC_ERROR_BOUNDS if index is an invalid index,
///     VEC_ERROR_NULL if self is NULL,
///     VEC_ERROR_ALLOCATION if the shrinking failed, VEC_OK otherwise
vec_status_t vec_erase_at(vec_t* self, size_t index);

/// @brief removes all elements from the vec and shrinks it if it is empty enough
/// @param self the vec to erase from
/// @param index the index to erase at
/// @return VEC_ERROR_BOUNDS if index is an invalid index,
///     VEC_ERROR_NULL if self is NULL,
///     VEC_ERROR_ALLOCATION if the shrinking failed, VEC_OK otherwise
vec_status_t vec_erase_all(vec_t* self);

/// @brief alias for vec_erase_all
vec_status_t vec_clear(vec_t* self);

///
/// ACCESS
///

/// @brief Reads the element at position index into buffer
/// @param self the vec to read from
/// @param index the position to read from. The first element is 0
/// @param buffer where to write the value that has been read. Caller must
///     guarantee that buffer is valid until the function call returns
/// @return VEC_OK if everything is fine, VEC_ERROR_NULL if vec or buffer is NULL
///     or VEC_ERROR_BOUNDS if index > vec_size(vec)
vec_status_t vec_get(const vec_t* self, size_t index, void *buffer);

/// @brief Set the element at position index to the value pointed to by buffer
/// @param self the vec to write to
/// @param index the position to write to. The first element is 0
/// @param buffer where the value to write is. Caller must
///     guarantee that buffer is valid until the function call returns
/// @return VEC_OK if everything is fine, VEC_ERROR_NULL if vec or buffer is NULL
///     or VEC_ERROR_BOUNDS if index > vec_size(vec)
vec_status_t vec_set(vec_t* self, size_t index, const void *buffer);

/// @brief returns a raw pointer to the vecs heap memory. Pointer may become invalid if used
///     after any operation that adds or removes elements
/// @param self the vec who's data shoud be accessed
/// @return a pointer to the heap data or NULL if self was NULL
void *vec_data(vec_t* self);

///
/// INTEGRATION
///

typedef struct hset_t_ hset_t;

/// @brief initialites destination as an hset containing all unique elements of self (i.e. duplicates are lost)
/// @param self the vector to source from
/// @param destination the hset to write to (must be uninitialized)
/// @param hset_comparision a function that compares two elements for equality
/// @return 
vec_status_t vec_to_hset(const vec_t* self, hset_t* destination,
    bool (*hset_comparison)(const void* a, const void* b, size_t item_size));

#endif // VEC_H
