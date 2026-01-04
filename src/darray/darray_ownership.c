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
#include <string.h>

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

DarrayStatus darraySwap(Darray* this, Darray* other) {
    if (this == NULL || other == NULL) {
        return DARRAY_ERROR_NULL;
    }

    swapValues(&(this->m_element_size), &(other->m_element_size));
    swapValues(&(this->m_elements_allocated), &(other->m_elements_allocated));
    swapValues(&(this->m_elements_used), &(other->m_elements_used));

    void* temp = this->m_data;
    this->m_data = other->m_data;
    other->m_data = temp;
    
    return DARRAY_OK;
}

DarrayStatus darrayDeepCopy(Darray* original, Darray* copy) {
    if (original == NULL || copy == NULL) {
        return DARRAY_ERROR_NULL;
    }
    
    size_t data_amount_bytes = original->m_elements_allocated * original->m_element_size;
    copy->m_data = malloc(data_amount_bytes);
    if (copy->m_data == NULL) {
        return DARRAY_ERROR_ALLOCATION;
    }

    memcpy(copy->m_data, original->m_data, data_amount_bytes);

    copy->m_elements_used = original->m_elements_used;
    copy->m_elements_allocated = original->m_elements_used;
    copy->m_element_size = original->m_element_size;
    
}

//ONLY FOR DEVELOPMENT
void show(Darray this) {
    printf("darray has these %zu elements: ", this.m_elements_used);
    for (size_t index = 0; index < this.m_elements_used; index++) {
        printf("%d, ", *(int*) internal_darrayNThElement(&this, index));
    }
    printf("\n");
}

