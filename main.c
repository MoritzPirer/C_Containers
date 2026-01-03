#include "darray.h"

#include <stdio.h>

int main() {
    Darray darray;
    darrayInit(&darray, 0, sizeof(int));

    // printf("%d\n", darrayIsEmpty(darray));
    darrayReserve(&darray, 10);
    for (int temp = 0; temp < 8; temp++) {
        darrayPushBack(&darray, &temp);
    }
    show(darray);
    
    int temp = 100;
    darrayPushFront(&darray, &temp);
    show(darray);
    darrayPushFront(&darray, &temp);
    show(darray);

    darrayDestroy(&darray);

    return 0;
}