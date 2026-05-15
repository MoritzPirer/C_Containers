#include "../inc/vec_algs.h"


int is_sorted_asc_simple() {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    for (size_t i = 0; i < 10; i++) {
        vec_push_back(&d, &i);
    }

    if (!vec_is_sorted_asc(d, vec_default_ordering)) return 1;

    vec_destroy(&d);
    return 0;
}

int is_sorted_empty() {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));


    if (!vec_is_sorted_asc(d, vec_default_ordering)) return 1;

    vec_destroy(&d);
    return 0;
}

int is_sorted_asc_all_same() {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));
    size_t val = 10;
    for (size_t i = 0; i < 10; i++) {
        vec_push_back(&d, &val);
    }

    if (!vec_is_sorted_asc(d, vec_default_ordering)) return 1;

    vec_destroy(&d);
    return 0;
}

int is_sorted_asc_false() {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    for (size_t i = 20; i > 10; i--) {
        vec_push_back(&d, &i);
    }

    if (vec_is_sorted_asc(d, vec_default_ordering)) return 1;

    vec_destroy(&d);

    return 0;
}





int is_sorted_desc_simple() {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    for (size_t i = 20; i > 10; i--) {
        vec_push_back(&d, &i);
    }

    if (!vec_is_sorted_desc(d, vec_default_ordering)) return 1;

    vec_destroy(&d);
    return 0;
}

int is_sorted_desc_all_same() {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));
    size_t val = 10;
    for (size_t i = 0; i < 10; i++) {
        vec_push_back(&d, &val);
    }

    if (!vec_is_sorted_desc(d, vec_default_ordering)) return 1;

    vec_destroy(&d);
    return 0;
}

int is_sorted_desc_false() {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    for (size_t i = 0; i < 10; i++) {
        vec_push_back(&d, &i);
    }

    if (vec_is_sorted_desc(d, vec_default_ordering)) return 1;

    vec_destroy(&d);

    return 0;
}