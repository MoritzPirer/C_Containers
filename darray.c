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

void* offsetPointer(void* pointer, size_t offset) {
    return (void*) ((char*) pointer + offset);
}

DarrayStatus darraySetSizeTo(Darray* darray, size_t new_element_count) {
    void* temp = realloc(darray->m_data, new_element_count * darray->m_element_size);

    if (temp == NULL) {
        darrayDestroy(darray);
        return DARRAY_ERROR_ALLOCATION;
    }

    darray->m_data = temp;
    darray->m_elements_allocated = new_element_count;

    //reduce elements used when sizing down
    darray->m_elements_used = min(darray->m_elements_used, new_element_count); 

    printf("resizing!\n");

    return DARRAY_OK; 
}

DarrayStatus darrayInit(Darray* darray, size_t initial_size, size_t element_size) {
    darray->m_elements_used = initial_size;
    darray->m_elements_allocated = max(initial_size, DARRAY_MIN_SIZE);
    darray->m_element_size = element_size;
    darray->m_data = malloc(darray->m_elements_allocated * element_size);

    if (darray->m_data == NULL) {
        return DARRAY_ERROR_ALLOCATION;
    }

    return DARRAY_OK;
}

void darrayDestroy(Darray* darray) {
    free(darray->m_data);
    darray->m_data = NULL;
    darray->m_elements_allocated = 0;
    darray->m_elements_used = 0;
}

DarrayStatus darrayReserve(Darray* darray, size_t elements_to_reserve) {
    if (elements_to_reserve <= darray->m_elements_allocated) {
        return DARRAY_OK; 
    }

    return darraySetSizeTo(darray, elements_to_reserve);
}

DarrayStatus darrayShrinkToFit(Darray* darray) {
    if (darray->m_elements_allocated == darray->m_elements_used) {
        return DARRAY_OK;
    }

    return darraySetSizeTo(darray, darray->m_elements_used);
}

size_t darraySize(Darray darray) {
    return darray.m_elements_used;
}

size_t darrayCapacity(Darray darray) {
    return darray.m_elements_allocated;
}

bool darrayIsEmpty(Darray darray) {
    return darray.m_elements_used == 0;
}

DarrayStatus darrayPushBack(Darray* darray, void* element) {
    if (darray->m_elements_used == darray->m_elements_allocated) {
        DarrayStatus result = darraySetSizeTo(
            darray, darray->m_elements_allocated * DARRAY_GROW_FACTOR);
        if (result != DARRAY_OK) {
            return result;
        }
    }
    
    size_t offset = darray->m_element_size * darray->m_elements_used;
    void* new_element_posiiton = offsetPointer(darray->m_data, offset);
    
    memcpy(new_element_posiiton, element, darray->m_element_size);

    darray->m_elements_used++;
    
    return DARRAY_OK;
}

void show(Darray darray) {
    void* current_element = darray.m_data;

    for (size_t _ = 0; _ < darray.m_elements_used; _++) {
        printf("%d, ", *(int*) current_element);
        current_element = offsetPointer(current_element, darray.m_element_size);
    }
    printf("\n");
}