#ifndef STR_INTERNAL_H
#define STR_INTERNAL_H

#include "../../../inc/str/str.h"

str_status_t _str_realloc(str_t* self, size_t new_size);

inline bool _str_is_less_than_half_full(str_t* self);
#endif // STR_INTERNAL_H