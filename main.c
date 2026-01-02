#include "darray.h"

#include <stdio.h>

int main() {
    Darray darray;
    darrayInit(&darray, 0, sizeof(int));

    // printf("%d\n", darrayIsEmpty(darray));
    darrayReserve(&darray, 10);
    int temp = 1;
    darrayPushBack(&darray, (void*) &temp);
    show(darray);
    temp = 2;
    darrayPushBack(&darray, (void*) &temp);
    show(darray);
    temp = 3;
    darrayPushBack(&darray, (void*) &temp);
    show(darray);
    temp = 4;
    darrayPushBack(&darray, (void*) &temp);
    show(darray);
    temp = 5;
    darrayPushBack(&darray, (void*) &temp);
    show(darray);
    temp = 6;
    darrayPushBack(&darray, (void*) &temp);
    show(darray);
    temp = -1;
    darraySetAt(&darray, 0, &temp);
    show(darray);
    
    darrayGetAt(&darray, 4, &temp);
    printf("%d", temp);
    
    darrayDestroy(&darray);

    return 0;
}