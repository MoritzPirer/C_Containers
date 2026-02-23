///
/// @file: darray_erase.c
/// @description: Contains functions related to erasing elements from a darray 
///
/// @date: 2026-01-03 
/// @author: Moritz Pirer
///

#include <string.h>

#include "../darray_internal.h"

DarrayStatus darrayEraseFromTo(Darray* self, size_t start, size_t end) {
    if (self == NULL) {
        return DARRAY_ERROR_NULL;
    }
    
    pthread_mutex_lock(&(self->darray_lock));

    if (!internal_darrayIsValidIndex(self, start)) {
        pthread_mutex_unlock(&(self->darray_lock));
        return DARRAY_ERROR_BOUNDS;
    }

    if (!internal_darrayIsValidIndex(self, end)) {
        pthread_mutex_unlock(&(self->darray_lock));
        return DARRAY_ERROR_BOUNDS;
    }

    if (end < start) {
        pthread_mutex_unlock(&(self->darray_lock));
        return DARRAY_ERROR_BOUNDS;
    }

    size_t num_elements_behind_erase = self->m_elements_used - end;
    if (num_elements_behind_erase > 0) { // if erase is at end, no overwrite is needed
        size_t bytes_to_copy = num_elements_behind_erase * self->m_element_size;
        internal_moveBytes(self, end + 1, start, bytes_to_copy);
    }

    self->m_elements_used -= (end - start + 1);

    DarrayStatus result = internal_darrayShrinkIfNeeded(self);
    pthread_mutex_unlock(&(self->darray_lock));

    return result;
}

DarrayStatus darrayEraseFrom(Darray* self, size_t start) {
    if (self == NULL) {
        return DARRAY_ERROR_NULL;
    }
    // synchronization in darrayEraseFromTo
    return darrayEraseFromTo(self, start, self->m_elements_used - 1);
}

DarrayStatus darrayEraseTo(Darray* self, size_t end) {
    // synchronization in darrayEraseFromTo
    return darrayEraseFromTo(self, 0, end);
}

DarrayStatus darrayEraseAt(Darray* self, size_t index) {
    // synchronization in darrayEraseFromTo
    return darrayEraseFromTo(self, index, index);
}

DarrayStatus darrayEraseAll(Darray* self) {
    if (self == NULL) {
        return DARRAY_ERROR_NULL;
    }
    
    // synchronization in darrayEraseFromTo
    return darrayEraseFromTo(self, 0, self->m_elements_used - 1);
}

DarrayStatus darrayClear(Darray* self) {
    // synchronization in darrayEraseFromTo
    return darrayEraseAll(self);
}