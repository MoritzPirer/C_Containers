///
/// @file: vec_algs_ranges.c
/// @description: Contains functions related to creating a range of values
///
/// @date: 2026-01-10
/// @author: Moritz Pirer
///
#include "../vec_internal.h"
#include "../../inc/vec_algs.h"

VecStatus vec_range_from_to_step(vec_t *self, size_t start, size_t stop, int step)
{
    if (self == NULL)
    {
        return VEC_ERROR_NULL;
    }

    if (step == 0)
    {
        return VEC_ERROR_INVALID; // cannot step nowhere
    }
    if ((start < stop && step < 0) || (start > stop && step > 0))
    {
        return VEC_ERROR_INVALID; // cannot step away from stop
    }

    int abs_step = (step > -step ? step : -step);
    size_t num_elements_in_range = (max(start, stop) - min(start, stop)) / abs_step + 1;
    if (vec_init(self, 0, sizeof(size_t)) != VEC_OK)
    {
        return VEC_ERROR_ALLOCATION;
    }
    if (vec_reserve(self, num_elements_in_range) != VEC_OK)
    {
        return VEC_ERROR_ALLOCATION;
    }

    for (size_t i = start; (step > 0 ? i < stop : i > stop); i += step)
    {
        vec_push_back(self, &i);
    }

    return VEC_OK;
}

VecStatus vec_range_from_to(vec_t *self, size_t start, size_t stop)
{
    return vec_range_from_to_step(self, start, stop, 1);
}

VecStatus vec_range_to_step(vec_t *self, size_t stop, int step)
{
    return vec_range_from_to_step(self, 0, stop, step);
}

VecStatus vec_range_to(vec_t *self, size_t stop)
{
    return vec_range_from_to_step(self, 0, stop, 1);
}