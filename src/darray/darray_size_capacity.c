///
/// @file: darray_size_capacity.h
/// @description: Contains functions related to the reserved capacity or used size 
///
/// @date: 2026-01-03 
/// @author: Moritz Pirer
///

#include "../darray_internal.h"

DarrayStatus darrayReserve(Darray* this, size_t elements_to_reserve) {
    if (this == NULL) {
        return DARRAY_ERROR_NULL;
    }

    if (elements_to_reserve <= this->m_elements_allocated) {
        return DARRAY_OK; 
    }
    //MODO rework tu use geometric growth
    size_t new_size = max(this->m_elements_allocated, 1);
    while (new_size < elements_to_reserve) {
        new_size <<= 1;
    }
    
    return internal_darraySetSizeTo(this, new_size);
}

DarrayStatus darrayShrinkToFit(Darray* this) {
    if (this == NULL) {
        return DARRAY_ERROR_NULL;
    }
    
    if (this->m_elements_allocated == this->m_elements_used) {
        return DARRAY_OK;
    }

    return internal_darraySetSizeTo(this, this->m_elements_used);
}

size_t darraySize(Darray this) {
    return this.m_elements_used;
}

size_t darrayCapacity(Darray this) {
    return this.m_elements_allocated;
}

bool darrayIsEmpty(Darray this) {
    return this.m_elements_used == 0;
}