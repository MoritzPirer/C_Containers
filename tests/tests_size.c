#include "../inc/vec/vec_algs.h"

int size_empty() {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    if (vec_size(&d) != 0) return 1;

    return 0;
}

int size_push_pop() {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    size_t element = 1;
    vec_push_back(&d, &element);

    if (vec_size(&d) != 1) return 1;

    vec_pop_back(&d, &element);

    if (vec_size(&d) != 0) return 2;

    return 0;
}

int size_afterErase() {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    size_t element = 1;
    vec_push_back(&d, &element);
    vec_push_back(&d, &element);
    vec_push_back(&d, &element);

    if (vec_size(&d) != 3) return 1;

    vec_clear(&d);

    if (vec_size(&d) != 0) return 2;

    vec_push_back(&d, &element);
    vec_push_back(&d, &element);
    vec_push_back(&d, &element);

    if (vec_size(&d) != 3) return 3;

    vec_erase_all(&d);

    if (vec_size(&d) != 0) return 4;

    return 0;
}

int size_afterPartialErase() {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    size_t element = 1;
    vec_push_back(&d, &element);
    vec_push_back(&d, &element);
    vec_push_back(&d, &element);
    vec_push_back(&d, &element);
    vec_push_back(&d, &element);

    vec_erase_from(&d, 1);

    if (vec_size(&d) != 1) return 2;

    vec_push_back(&d, &element);
    vec_push_back(&d, &element);
    vec_push_back(&d, &element);
    vec_push_back(&d, &element);
    vec_push_back(&d, &element);
    
    vec_erase_to(&d, 3);

    if (vec_size(&d) != 2) return 4;

    return 0;
}

int size_afterReserveResize() {
    vec_t d;
    vec_init(&d, 0, sizeof(int));

    vec_reserve(&d, 10);

    if (vec_size(&d) != 0) return 1;

    vec_resize(&d, 20);

    if (vec_size(&d) != 20) return 2;

    return 0;
}
