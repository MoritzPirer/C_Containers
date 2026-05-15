///
/// @file: vec_algs_sorting.c
/// @description: Contains functions related to sorting vecs
///
/// @date: 2026-01-07
/// @author: Moritz Pirer
///
#include <stdio.h>
#include <stdlib.h>

#include "../../inc/vec_algs.h"
#include "../vec_internal.h"

VecStatus vec_sort(vec_t *self, vec_ordering_t vec_ordering)
{
    if (self == NULL)
    {
        return VEC_ERROR_NULL;
    }

    qsort(self->m_data, self->size_used, self->item_size, vec_ordering);

    return VEC_OK;
}

bool vec_is_sorted(vec_t self, vec_ordering_t vec_ordering, bool is_ascending)
{
    if (self.size_used <= 1)
    { // sorted by definition
        return true;
    }

    int factor = (is_ascending ? 1 : -1); // inverts comparision for descending sorting

    for (size_t index = 1; index < self.size_used; index++)
    {
        if (vec_ordering(
                internal_vecNThElement(&self, index - 1),
                internal_vecNThElement(&self, index)) *
                factor >
            0)
        {
            return false;
        }
    }

    return true;
}

bool vec_is_sorted_asc(vec_t self, vec_ordering_t vec_ordering)
{
    return vec_is_sorted(self, vec_ordering, true);
}

bool vec_is_sorted_desc(vec_t self, vec_ordering_t vec_ordering)
{
    return vec_is_sorted(self, vec_ordering, false);
}