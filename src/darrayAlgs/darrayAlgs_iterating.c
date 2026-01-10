///
/// @file: darrayAlgs_iterating.c
/// @description: Contains functions related to doing something to each element in the darray 
///
/// @date: 2026-01-10 
/// @author: Moritz Pirer
///

#include <string.h>

#include "../darray_internal.h"
#include "../../inc/darrayAlgs.h"

bool darrayAny(Darray self, darrayCondition condition, void* data) {
    for (size_t index = 0; index < self.m_elements_used; index++) {
        if (condition(internal_darrayNThElement(&self, index), data) == true) {
            return true;
        }
    }
    
    return false;
}

bool darrayAll(Darray self, darrayCondition condition, void* data) {
    for (size_t index = 0; index < self.m_elements_used; index++) {
        if (condition(internal_darrayNThElement(&self, index), data) == false) {
            return false;
        }
    }
    
    return true;
}

bool darrayNone(Darray self, darrayCondition condition, void* data) {
    for (size_t index = 0; index < self.m_elements_used; index++) {
        if (condition(internal_darrayNThElement(&self, index), data) == true) {
            return false;
        }
    }
    
    return true;
}

void darrayReverse(Darray* self) {
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
}