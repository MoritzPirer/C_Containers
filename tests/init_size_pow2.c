#include "../inc/darray.h"

int init_size_pow2() {
    Darray d;
    size_t size = 2*2*2*2*2*2;
    darrayInit(&d, size, sizeof(int));

    if (d.m_element_size != sizeof(int)) return 1;
    if (d.m_elements_allocated != size) return 2;
    if (d.m_elements_used != size) return 3;

    return 0;
}