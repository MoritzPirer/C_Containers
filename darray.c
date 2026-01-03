#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "darray.h"

size_t max(size_t a, size_t b) {
    return (a > b? a : b);
}

size_t min(size_t a, size_t b) {
    return (a < b? a : b);
}

/// @brief return a pointer to the n-th element of array. Only for internal use
///     because pointer can become stale if the array reallocates
/// @attention caller is responsible for making sure that address is valid
/// @param this the darray to access 
/// @param index the index to access in the darray
/// @return a pointer to the n-th element
void* nThElement(Darray* this, size_t index) {
    return (void*) ((char*) this->m_data + (index * this->m_element_size));
}

/// @brief set the size of the darray to new_element_count. 
///     If the new size is less than the amount of elements in use, they are lost.
/// @param this the darray to modify
/// @param new_element_count the new size of the darray 
/// @return DARRAY_ERROR_ALLOCATION if reallocation failed, DARRAY_OK otherwise
DarrayStatus darraySetSizeTo(Darray* this, size_t new_element_count) {
    void* temp = realloc(this->m_data, new_element_count * this->m_element_size);

    if (temp == NULL) {
        return DARRAY_ERROR_ALLOCATION;
    }

    this->m_data = temp;
    this->m_elements_allocated = new_element_count;

    //reduce elements used when sizing down
    this->m_elements_used = min(this->m_elements_used, new_element_count); 

    return DARRAY_OK; 
}

DarrayStatus darrayGrow(Darray* this) {
    if (this->m_elements_used == this->m_elements_allocated) {
        DarrayStatus result = darraySetSizeTo(
            this,
            this->m_elements_allocated * DARRAY_GROW_FACTOR);
        return result;
    }

    return DARRAY_OK;
}

/// @brief If the darray is less than 1 / DARRAY_GROW_FACTOR full,
///     shrink to be 1 / DARRAY_GROW_FACTOR times the size
/// @example if DARRAY_GROW_FACTOR = 2, when less than half full (e.g. 2 used, 6 allocated),
///     shrink to be half as large (e.g. shrink from 6 used to 3 used)
/// @param this the darray to shrink
/// @return DARRAY_ERROR_ALLOCATION if reallocation failed, DARRAY_OK otherwise
DarrayStatus darrayShrinkIfNeeded(Darray* this) {
    if ((float) this->m_elements_used / this->m_elements_allocated < 1.0 / DARRAY_GROW_FACTOR) {
        return darraySetSizeTo(this, this->m_elements_allocated / DARRAY_GROW_FACTOR);
    }

    return DARRAY_OK;
}



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

DarrayStatus darrayReserve(Darray* this, size_t elements_to_reserve) {
    if (this == NULL) {
        return DARRAY_ERROR_NULL;
    }

    if (elements_to_reserve <= this->m_elements_allocated) {
        return DARRAY_OK; 
    }

    return darraySetSizeTo(this, elements_to_reserve);
}

