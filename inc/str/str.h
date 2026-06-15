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

str_status_t str_init(str_t* self, size_t initial_capacity);
str_status_t str_init_from(str_t* self, const char* source, size_t len);
str_status_t str_init_repeat(str_t* self, char c, size_t count);
str_status_t str_destroy(str_t* self);
str_status_t str_copy(const str_t* original, str_t* copy);
str_status_t str_swap(str_t* self, str_t* other);

///
/// SIZE & CAPACITY
///

// potentially also provide length as an alias
size_t str_size(const str_t* self);
size_t str_capacity(const str_t* self);
bool str_is_empty(const str_t* self);
str_status_t str_reserve(str_t* self, size_t elements_to_reserve);
str_status_t str_shrink(str_t* self);

///
/// STRUCTURE
///

str_status_t str_get_at(const str_t* self, size_t index, char* destination);
str_status_t str_set_at(str_t* self, size_t index, char c);
const char* str_cstr(const str_t* self); // like vec_data
str_status_t str_append_char(str_t* self, char c);
str_status_t str_append_str(str_t* self, const str_t* other);

str_status_t str_prepend_char(str_t* self, char c);
str_status_t str_prepend_str(str_t* self, const str_t* other);

str_status_t str_insert_char(str_t* self, size_t index, char c);
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