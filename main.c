#include "inc/darray.h"

#include <stdio.h>

int main() {
    Darray darray;
    if (darrayInit(&darray, 0, sizeof(char)) != DARRAY_OK) { printf("ALARM");}
    //getchar();
    darrayReserve(&darray, 10);
    for (char temp = 'a'; temp < 'z'; temp++) {
        darrayPushBack(&darray, &temp);
    }
    show(darray);

    
    char temp = '1';
    darrayPushFront(&darray, &temp);
    show(darray);
    darrayPopFrontInto(&darray, &temp);
    show(darray);

    darrayDestroy(&darray);

    return 0;
}