///
/// @file: str.h
/// @description: an implementation of a dynamic string
///
/// @date: 2026-06-15
/// @author: Moritz Pirer
///

#ifndef STR_H
#define STR_H

#include <stddef.h>
#include <stdbool.h>

#define STR_MIN_CAPACITY 8

typedef struct str_t_ {
    char* array;
    size_t capacity;
    size_t size;
} str_t;

typedef enum str_status_t_ {
    STR_OK,
    STR_ERROR_ALLOCATION,
    STR_ERROR_BOUNDS,
    STR_ERROR_NULL,
    STR_ERROR_INVALID,
    STR_ERROR_NOT_FOUND
} str_status_t;

///
/// OWNERSHIP
///

/// @brief initializes self as an empty string large enough to hold at least initial_capacity characters
/// @param self the string to initialize
/// @param initial_capacity the minimum capacity the string should be able to hold without reallocating
/// @return STR_ERROR_NULL if self was NULL, STR_ERROR_ALLOCATION if allocating memory for the string failed,
///     STR_OK otherwise
str_status_t str_init(str_t* self, size_t initial_capacity);

/// @brief not finished implementing
str_status_t str_init_from(str_t* self, const char* source, size_t len);

/// @brief initializes self as a string containing the given character the given number of times
/// @param self the string to initialize
/// @param c the character to fill with
/// @param count how often to repeat the character
/// @return STR_ERROR_NULL if self was NULL, STR_ERROR_ALLOCATION if allocating memory for the string failed,
///     STR_OK otherwise
str_status_t str_init_repeat(str_t* self, char c, size_t count);

/// @brief destroys the given string. save to call multiple times
/// @param self the string to destroy
/// @return STR_ERROR_NULL if self was NULL, STR_OK otherwise
str_status_t str_destroy(str_t* self);

/// @brief creates a deep copy of the given string
/// @param original the string to copy
/// @param copy where to write the copy. Should be uninitialized to avoid memory leaks
/// @return STR_ERROR_NULL if self was NULL, STR_ERROR_ALLOCATION if allocating memory for the copy failed,
///     STR_OK otherwise
str_status_t str_copy(const str_t* original, str_t* copy);

/// @brief swaps the content (and associated metadata) of the two strings
/// @param self one of the strings to swap
/// @param other the other string to swap
/// @return STR_ERROR_NULL if one or both strings were NULL, STR_OK otherwise
str_status_t str_swap(str_t* self, str_t* other);

///
/// SIZE & CAPACITY
///

/// @brief returns the size of the string (not including a null byte)
/// @param self the string to inspect
/// @return the length of the string or -1 if self was NULL
size_t str_size(const str_t* self);

/// @brief returns the capacity of the string, i.e. the number of characters the string can store before reallocating
/// @param self the string to inspect
/// @return the capacity of the string or -1 if self was NULL
size_t str_capacity(const str_t* self);

/// @brief checks if the string is empty
/// @param self the string to check
/// @return true if the string does not contain any characters or if string is NULL, false if it contains
///     at least one character
bool str_is_empty(const str_t* self);

/// @brief TODO
str_status_t str_reserve(str_t* self, size_t elements_to_reserve);

/// @brief TODO
str_status_t str_shrink(str_t* self);

///
/// STRUCTURE
///

/// @brief read the char at the given index into destination
/// @param self the string to read from
/// @param index the index to read at
/// @param destination where to write the character to
/// @return STR_ERROR_NULL if self of destination were NULL, STR_ERROR_BOUNDS if index is out of range, STR_OK otherwise
str_status_t str_get_at(const str_t* self, size_t index, char* destination);

/// @brief set the char at the given index 
/// @param self the string to write to
/// @param index the index to write at
/// @param c the char to write
/// @return STR_ERROR_NULL if self of destination were NULL, STR_ERROR_BOUNDS if index is out of range, STR_OK otherwise
str_status_t str_set_at(str_t* self, size_t index, char c);

/// @brief TODO
const char* str_cstr(const str_t* self); // like vec_data

/// @brief adds a character to the end of the string
/// @param self the string to add to
/// @param c the character to add
/// @return STR_ERROR_NULL if self was NULL, STR_ERROR_ALLOCATION if the string could not
///     be resized to contain the new char, STR_OK otherwise
str_status_t str_append_char(str_t* self, char c);

/// @brief adds a string to the end of the string
/// @param self the string to add to
/// @param other the string to add
/// @return STR_ERROR_NULL if self was NULL, STR_ERROR_ALLOCATION if the string could not
///     be resized to contain the new characters, STR_OK otherwise
str_status_t str_append_str(str_t* self, const str_t* other);

/// @brief adds a string to the start of the string
/// @param self the string to add to
/// @param c the character to add
/// @return STR_ERROR_NULL if self was NULL, STR_ERROR_ALLOCATION if the string could not
///     be resized to contain the new char, STR_OK otherwise
str_status_t str_prepend_char(str_t* self, char c);

/// @brief adds a string to the start of the string
/// @param self the string to add to
/// @param other the string to add
/// @return STR_ERROR_NULL if self was NULL, STR_ERROR_ALLOCATION if the string could not
///     be resized to contain the new characters, STR_OK otherwise
str_status_t str_prepend_str(str_t* self, const str_t* other);


/// @brief inserts a character at the given index
/// @param self the string to insert in
/// @param index the index to insert at
/// @param c the character to insert
/// @return STR_ERROR_NULL if self was NULL, STR_ERROR_ALLOCATION if the string could not
///     be resized to contain the new char, STR_ERROR_BOUNDS if index is out of range, STR_OK otherwise
str_status_t str_insert_char(str_t* self, size_t index, char c);

/// @brief inserts a string at the given index
/// @param self the string to insert in
/// @param index the index to insert at
/// @param other the string to insert
/// @return STR_ERROR_NULL if self was NULL, STR_ERROR_ALLOCATION if the string could not
///     be resized to contain the new characters, STR_ERROR_BOUNDS if index is out of range, STR_OK otherwise
str_status_t str_insert_str(str_t* self, size_t index, const str_t* other);

///
/// ERASE
///

str_status_t str_erase_at(str_t* self, size_t index);
str_status_t str_erase_from_to(str_t* self, size_t start, size_t end);
str_status_t str_erase_from(str_t* self, size_t start);
str_status_t str_erase_to(str_t* self, size_t end);
str_status_t str_clear(str_t* self);

#endif // STR_H