DarrayStatus darrayShrinkToFit(Darray* this) {
    if (this == NULL) {
        return DARRAY_ERROR_NULL;
    }
    
    if (this->m_elements_allocated == this->m_elements_used) {
        return DARRAY_OK;
    }

    return darraySetSizeTo(this, this->m_elements_used);
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

DarrayStatus darrayPushBack(Darray* this, void* element) {
    if (this == NULL || element == NULL) {
        return DARRAY_ERROR_NULL;
    }

    DarrayStatus grow_result = darrayGrow(this);
    if (grow_result != DARRAY_OK) {
        return grow_result;
    }
    
    memcpy(nThElement(this, this->m_elements_used), element, this->m_element_size);

    this->m_elements_used++;
    
    return DARRAY_OK;
}


DarrayStatus darrayPopBackInto(Darray* this, void* buffer) {
    if (this == NULL || buffer == NULL) {
        return DARRAY_ERROR_NULL;
    }
    
    if (this->m_elements_used == 0) {
        return DARRAY_ERROR_BOUNDS;
    }
    
    memcpy(buffer, nThElement(this, this->m_elements_used - 1), this->m_element_size);

    this->m_elements_used--;

    return DARRAY_OK;
}

DarrayStatus darrayPushFront(Darray* this, void* element) {
    return darrayInsertAt(this, 0, element);
}

DarrayStatus darrayEraseFromTo(Darray* this, size_t start, size_t end) {
    if (this == NULL) {
        return DARRAY_ERROR_NULL;
    }
    
    if (start < 0 || start >= this->m_elements_used) {
        return DARRAY_ERROR_BOUNDS;
    }

    if (end < 0 || end >= this->m_elements_used) {
        return DARRAY_ERROR_BOUNDS;
    }

    if (end < start) {
        return DARRAY_ERROR_BOUNDS;
    }

    size_t num_elements_behind_erase = this->m_elements_used - end;
    if (num_elements_behind_erase > 0) { // if erase is at end, no overwrite is needed
        size_t bytes_to_copy = num_elements_behind_erase * this->m_element_size;
        char buffer[bytes_to_copy];
        
        memcpy(buffer, nThElement(this, end + 1), bytes_to_copy);

        memcpy(nThElement(this, start), buffer, bytes_to_copy);
    }

    this->m_elements_used -= (end - start + 1);

    return darrayShrinkIfNeeded(this);
}

DarrayStatus darrayEraseFrom(Darray* this, size_t start) {
    if (this == NULL) {
        return DARRAY_ERROR_NULL;
    }
    
    return darrayEraseFromTo(this, start, this->m_elements_used - 1);
}

DarrayStatus darrayEraseTo(Darray* this, size_t end) {
    return darrayEraseFromTo(this, 0, end);
}

DarrayStatus darrayEraseAt(Darray* this, size_t index) {
    return darrayEraseFromTo(this, index, index);
}

DarrayStatus darrayEraseAll(Darray* this) {
    if (this == NULL) {
        return DARRAY_ERROR_NULL;
    }
    
    return darrayEraseFromTo(this, 0, this->m_elements_used - 1);
}

DarrayStatus darrayInsertAt(Darray* this, size_t index, void* element) {
    if (this == NULL) {
        return DARRAY_ERROR_NULL;
    }
    
    if (index < 0 || index >= this->m_elements_used) {
        return DARRAY_ERROR_BOUNDS;
    }
    
    DarrayStatus grow_result = darrayGrow(this);
    if (grow_result != DARRAY_OK) {
        return grow_result;
    }
    
    size_t num_elements_behind_insert = this->m_elements_used - index;

    size_t bytes_to_copy = num_elements_behind_insert * this->m_element_size;

    char buffer[bytes_to_copy];
    memcpy(buffer, nThElement(this, index), bytes_to_copy);
    memcpy(nThElement(this, index + 1), buffer, bytes_to_copy);

    memcpy(nThElement(this, index), element, this->m_element_size);

    this->m_elements_used++;

    return DARRAY_OK;
}

DarrayStatus darrayGetAt(Darray* this, size_t index, void* buffer) {
    if (this == NULL || buffer == NULL) {
        return DARRAY_ERROR_NULL;
    }
    
    if (index < 0 || index >= this->m_elements_used) {
        return DARRAY_ERROR_BOUNDS;
    }

    memcpy(buffer, nThElement(this, index), this->m_element_size);

    return DARRAY_OK;
}

DarrayStatus darraySetAt(Darray* this, size_t index, void* buffer) {
    if (this == NULL) {
        return DARRAY_ERROR_NULL;
    }
    
    if (index < 0 || index >= this->m_elements_used) {
        return DARRAY_ERROR_BOUNDS;
    }

    memcpy(nThElement(this, index), buffer, this->m_element_size);

    return DARRAY_OK;
}

void show(Darray this) {
    for (size_t index = 0; index < this.m_elements_used; index++) {
        printf("%d, ", *(int*) nThElement(&this, index));
    }
    printf("\n");
}

