#include "../inc/darray.h"

int destroy_initialized() {
    Darray d;
    darrayInit(&d, 1, sizeof(int));

    darrayDestroy(&d);

    if (d.m_data != NULL) return 1;
    if (d.m_elements_allocated != 0) return 2;
    if (d.m_elements_used != 0) return 3;

    return 0;
}

int destroy_NULL() {
    darrayDestroy(NULL); //should not crash

    return 0;
}

int destroy_double() {
    Darray d;
    darrayInit(&d, 10, sizeof(int));

    darrayDestroy(&d);

    if (d.m_data != NULL) return 1;
    if (d.m_elements_allocated != 0) return 2;
    if (d.m_elements_used != 0) return 3;

    darrayDestroy(&d); // should not crash

    if (d.m_data != NULL) return 4;
    if (d.m_elements_allocated != 0) return 5;
    if (d.m_elements_used != 0) return 6;

    return 0;
}