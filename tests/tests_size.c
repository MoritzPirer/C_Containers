#include "../inc/darray.h"

int size_empty() {
    Darray d;
    darrayInit(&d, 0, sizeof(size_t));

    if (darraySize(d) != 0) return 1;

    return 0;
}

int size_push_pop() {
    Darray d;
    darrayInit(&d, 0, sizeof(size_t));

    size_t element = 1;
    darrayPushBack(&d, &element);

    if (darraySize(d) != 1) return 1;

    darrayPopBackInto(&d, &element);

    if (darraySize(d) != 0) return 2;

    return 0;
}

int size_afterErase() {
    Darray d;
    darrayInit(&d, 0, sizeof(size_t));

    size_t element = 1;
    darrayPushBack(&d, &element);
    darrayPushBack(&d, &element);
    darrayPushBack(&d, &element);

    if (darraySize(d) != 3) return 1;

    darrayClear(&d);

    if (darraySize(d) != 0) return 2;

    darrayPushBack(&d, &element);
    darrayPushBack(&d, &element);
    darrayPushBack(&d, &element);

    if (darraySize(d) != 3) return 3;

    darrayEraseAll(&d);

    if (darraySize(d) != 0) return 4;

    return 0;
}

int size_afterPartialErase() {
    Darray d;
    darrayInit(&d, 0, sizeof(size_t));

    size_t element = 1;
    darrayPushBack(&d, &element);
    darrayPushBack(&d, &element);
    darrayPushBack(&d, &element);
    darrayPushBack(&d, &element);
    darrayPushBack(&d, &element);

    darrayEraseFrom(&d, 1);

    if (darraySize(d) != 1) return 2;

    darrayPushBack(&d, &element);
    darrayPushBack(&d, &element);
    darrayPushBack(&d, &element);
    darrayPushBack(&d, &element);
    darrayPushBack(&d, &element);
    
    darrayEraseTo(&d, 3);

    if (darraySize(d) != 2) return 4;

    return 0;
}

int size_afterReserveResize() {
    Darray d;
    darrayInit(&d, 0, sizeof(int));

    darrayReserve(&d, 10);

    if (darraySize(d) != 0) return 1;

    darrayResize(&d, 20);

    if (darraySize(d) != 20) return 2;

    return 0;
}
