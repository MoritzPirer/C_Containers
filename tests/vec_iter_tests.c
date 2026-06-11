#include "../inc/vec/vec_algs.h"
#include "../inc/vec/vec_iter.h"
#include "tests.h"
#include <stddef.h>

void vec_iter_init_test(void) {
    vec_t vec;
    vec_iter_t iter;
    vec_init(&vec, 0, sizeof(size_t));

    ASSERT_TRUE("creating an iterator should fail if vec is null", vec_iter_init(NULL, &iter, 0) == VEC_ERROR_NULL);
    ASSERT_TRUE("creating an iterator should fail if iter is null", vec_iter_init(&vec, NULL, 0) == VEC_ERROR_NULL);
    ASSERT_TRUE("creating an iterator should fail for empty vec", vec_iter_init(&vec, &iter, 0) == VEC_ERROR_BOUNDS);

    int vals[] = {1, 2, 3};
    vec_push_back(&vec, &vals[0]);
    vec_push_back(&vec, &vals[1]);
    vec_push_back(&vec, &vals[2]);

    ASSERT_TRUE("creating an iterator should fail for out of bounds", vec_iter_init(&vec, &iter, 5) == VEC_ERROR_BOUNDS);
    ASSERT_TRUE("creating an iterator succeed for non-empty vec", vec_iter_init(&vec, &iter, 0) == VEC_OK);

    vec_destroy(&vec);
}

void vec_iter_move_test() {
    vec_t vec;
    vec_iter_t iter;
    vec_init(&vec, 0, sizeof(int));

    int vals[] = {1, 2, 3};
    vec_push_back(&vec, &vals[0]);
    vec_push_back(&vec, &vals[1]);
    vec_push_back(&vec, &vals[2]);

    vec_iter_init(&vec, &iter, 0);

    ASSERT_TRUE("moving back should fail at index 0", vec_iter_previous(&iter, NULL) == VEC_ITER_END);
    ASSERT_TRUE("should not have previous at index 0", vec_iter_has_previous(&iter) == false);

    int temp = 0;
    ASSERT_TRUE("moving forward should succeed", vec_iter_next(&iter, &temp) == VEC_ITER_OK);
    ASSERT_TRUE("value should be written to temp", temp == 2);

    ASSERT_TRUE("should have next", vec_iter_has_next(&iter));
    ASSERT_TRUE("should have previous", vec_iter_has_previous(&iter));
    ASSERT_TRUE("should be at index 1", iter.current_index == 1);


    vec_iter_next(&iter, NULL);
    ASSERT_TRUE("should not have next", !vec_iter_has_next(&iter));
}

void vec_iter_get_set() {
    vec_t vec;
    vec_iter_t iter;
    vec_init(&vec, 0, sizeof(int));

    int vals[] = {1, 2, 3};
    vec_push_back(&vec, &vals[0]);
    vec_push_back(&vec, &vals[1]);
    vec_push_back(&vec, &vals[2]);

    vec_iter_init(&vec, &iter, 0);

    int temp = 10;

    ASSERT_TRUE("setting should succeed", vec_iter_set(&iter, &temp) == VEC_ITER_OK);
    temp = 1;
    vec_get(&vec, 0, &temp);
    ASSERT_TRUE("values should be reflected in the vec", temp == 10);
    temp = 15;
    vec_set(&vec, 0, &temp);
    temp = 0;
    vec_iter_get(&iter, &temp);
    ASSERT_TRUE("iterator should read new value", temp == 15);
}

void vec_iter_invalidation() {
    vec_t vecs[19];
    vec_iter_t iters[19];

    for (int i = 0; i < 19; i++) {
        vec_init(&vecs[i], 0, sizeof(int));

        int vals[] = {1, 2, 3};
        vec_push_back(&vecs[i], &vals[0]);
        vec_push_back(&vecs[i], &vals[1]);
        vec_push_back(&vecs[i], &vals[2]);

        vec_iter_init(&vecs[i], &iters[i], 0);
    }

    // all these functiuons should invalidate the corresponding iterator
    vec_erase_from_to(&vecs[0], 0, 1);
    vec_erase_from(&vecs[1], 1);
    vec_erase_to(&vecs[2], 1);
    vec_erase_at(&vecs[3], 1);
    vec_erase_all(&vecs[4]);
    vec_clear(&vecs[5]);
    vec_swap(&vecs[6], &vecs[7]);
    vec_append(&vecs[8], &vecs[9]);
    vec_reverse(&vecs[9]);
    vec_shrink(&vecs[10]);
    vec_resize(&vecs[11], 8);
    int temp = 0;
    vec_push_back(&vecs[12], &temp);
    vec_push_front(&vecs[13], &temp);
    vec_pop_back(&vecs[14], &temp);
    vec_pop_front(&vecs[15], &temp);
    vec_insert(&vecs[16], 0, &temp);
    vec_reverse(&vecs[17]);
    vec_sort(&vecs[18], vec_default_ordering);

    for (int i = 0; i < 19; i++) {
        ASSERT_TRUE("iter should be invalidated", vec_iter_next(&iters[i], NULL) == VEC_ITER_INVALID);
    }
}

void vec_iter_tests() {
    printf("--- RUNNING VECTOR ITERATOR TESTS ---\n");

    RUN_TEST(vec_iter_init_test);
    RUN_TEST(vec_iter_move_test);
    RUN_TEST(vec_iter_get_set);
    RUN_TEST(vec_iter_invalidation);

    printf("\n");
}
