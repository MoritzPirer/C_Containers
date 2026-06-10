#include "../../inc/hset/hset.h"

/// @brief for internal use; indicates if an entry in the hash table is free
typedef enum hset_item_state_t {
    HSET_EMPTY = 0,
    HSET_USED = 1,
    HSET_DELETED = 2,
} hset_item_state_t;

void hset_copy_from_nth_index(void* destination, const hset_t* source, size_t index);

void hset_copy_to_nth_index(hset_t* destination, const void* source, size_t index); 

#define HSET_PAYLOAD(x) x + sizeof(hset_item_state_t)
#define HSET_STATE(x) *(hset_item_state_t*) x