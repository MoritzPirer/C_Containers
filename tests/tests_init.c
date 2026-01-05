#include "../inc/darray.h"

int init_elementSize_0() {
    Darray d;
    DarrayStatus res = darrayInit(&d, 1, 0);

    if (res != DARRAY_ERROR_INVALID) return 1;

    return 0;
}

int init_NULL() {
    DarrayStatus res = darrayInit(NULL, 1, 1);

    if (res != DARRAY_ERROR_NULL) return 1;

    return 0;
}

int init_size_0() {
    Darray d;
    darrayInit(&d, 0, sizeof(int));

    if (d.m_element_size != sizeof(int)) return 1;
    if (d.m_elements_allocated != DARRAY_MIN_SIZE) return 2;
    if (d.m_elements_used != 0) return 3;

    return 0;
}

int init_size_1() {
    Darray d;
    darrayInit(&d, 1, sizeof(int));

    if (d.m_element_size != sizeof(int)) return 1;
    if (d.m_elements_allocated != DARRAY_MIN_SIZE) return 2;
    if (d.m_elements_used != 1) return 3;

    return 0;
}

int init_size_pow2() {
    Darray d;
    size_t size = 2*2*2*2*2*2;
    darrayInit(&d, size, sizeof(int));

    if (d.m_element_size != sizeof(int)) return 1;
    if (d.m_elements_allocated != size) return 2;
    if (d.m_elements_used != size) return 3;

    return 0;
}

int init_size_XL() {
    Darray d;
    size_t size = 10000000;
    darrayInit(&d, size, sizeof(int));

    if (d.m_element_size != sizeof(int)) return 1;
    if (d.m_elements_allocated < size) return 2;
    if (d.m_elements_used != size) return 3;

    return 0;
}


int init_size_XXXL() {
    Darray d;
    size_t size = (size_t) -1;
    DarrayStatus res = darrayInit(&d, size, sizeof(int));

    if (res == DARRAY_OK && d.m_data == NULL) return 1;

    return 0;
}