#include "str.h"

bool str_equals(const str_t* a, const str_t* b);

bool str_equals_case(const str_t* a, const str_t* b);

int str_compare(const str_t* a, const str_t* b);

int str_compare_case(const str_t* a, const str_t* b);

bool str_starts_with_char(const str_t* self, char c);

bool str_starts_with_str(const str_t* self, const str_t* prefix);

bool str_ends_with_char(const str_t* self, char c);

bool str_ends_with_str(const str_t* self, const str_t* suffix);

bool str_is_uppercase(const str_t* self);

bool str_is_lowercase(const str_t* self);

bool str_is_numeric(const str_t* self);

bool str_is_alphabetic(const str_t* self);

bool str_is_alphanumeric(const str_t* self);
