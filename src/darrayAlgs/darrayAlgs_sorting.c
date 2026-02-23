 ///
/// @file: darrayAlgs_sorting.c
/// @description: Contains functions related to sorting darrays 
///
/// @date: 2026-01-07 
/// @author: Moritz Pirer
///
#include <stdio.h>
#include <stdlib.h>

#include "../../inc/darrayAlgs.h"
#include "../darray_internal.h"

DarrayStatus darraySort(Darray* self, darrayOrdering darray_ordering) {
    if (self == NULL) {
        return DARRAY_ERROR_NULL;
    }

    pthread_mutex_lock(&self->darray_lock);

    qsort(self->m_data, self->m_elements_used, self->m_element_size, darray_ordering);
    
    pthread_mutex_unlock(&self->darray_lock);
    return DARRAY_OK;
}

bool darrayIsSorted(Darray self, darrayOrdering darray_ordering, bool is_ascending) {
    if (self.m_elements_used <= 1) { //sorted by definition
        return true;
    }
    
    pthread_mutex_lock(&self.darray_lock);
    int factor = (is_ascending? 1 : -1); //inverts comparision for descending sorting

    for (size_t index = 1; index < self.m_elements_used; index++) {
        if (darray_ordering(
            internal_darrayNThElement(&self, index - 1),
            internal_darrayNThElement(&self, index)) * factor > 0
        ) {
            pthread_mutex_unlock(&self.darray_lock);
            return false;
        }
    }

    pthread_mutex_unlock(&self.darray_lock);
    return true;
}

bool darrayIsSortedAscending(Darray self, darrayOrdering darray_ordering) {
    return darrayIsSorted(self, darray_ordering, true);
}

bool darrayIsSortedDescending(Darray self, darrayOrdering darray_ordering) {
    return darrayIsSorted(self, darray_ordering, false);
}