#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "hset_internal.h"

bool hset_default_comparison(const void* a, const void* b, size_t item_size) {
    unsigned char a_bits[item_size];
    unsigned char b_bits[item_size];
    memcpy(a_bits, a, item_size);
    memcpy(b_bits, b, item_size);

    for (size_t i = 0; i < item_size; i++) {
        if ((a_bits[i] ^ b_bits[i]) != 0) {
            return false;
        }
    }
    
    return true;
}

void hset_debug(hset_t* self) {
    if (self == NULL) {
        return;
    }
    
    printf("=========\n");
    printf("size: %zu\n", self->size);
    printf("capacity: %zu\n", self->capacity);
    printf("item size: %zu\n", self->item_size);
    
    for (size_t index = 0; index < self->capacity; index++) {
        unsigned char entry[self->boosted_size];
        hset_copy_from_nth_index(entry, self, index);

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
    printf("=========\n");
}

hset_status_t hset_init(hset_t* self, size_t initial_size, size_t element_size, hset_comparison_t comparison) {
    if (self == NULL) {
        return HSET_ERROR_NULL;
    }
    if (element_size == 0) {
        return HSET_ERROR_INVALID;
    }

    self->item_size = element_size;
    self->boosted_size = element_size + sizeof(hset_item_state_t);
    if (comparison == NULL) {
        self->comparison = &hset_default_comparison;
    }
    else {
        self->comparison = comparison;
    }

    self->size = 0;
    self->capacity = initial_size > HSET_MIN_SIZE ? initial_size : HSET_MIN_SIZE;
    
    self->table = calloc(self->capacity, self->boosted_size);
    if (self->table == NULL) {
        return HSET_ERROR_ALLOCATION;
    }

    return HSET_OK;
}

hset_status_t hset_destroy(hset_t* self) {
    if (self == NULL) {
        return HSET_ERROR_NULL;
    }

    free(self->table);
    self->table = NULL;
    self->capacity = 0;
    self->size = 0;

    return HSET_OK;
}

hset_status_t hset_copy(const hset_t* self, hset_t* copy) {
    if (self == NULL || copy == NULL) {
        return HSET_ERROR_NULL;
    }

    copy->size = self->size;
    copy->capacity = self->capacity;
    copy->item_size = self->item_size;
    copy->boosted_size = self->boosted_size;
    copy->comparison = self->comparison;

    copy->table = calloc(copy->capacity, copy->boosted_size);
    if (copy->table == NULL) {
        return HSET_ERROR_NULL;
    }

    memcpy(copy->table, self->table, copy->capacity * copy->boosted_size);

    return HSET_OK;
}