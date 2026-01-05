#include "../inc/darray.h"

int init_NULL() {
    DarrayStatus res = darrayInit(NULL, 1, 1);

    if (res != DARRAY_ERROR_NULL) return 1;

    return 0;
}