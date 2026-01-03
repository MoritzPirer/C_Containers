///
/// @file: darray_ownership.h
/// @description: Contains functions related to obtaining, owning and transferring 
///     ownership of memory. If it would be a constructor / destructor in C++, it belongs here.
///
/// @date: 2025-12-31
/// @author: Moritz Pirer
///

#include <stdio.h>
#include <stdlib.h>

#include "../darray_internal.h"

DarrayStatus darrayInit(Darray* this, size_t initial_size, size_t element_size) {
    if (this == NULL) {
        return DARRAY_ERROR_NULL;
    }

    this->m_elements_used = initial_size;
    this->m_elements_allocated = max(initial_size, DARRAY_MIN_SIZE);
    this->m_element_size = element_size;
    this->m_data = malloc(this->m_elements_allocated * element_size);

    if (this->m_data == NULL) {
        return DARRAY_ERROR_ALLOCATION;
    }

    return DARRAY_OK;
}

DarrayStatus darrayDestroy(Darray* this) {
    if (this == NULL) {
        return DARRAY_ERROR_NULL;
    }

    free(this->m_data);
    this->m_data = NULL;
    this->m_elements_allocated = 0;
    this->m_elements_used = 0;

    return DARRAY_OK;
}


//ONLY FOR DEVELOPMENT
void show(Darray this) {
    printf("darray has these %zu elements: ", this.m_elements_used);
    for (size_t index = 0; index < this.m_elements_used; index++) {
        printf("%d, ", *(int*) internal_darrayNThElement(&this, index));
    }
    printf("\n");
}

