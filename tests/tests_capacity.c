#include "../inc/vec/vec.h"

int capacity_afterPartialErase() {
    vec_t vec;
    vec_init(&vec, 0, sizeof(size_t));

    size_t element = 1;
    vec_push_back(&vec, &element);
    vec_push_back(&vec, &element);
    vec_push_back(&vec, &element);
    vec_push_back(&vec, &element);
    vec_push_back(&vec, &element);

    vec_erase_from(&vec, 1);

    if (vec_capacity(&vec) > 2 ) return 2;

    vec_push_back(&vec, &element);
    vec_push_back(&vec, &element);
    vec_push_back(&vec, &element);
    vec_push_back(&vec, &element);
    vec_push_back(&vec, &element);
    
    vec_erase_to(&vec, 3);

    if (vec_capacity(&vec) > 4) return 4;

    return 0;
}

int capacity_afterReserveResize() {
    vec_t vec;
    vec_init(&vec, 0, sizeof(int));

    vec_reserve(&vec, 10);

    if (vec_capacity(&vec) < 10) return 1;

    vec_resize(&vec, 20);

    if (vec_capacity(&vec) < 20) return 2;

    return 0;
}
