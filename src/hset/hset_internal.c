#include <string.h>
#include "hset_internal.h"

void hset_copy_from_nth_index(void* destination, const hset_t* source, size_t index) {
    memcpy(destination, (void *)((char *)source->table + (index * source->boosted_size)), source->boosted_size);
};

void hset_copy_to_nth_index(hset_t* destination, const void* source, size_t index) {
    memcpy((void *)((char *)destination->table + (index * destination->boosted_size)), source, destination->boosted_size);
}