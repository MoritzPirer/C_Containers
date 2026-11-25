#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "inc/llist/llist.h"

bool llist_is_empty(const llist_t* self) {
    if (self == NULL) {
        return false;
    }

    return self->size == 0;
}

size_t llist_size(const llist_t* self) {
    if (self == NULL) {
        return (size_t) -1;
    }

    return self->size;
}

llist_element_t* create_element(size_t total_size, size_t item_size, const void* source) {
    llist_element_t* new_element = malloc(total_size);
    if (new_element == NULL) {
        return NULL;
    }

    new_element->next = NULL;
    new_element->previous = NULL;
    memcpy(new_element->payload, source, item_size);

    return new_element;
}

llist_status_t llist_push_back(llist_t* self, const void* source) {
    if (self == NULL || source == NULL) {
        return LLIST_ERROR_NULL;
    }

    llist_element_t* new_element = create_element(self->total_size, self->item_size, source);
    if (new_element == NULL) {
        return LLIST_ERROR_ALLOCATION;
    }

    if (llist_is_empty(self)) {
        self->head = new_element;
        self->tail = new_element;
    }
    else {
        self->tail->next = new_element;
        new_element->previous = self->tail;
        self->tail = new_element;
    }

    self->size++;

    return LLIST_OK;
}

void free_only_element(llist_t* self) {
    assert(self->size == 1);
    free(self->head);
    self->head = NULL;
    self->tail = NULL;
    self->size = 0;
}

llist_status_t llist_pop_back(llist_t* self, void* destination) {
    if (self == NULL) {
        return LLIST_ERROR_NULL;
    }

    if (llist_is_empty(self)) {
        return LLIST_ERROR_BOUNDS;
    }

    if (destination != NULL) {
        memcpy(destination, self->tail->payload, self->item_size);
    }
    if (self->size == 1) {
        free_only_element(self);
        return LLIST_OK;
    }

    assert(self->head != self->tail);

    llist_element_t* new_tail = self->tail->previous;
    free(self->tail);
    self->tail = new_tail;
    new_tail->next = NULL;
    self->size--;

    return LLIST_OK;
}

llist_status_t llist_push_front(llist_t* self, const void* source) {
    if (self == NULL || source == NULL) {
        return LLIST_ERROR_NULL;
    }

    llist_element_t* new_element = create_element(self->total_size, self->item_size, source);
    if (new_element == NULL) {
        return LLIST_ERROR_ALLOCATION;
    }

    if (llist_is_empty(self)) {
        self->head = new_element;
        self->tail = new_element;
    }
    else {
        self->head->previous = new_element;
        new_element->next = self->head;
        self->head = new_element;
    }

    self->size++;

    return LLIST_OK;

}

llist_status_t llist_pop_front(llist_t* self, void* destination) {
    if (self == NULL) {
        return LLIST_ERROR_NULL;
    }

    if (llist_is_empty(self)) {
        return LLIST_ERROR_BOUNDS;
    }

    if (destination != NULL) {
        memcpy(destination, self->head->payload, self->item_size);
    }
    if (self->size == 1) {
        free_only_element(self);
        return LLIST_OK;
    }

    assert(self->head != self->tail);

    llist_element_t* new_head = self->head->next;
    free(self->head);
    self->head = new_head;
    new_head->previous = NULL;
    self->size--;

    return LLIST_OK;
}
