///
/// @file: darrayAlgs_iterating.c
/// @description: Contains functions related to doing something to each element in the darray 
///
/// @date: 2026-01-10 
/// @author: Moritz Pirer
///

#include <string.h>
#include <assert.h>

#include "../darray_internal.h"
#include "../../inc/darrayAlgs.h"

bool darrayAny(Darray self, darrayCondition condition, const void* data) {
    pthread_mutex_lock(&self.darray_lock);
    for (size_t index = 0; index < self.m_elements_used; index++) {
        if (condition(internal_darrayNThElement(&self, index), data) == true) {
            pthread_mutex_unlock(&self.darray_lock);
            return true;
        }
    }
    
    pthread_mutex_unlock(&self.darray_lock);
    return false;
}

bool darrayAll(Darray self, darrayCondition condition, const void* data) {
    pthread_mutex_unlock(&self.darray_lock);
    for (size_t index = 0; index < self.m_elements_used; index++) {
        if (condition(internal_darrayNThElement(&self, index), data) == false) {
            pthread_mutex_unlock(&self.darray_lock);
            return false;
        }
    }
    
    pthread_mutex_unlock(&self.darray_lock);
    return true;
}

bool darrayNone(Darray self, darrayCondition condition, const void* data) {
    pthread_mutex_lock(&self.darray_lock);
    for (size_t index = 0; index < self.m_elements_used; index++) {
        if (condition(internal_darrayNThElement(&self, index), data) == true) {
            pthread_mutex_unlock(&self.darray_lock);
            return false;
        }
    }
    
    pthread_mutex_unlock(&self.darray_lock);
    return true;
}

void darrayReverse(Darray* self) {
    pthread_mutex_lock(&self->darray_lock);
    for (size_t index = 0; index < self->m_elements_used / 2; index++) {
        size_t swap_index = self->m_elements_used - index - 1;
        char buffer[self->m_element_size];
        memcpy(buffer, internal_darrayNThElement(self, index), self->m_element_size);
        memcpy(
            internal_darrayNThElement(self, index),
            internal_darrayNThElement(self, swap_index),
            self->m_element_size
        );
        memcpy(internal_darrayNThElement(self, swap_index), buffer, self->m_elements_used);
    }

    pthread_mutex_unlock(&self->darray_lock);
}

DarrayStatus darrayFilter(Darray* self, darrayCondition condition,
    Darray* filtered, const void* data) {
   
    assert(false); // this function is not yet thread safe
   
    if (self == NULL || filtered == NULL) {
        return DARRAY_ERROR_NULL;
    }

    if (darrayInit(filtered, 0, sizeof(size_t)) != DARRAY_OK) {
        return DARRAY_ERROR_ALLOCATION;
    }
    
    if (darrayReserve(filtered, self->m_elements_used) != DARRAY_OK) {
        return DARRAY_ERROR_ALLOCATION;
    }

    for (size_t index = 0; index < self->m_elements_used; index++) {
        if (condition(internal_darrayNThElement(self, index), data) == false) {
            continue;
        }

        DarrayStatus result = darrayPushBack(filtered, internal_darrayNThElement(self, index));
        if (result != DARRAY_OK) {
            return result;
        }
    }

    return darrayShrinkToFit(filtered);
}

DarrayStatus darrayTransform(Darray* self, darrayTransformation transfomration, const void* data) {
    if (self == NULL) {
        return DARRAY_ERROR_NULL;
    }

    pthread_mutex_lock(&self->darray_lock);

    for (size_t index = 0; index < self->m_elements_used; index++) {
        transfomration(internal_darrayNThElement(self, index), data);
    }

    pthread_mutex_unlock(&self->darray_lock);
    return DARRAY_OK;
}