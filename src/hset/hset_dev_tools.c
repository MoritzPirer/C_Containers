#include <printf.h>
#include "../../inc/hset/hset.h"
#include "hset_internal.h"

void hset_debug(const hset_t* self) {
    if (self == NULL) {
        return;
    }

    printf("=== Hset Debug ===\n");
    printf("size: %zu\n", self->size);
    printf("capacity: %zu\n", self->capacity);
    printf("item size: %zu\n", self->item_size);
    
    for (size_t index = 0; index < self->capacity; index++) {
        unsigned char entry[self->boosted_size];
        _hset_copy_from_nth_index(entry, self, index);

        hset_item_state_t item_state = *((hset_item_state_t*) entry); 
        if (item_state == HSET_EMPTY) {
            printf("[NIL]\n");
            continue;
        }
        if (item_state == HSET_DELETED) {
            printf("[DEL] %d\n", *(int*) (entry + sizeof(hset_status_t)));
        }

        printf("[USE] %d\n", *(int*) (entry + sizeof(hset_status_t)));
    }

    printf("iterator version: %zu\n", self->iterator_version);
    printf("=== Hset ===\n");
}
