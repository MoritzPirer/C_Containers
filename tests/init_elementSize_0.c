#include "../inc/darray.h"

int init_elementSize_0() {
    Darray d;
    DarrayStatus res = darrayInit(&d, 1, 0);

    if (res != DARRAY_ERROR_INVALID) return 1;

    return 0;
}