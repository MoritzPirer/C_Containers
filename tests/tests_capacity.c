#include "../inc/darray.h"

int capacity_afterPartialErase() {
    Darray d;
    darrayInit(&d, 0, sizeof(size_t));

    size_t element = 1;
    darrayPushBack(&d, &element);
    darrayPushBack(&d, &element);
    darrayPushBack(&d, &element);
    darrayPushBack(&d, &element);
    darrayPushBack(&d, &element);

    darrayEraseFrom(&d, 1);

    if (darrayCapacity(d) > 2 ) return 2;

    darrayPushBack(&d, &element);
    darrayPushBack(&d, &element);
    darrayPushBack(&d, &element);
    darrayPushBack(&d, &element);
    darrayPushBack(&d, &element);
    
    darrayEraseTo(&d, 3);

    if (darrayCapacity(d) > 4) return 4;

    return 0;
}

int capacity_afterReserveResize() {
    Darray d;
    darrayInit(&d, 0, sizeof(int));

    darrayReserve(&d, 10);

    if (darrayCapacity(d) < 10) return 1;

    darrayResize(&d, 20);

    if (darrayCapacity(d) < 20) return 2;

    return 0;
}
