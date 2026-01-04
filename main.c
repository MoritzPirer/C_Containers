#include "inc/darray.h"

#include <stdio.h>

int main() {
    Darray darray;
    Darray darray2;
    
    darrayInit(&darray, 0, sizeof(int));
    darrayInit(&darray2, 0, sizeof(int));

    for (int temp = 0; temp < 15; temp++) {
        int tempi = 15 - temp;
        darrayPushBack(&darray, &temp);
        darrayPushBack(&darray2, &tempi);
    }
    int i = 20;
    darrayPushBack(&darray2, &i);
    show(darray);
    show(darray2);
    
    darraySwap(&darray, &darray2);
    
    show(darray);
    show(darray2);
   
    printf("%zu\n", darraySize(darray));
    printf("%zu\n", darraySize(darray2));

    darrayDestroy(&darray);
    darrayDestroy(&darray2);

    return 0;
}