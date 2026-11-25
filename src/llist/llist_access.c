#include <string.h>

#include "inc/llist/llist.h"

llist_status_t llist_get(const llist_t* self, size_t index, void* destination) {
    if (self == NULL || destination == NULL) {
        return LLIST_ERROR_NULL;
    }

    if (index >= self->size) {
        return LLIST_ERROR_BOUNDS;
    }

    llist_element_t* current = self->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }

    memcpy(destination, current->payload, self->item_size);
    return LLIST_OK;
}

llist_status_t llist_set(llist_t* self, size_t index, const void* source) {
    if (self == NULL || source == NULL) {
        return LLIST_ERROR_NULL;
    }

    if (index >= self->size) {
        return LLIST_ERROR_BOUNDS;
    }

    llist_element_t* current = self->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }

    memcpy(current->payload, source, self->item_size);
    return LLIST_OK;
}
