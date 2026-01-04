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
    darrayResize(&darray, 40);
    printf("size: %d", darraySize(darray));
    darrayGetAt(&darray, 30, &temp);
    temp += 'a';
    printf("%c", temp);

    darrayDestroy(&darray);

    return 0;
}