///
/// @file: vec_algs.c
/// @description: Contains defaults for functions intended to be passed to other
///     vec_algs functions as function pointers.
///
/// @date: 2026-01-07
/// @author: Moritz Pirer
///

#include "../../inc/vec_algs.h"

bool vec_default_condition(const void *element, const void *data)
{
    return (*(size_t *)element == *(size_t *)data);
}

int vec_default_ordering(const void *a, const void *b)
{
    return (*(size_t *)a - *(size_t *)b);
}