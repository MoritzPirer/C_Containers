#include "../inc/darray.h"

int init_size_0() {
    Darray d;
    darrayInit(&d, 0, sizeof(int));

    if (d.m_element_size != sizeof(int)) return 1;
    if (d.m_elements_allocated != DARRAY_MIN_SIZE) return 2;
    if (d.m_elements_used != 0) return 3;

    return 0;
}