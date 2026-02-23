///
/// @file: darray_size_capacity.h
/// @description: Contains functions related to the reserved capacity or used size 
///
/// @date: 2026-01-03 
/// @author: Moritz Pirer
///
#include <string.h>

#include "../darray_internal.h"

DarrayStatus darrayReserve(Darray* self, size_t elements_to_reserve) {
    if (self == NULL) {
        return DARRAY_ERROR_NULL;
    }

    pthread_mutex_lock(&(self->darray_lock));
    if (elements_to_reserve <= self->m_elements_allocated) {
        pthread_mutex_unlock(&(self->darray_lock));
        return DARRAY_OK; 
    }
    
    size_t new_size = max(self->m_elements_allocated, 1);
    while (new_size < elements_to_reserve) {
        new_size <<= 1;
    }
    
    DarrayStatus result = internal_darraySetSizeTo(self, new_size);
    pthread_mutex_unlock(&(self->darray_lock));

    return result;
}

DarrayStatus darrayShrinkToFit(Darray* self) {
    if (self == NULL) {
        return DARRAY_ERROR_NULL;
    }

    pthread_mutex_lock(&(self->darray_lock));
    
    if (self->m_elements_allocated == self->m_elements_used) {
        pthread_mutex_unlock(&(self->darray_lock));
        return DARRAY_OK;
    }

    DarrayStatus result = internal_darraySetSizeTo(self, self->m_elements_used);
    pthread_mutex_unlock(&(self->darray_lock));

    return result;
}

size_t darraySize(Darray self) {
    return self.m_elements_used;
}

size_t darrayCapacity(Darray self) {
    return self.m_elements_allocated;
}

bool darrayIsEmpty(Darray self) {
    return self.m_elements_used == 0;
}

DarrayStatus darrayResize(Darray* self, size_t new_size) {
    if (self == NULL) {
        return DARRAY_ERROR_NULL;
    }
    
    pthread_mutex_lock(&(self->darray_lock));
    if (new_size == self->m_elements_used) {
        return DARRAY_OK;
    }

    size_t old_size = self->m_elements_used;

    DarrayStatus resize_result = internal_darraySetSizeTo(self, new_size);
    if (resize_result != DARRAY_OK) {
        pthread_mutex_unlock(&(self->darray_lock));
        return resize_result;
    }

    //zero new memory
    if (new_size > old_size) {
        self->m_elements_used = new_size;
        memset(internal_darrayNThElement(self, old_size), 0, (new_size - old_size) * self->m_element_size);
    }

    pthread_mutex_unlock(&(self->darray_lock));
    return DARRAY_OK;
}