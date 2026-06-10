#include "../../inc/hset/hset.h"

/// @brief access the user data of an entry in the hash table
#define HSET_PAYLOAD(entry) entry + sizeof(hset_item_state_t)

/// @brief access the state of an entry in the hash table
#define HSET_STATE(entry) *(hset_item_state_t*) entry

/// @brief indicates if an entry in the hash table is free
typedef enum hset_item_state_t {
    HSET_EMPTY = 0,
    HSET_USED = 1,
    HSET_DELETED = 2,
} hset_item_state_t;

void hset_copy_from_nth_index(void* destination, const hset_t* source, size_t index);

void hset_copy_to_nth_index(hset_t* destination, const void* source, size_t index); 
