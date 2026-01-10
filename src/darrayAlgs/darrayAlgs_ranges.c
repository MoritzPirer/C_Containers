///
/// @file: darrayAlgs_ranges.c
/// @description: Contains functions related to creating a range of values
///
/// @date: 2026-01-10 
/// @author: Moritz Pirer
///
#include "../darray_internal.h"
#include "../../inc/darrayAlgs.h"

DarrayStatus darrayRangeFromToStep(Darray* self, size_t start, size_t stop, int step) {
    if (self == NULL) {
        return DARRAY_ERROR_NULL;
    }

    if (step == 0) {
        return DARRAY_ERROR_INVALID; // cannot step nowhere
    }
    if ((start < stop && step < 0) || (start > stop && step > 0)) {
        return DARRAY_ERROR_INVALID; // cannot step away from stop
    }

    int abs_step = (step > -step? step : -step);
    size_t num_elements_in_range = (max(start, stop) - min(start, stop)) / abs_step + 1;
    if (darrayInit(self, 0, sizeof(size_t)) != DARRAY_OK) {
        return DARRAY_ERROR_ALLOCATION;
    }
    if (darrayReserve(self, num_elements_in_range) != DARRAY_OK) {
        return DARRAY_ERROR_ALLOCATION;
    }

    for (size_t i = start; (step > 0? i < stop : i > stop); i += step) {
        darrayPushBack(self, &i);
    }

    return DARRAY_OK;
}

DarrayStatus darrayRangeFromTo(Darray* self, size_t start, size_t stop) {
    return darrayRangeFromToStep(self, start, stop, 1);
}

DarrayStatus darrayRangeToStep(Darray* self, size_t stop, int step) {
    return darrayRangeFromToStep(self, 0, stop, step);
}

DarrayStatus darrayRangeTo(Darray* self, size_t stop) {
    return darrayRangeFromToStep(self, 0, stop, 1);
}