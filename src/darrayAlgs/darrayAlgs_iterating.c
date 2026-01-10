///
/// @file: darrayAlgs_iterating.c
/// @description: Contains functions related to doing something to each element in the darray 
///
/// @date: 2026-01-10 
/// @author: Moritz Pirer
///
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