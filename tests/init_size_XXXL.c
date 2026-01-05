#include "../inc/darray.h"

int init_size_XXXL() {
    Darray d;
    size_t size = (size_t) -1;
    DarrayStatus res = darrayInit(&d, size, sizeof(int));

    if (res == DARRAY_OK && d.m_data == NULL) return 1;

    return 0;
}