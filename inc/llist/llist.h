/*
push back
push front
pop back
pop front
insert at index
pop at index
clear
isempty
size
deep copy

iterator
*/

#ifndef LLIST_H
#define LLIST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct llist_element_t_ {
    struct llist_element_t_* previous;
    struct llist_element_t_* next;
    unsigned char payload[];
} llist_element_t;

typedef struct llist_t_ {
    size_t size;
    size_t item_size;
    size_t total_size;
    llist_element_t* head;
    llist_element_t* tail;
} llist_t;

typedef enum llist_status_t_ {
    LLIST_OK,
    LLIST_ERROR_ALLOCATION,
    LLIST_ERROR_BOUNDS,
    LLIST_ERROR_NULL
} llist_status_t;

llist_status_t llist_init(llist_t* self, size_t element_size);

llist_status_t llist_destroy(llist_t* self);

//TODO: deep copy, add all

size_t llist_size(const llist_t* self);
bool llist_is_empty(const llist_t* self);

llist_status_t llist_push_back(llist_t* self, const void* source);
llist_status_t llist_pop_back(llist_t* self, void* destination);
llist_status_t llist_push_front(llist_t* self, const void* source);
llist_status_t llist_pop_front(llist_t* self, void* destination);

//TODO insert, pop at index, clear

llist_status_t llist_get(const llist_t* self, size_t index, void* destination);
llist_status_t llist_set(llist_t* self, size_t index, const void* source);

llist_status_t llist_get_head(const llist_t* self, void* destination);
llist_status_t llist_set_head(llist_t* self, const void* source);

llist_status_t llist_get_tail(const llist_t* self, void* destination);
llist_status_t llist_set_tail(llist_t* self, const void* source);


#endif //LLIST_H
