#include <stdlib.h>
#include "inc/llist/llist.h"


llist_status_t llist_init(llist_t* self, size_t element_size) {
    if (self == NULL) {
        return LLIST_ERROR_NULL;
    }

    self->size = 0;
    self->item_size = element_size;
    self->total_size = sizeof(llist_element_t) + element_size;
    self->head = NULL;
    self->tail = NULL;

    return LLIST_OK;
}

llist_status_t llist_destroy(llist_t* self) {
    if (self == NULL) {
        return LLIST_ERROR_NULL; 
    }

    llist_element_t* current = self->head;

    while (current != NULL) {
        llist_element_t* next = current->next;
        free(current);
        current = next;
    }

    return LLIST_OK;
}
